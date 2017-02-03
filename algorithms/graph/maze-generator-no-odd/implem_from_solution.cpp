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
  const char wall { to_char(MazeElement::Wall) };
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
  auto current = Point{ start_pt };
  auto choices = build_choices(maze, dim, current, is_inside_wall);
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
    
    std::uniform_int_distribution<std::size_t> dist(0, choices.size()-1);
    std::size_t selected_idx { dist(g) };
    Delta d { choices[selected_idx] };
    choices.erase(choices.begin() + selected_idx);

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
  }
  
  // Put start and end
  maze[start_pt.y][start_pt.x] = to_char(MazeElement::Start);
  maze[end_pt.y][end_pt.x] = to_char(MazeElement::End);
}

