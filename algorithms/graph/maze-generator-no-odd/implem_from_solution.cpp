#include <algorithm>
#include <random>
#include <stack>
#include <vector>

#include "aim.hpp"
#include "maze.hpp"

struct Delta
{
  int x, y;
  Delta(int x, int y) : x(x), y(y) {}
};

struct UnvisitOnDelete
{
  char** maze_;
  Dimension dim_;
  UnvisitOnDelete(char** maze, Dimension const& dim) : maze_(maze), dim_(dim) {}
  ~UnvisitOnDelete()
  {
    const char visited { to_char(MazeElement::Undefined) };
    const char wall { to_char(MazeElement::Wall) };
    for (std::size_t j {} ; j < dim_.height ; j += 2)
    {
      for (std::size_t i {} ; i < dim_.width ; i += 2)
      {
        if (maze_[j][i] == visited) { maze_[j][i] = wall; }
      }
    }
  }
};

// Check properties

static bool is_inside(char** /*maze*/, Dimension const& dim, Point const& pt)
{
  return pt.x < dim.width && pt.y < dim.height;
}
static bool is_wall(char** maze, Dimension const& /*dim*/, Point const& pt)
{
  return maze[pt.y][pt.x] == to_char(MazeElement::Wall);
}
static bool is_inside_wall(char** maze, Dimension const& dim, Point const& pt)
{
  return is_inside(maze, dim, pt) && is_wall(maze, dim, pt);
}

static bool can_reach_end(char** maze, Dimension const& dim, Point const& origin, Point const& end)
{
  UnvisitOnDelete undoMe { maze, dim };

  std::stack<Point> can_be_visited;
  auto push_and_visit = [&can_be_visited,&maze,visited=to_char(MazeElement::Undefined)](auto&& pt) {
      can_be_visited.push(pt);
      maze[pt.y][pt.x] = visited;
  };

  push_and_visit(origin);
  while (! can_be_visited.empty())
  {
    Point pt { can_be_visited.top() };
    can_be_visited.pop();
    if (pt == end) { return true; }
    
    if (is_inside_wall(maze, dim, Point{pt.x-2, pt.y})) { push_and_visit(Point{pt.x-2, pt.y}); }
    if (is_inside_wall(maze, dim, Point{pt.x+2, pt.y})) { push_and_visit(Point{pt.x+2, pt.y}); }
    if (is_inside_wall(maze, dim, Point{pt.x, pt.y-2})) { push_and_visit(Point{pt.x, pt.y-2}); }
    if (is_inside_wall(maze, dim, Point{pt.x, pt.y+2})) { push_and_visit(Point{pt.x, pt.y+2}); }
  }
  return false;
}

// Helpers

template <class Container, class Predicate>
static void push_if(Container& container, char** maze, Dimension const& dim, Point const& pt, Delta const& delta, Predicate&& predicate)
{
  if (predicate(maze, dim, Point{pt.x + 2*delta.x, pt.y + 2*delta.y}))
  {
    container.push_back(delta);
  }
}

template <class Predicate, class Gen>
static auto build_choices(char** maze, Dimension const& dim, Point const& pt, Predicate&& predicate, Gen& g)
{
  std::vector<Delta> choices;
  push_if(choices, maze, dim, pt, Delta{-1, 0}, predicate);
  push_if(choices, maze, dim, pt, Delta{ 1, 0}, predicate);
  push_if(choices, maze, dim, pt, Delta{ 0,-1}, predicate);
  push_if(choices, maze, dim, pt, Delta{ 0, 1}, predicate);
  std::shuffle(choices.begin(), choices.end(), g);
  return choices;
}

template <class Gen>
static void adapt_for_traps(std::vector<std::pair<Point, std::vector<Delta>>>& main_roads, char** maze, Dimension const& dim, Gen& g)
{
  main_roads.erase(
      std::remove_if(main_roads.begin(), main_roads.end(), [](auto&& details) { return details.first.x % 2 != 0 || details.first.y % 2 != 0; })
      , main_roads.end());
  std::transform(main_roads.begin(), main_roads.end()
      , main_roads.begin()
      , [&](auto&& details) { return std::make_pair(details.first, build_choices(maze, dim, details.first, is_inside_wall, g)); });
  main_roads.erase(
      std::remove_if(main_roads.begin(), main_roads.end(), [](auto&& details) { return details.second.empty(); })
      , main_roads.end());
  std::shuffle(main_roads.begin(), main_roads.end(), g);
}

// Maze generation steps

