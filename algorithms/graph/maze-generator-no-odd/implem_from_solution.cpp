#include <algorithm>
#include <iostream>
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

struct UndoCanReach
{
  char** maze_;
  Dimension dim_;
  UndoCanReach(char** maze, Dimension const& dim) : maze_(maze), dim_(dim) {}
  ~UndoCanReach()
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
static bool can_reach_end(char** maze, Dimension const& dim, Point const& origin, Point const& end)
{
  const char visited { to_char(MazeElement::Undefined) };
  UndoCanReach undoMe { maze, dim };

  std::stack<Point> can_be_visited;
  can_be_visited.push(origin);
  while (! can_be_visited.empty())
  {
    Point pt { can_be_visited.top() };
    can_be_visited.pop();

    if (pt == end)
    {
      return true;
    }
    maze[pt.y][pt.x] = visited;
    if (is_inside_wall(maze, dim, Point{pt.x-2, pt.y})) { can_be_visited.emplace(pt.x-2, pt.y); }
    if (is_inside_wall(maze, dim, Point{pt.x+2, pt.y})) { can_be_visited.emplace(pt.x+2, pt.y); }
    if (is_inside_wall(maze, dim, Point{pt.x, pt.y-2})) { can_be_visited.emplace(pt.x, pt.y-2); }
    if (is_inside_wall(maze, dim, Point{pt.x, pt.y+2})) { can_be_visited.emplace(pt.x, pt.y+2); }
  }
  return false;
}

// Algorithm to be tested

void generate_maze(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt, unsigned seed)
{
  auto const& width = dim.width;
  auto const& height = dim.height;
  
  // Reset the map
  for (std::size_t j {} ; j != height ; ++j)
  {
    for (std::size_t i {} ; i != width ; ++i)
    {
      maze[j][i] = to_char(MazeElement::Wall);
    }
  }
  
  // Random journey in the grid
  std::mt19937 g(seed);
  std::vector<Point> toscan;
  
  auto push_if = [](auto& container, char** maze, Dimension const& dim, Point const& pt, Delta const& delta, auto&& predicate) {
      if (predicate(maze, dim, Point{pt.x + 2*delta.x, pt.y + 2*delta.y})) { container.push_back(delta); }
  };
  auto build_choices = [&push_if](char** maze, Dimension const& dim, Point const& pt, auto&& predicate) {
    std::vector<Delta> choices;
    push_if(choices, maze, dim, pt, Delta{-1, 0}, predicate);
    push_if(choices, maze, dim, pt, Delta{ 1, 0}, predicate);
    push_if(choices, maze, dim, pt, Delta{ 0,-1}, predicate);
    push_if(choices, maze, dim, pt, Delta{ 0, 1}, predicate);
    return choices;
  };
  
  std::vector<std::pair<Point, std::vector<Delta>>> path_to_end;
  
  // 1. build a solution

  auto current = Point{ start_pt };
  auto choices = build_choices(maze, dim, current, is_inside_wall);
  std::shuffle(choices.begin(), choices.end(), g);
  while (current != end_pt)
  {
    if (choices.empty())
    {
      current = path_to_end.back().first;
      maze[current.y][current.x] = to_char(MazeElement::Wall);
      path_to_end.pop_back();
      
      current = path_to_end.back().first;
      choices = std::move(path_to_end.back().second);
      maze[current.y][current.x] = to_char(MazeElement::Wall);
      path_to_end.pop_back();
      continue;
    }
    
    Delta d { choices.back() };
    choices.pop_back();

    // check if such path can lead to the end of the maze
    maze[current.y][current.x] = to_char(MazeElement::Road);
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
    maze[current.y][current.x] = to_char(MazeElement::Road);
    
    // next position
    current = Point{ current.x + d.x, current.y + d.y };
    choices = build_choices(maze, dim, current, is_inside_wall);
    std::shuffle(choices.begin(), choices.end(), g);
  }
  
  // Put start and end
  maze[start_pt.y][start_pt.x] = to_char(MazeElement::Start);
  maze[end_pt.y][end_pt.x] = to_char(MazeElement::End);

  // 2. derive wrong paths from solution

  path_to_end.erase(
      std::remove_if(path_to_end.begin(), path_to_end.end(), [](auto&& details) { return details.first.x % 2 != 0 || details.first.y % 2 != 0; })
      , path_to_end.end());
  std::transform(path_to_end.begin(), path_to_end.end()
      , path_to_end.begin()
      , [&g,maze,&dim,&build_choices](auto&& details) {
          auto&& choices = build_choices(maze, dim, details.first, is_inside_wall);
          std::shuffle(choices.begin(), choices.end(), g);
          return std::make_pair(details.first, choices);
        });
  path_to_end.erase(
      std::remove_if(path_to_end.begin(), path_to_end.end(), [](auto&& details) { return details.second.empty(); })
      , path_to_end.end());
  std::shuffle(path_to_end.begin(), path_to_end.end(), g);

  while (! path_to_end.empty())
  {
    auto const& pt { path_to_end.back().first };
    auto& choices { path_to_end.back().second };
    if (choices.empty())
    {// no path is accessible from this road
      // update possible choices of each road
      std::for_each(path_to_end.begin(), path_to_end.end()
          , [maze,&dim](auto&& details) {
            details.second.erase(
              std::remove_if(details.second.begin(), details.second.end()
                , [pt=details.first,maze,&dim](auto d) { return ! is_inside_wall(maze, dim, Point{ pt.x + 2 * d.x, pt.y + 2 * d.y }); })
              , details.second.end());
          });
      // remove roads not having choices
      path_to_end.erase(
          std::remove_if(path_to_end.begin(), path_to_end.end(), [](auto&& details) { return details.second.empty(); })
          , path_to_end.end());
      // shuffle remaining roads
      std::shuffle(path_to_end.begin(), path_to_end.end(), g);
      continue;
    }

    auto d = choices.back();
    choices.pop_back();
    auto target = Point{ pt.x + 2 * d.x, pt.y + 2 * d.y };
    if (! is_inside_wall(maze, dim, target))
    {// this is not a possible path
      continue;
    }

    auto junction = Point{ pt.x + d.x, pt.y + d.y };
    maze[junction.y][junction.x] = to_char(MazeElement::Road);
    maze[target.y][target.x] = to_char(MazeElement::Road);

    auto next_choices = build_choices(maze, dim, target, is_inside_wall);
    std::shuffle(next_choices.begin(), next_choices.end(), g);
    if (! next_choices.empty())
    {
      path_to_end.emplace_back(target, std::move(next_choices));
    }    
  }
}