static void reset(char** maze, Dimension const& dim)
{
  std::for_each(maze, maze+dim.height
	  , [width = dim.width, wall = to_char(MazeElement::Wall)](char* line) { std::fill(line, line + width, wall); });
}

template <class Gen>
static auto generate_main_path(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt, Gen& g)
{
  // Generate a random path starting at start_pt and going to end_pt
  // Only one path will be generated

  const char road = to_char(MazeElement::Road);
  const char wall = to_char(MazeElement::Wall);

  auto path_to_end = std::vector<std::pair<Point, std::vector<Delta>>>{};
  auto current = Point{ start_pt };
  auto choices = build_choices(maze, dim, current, is_inside_wall, g);

  while (current != end_pt)
  {
    if (choices.empty())
    {// no more choices: backtrack
      current = path_to_end.back().first;
      maze[current.y][current.x] = wall;
      path_to_end.pop_back();
      
      current = path_to_end.back().first;
      choices = std::move(path_to_end.back().second);
      maze[current.y][current.x] = wall;
      path_to_end.pop_back();
      continue;
    }
    
    auto d  = Delta{ choices.back() };
    choices.pop_back();

    // check if such path can lead to the end of the maze
    maze[current.y][current.x] = road;
    if (! can_reach_end(maze, dim, Point{ current.x + 2 * d.x, current.y + 2 * d.y }, end_pt))
    {
      maze[current.y][current.x] = to_char(MazeElement::Wall);
      continue;
    }
    
    // current decision
    path_to_end.emplace_back(current, std::move(choices));
    
    // junction road
    current = Point{ current.x + d.x, current.y + d.y };
    path_to_end.emplace_back(current, decltype(choices){});
    maze[current.y][current.x] = road;
    
    // next position
    current = Point{ current.x + d.x, current.y + d.y };
    choices = build_choices(maze, dim, current, is_inside_wall, g);
  }
  
  maze[start_pt.y][start_pt.x] = to_char(MazeElement::Start);
  maze[end_pt.y][end_pt.x] = to_char(MazeElement::End);
  return path_to_end;
}

static void clean_not_accessible(char** maze, Dimension const& dim, std::pair<Point, std::vector<Delta>>& crossroad)
{
  auto const& pt = crossroad.first;
  auto& choices = crossroad.second;
  choices.erase(
      std::remove_if(choices.begin(), choices.end(), [&](auto const& d) { return ! is_inside_wall(maze, dim, Point{ pt.x + 2 * d.x, pt.y + 2 * d.y }); })
      , choices.end());
}

template <class Gen>
static void generate_trap_paths(char** maze, Dimension const& dim, std::vector<std::pair<Point, std::vector<Delta>>> nonfull_crossroads, Gen& g)
{
  const char road = to_char(MazeElement::Road);
  while (! nonfull_crossroads.empty())
  {
    auto const& pt = nonfull_crossroads.back().first;
    auto& choices = nonfull_crossroads.back().second;

    auto valid_delta = std::find_if(choices.begin(), choices.end()
		, [&](Delta d) { return is_inside_wall(maze, dim, Point{ pt.x + 2 * d.x, pt.y + 2 * d.y }); });

    if (valid_delta == choices.end())
    {// no path is accessible from this road
      // update possible choices of each road
      std::for_each(nonfull_crossroads.begin(), nonfull_crossroads.end(), [&](auto&& details) { clean_not_accessible(maze, dim, details); });
      // remove roads not having choices
      nonfull_crossroads.erase(
          std::remove_if(nonfull_crossroads.begin(), nonfull_crossroads.end(), [](auto&& details) { return details.second.empty(); })
          , nonfull_crossroads.end());
      // shuffle remaining roads
      std::shuffle(nonfull_crossroads.begin(), nonfull_crossroads.end(), g);
      continue;
    }

    auto d = *valid_delta;
    auto junction = Point{ pt.x + d.x, pt.y + d.y };
    auto target = Point{ pt.x + 2 * d.x, pt.y + 2 * d.y };
    maze[junction.y][junction.x] = road;
    maze[target.y][target.x] = road;

    auto next_choices = build_choices(maze, dim, target, is_inside_wall, g);
    if (! next_choices.empty())
    {
      nonfull_crossroads.emplace_back(target, std::move(next_choices));
    }    
  }
}

// Algorithm to be tested

void generate_maze(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt, unsigned seed)
{
  std::mt19937 g(seed);

  reset(maze, dim);
  auto main_roads = generate_main_path(maze, dim, start_pt, end_pt, g);
  adapt_for_traps(main_roads, maze, dim, g);
  generate_trap_paths(maze, dim, std::move(main_roads), g);
}
