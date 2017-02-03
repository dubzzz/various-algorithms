#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "aim.hpp"
#include "maze.hpp"

struct Delta
{
  int x, y;
  Delta(int x, int y) : x(x), y(y) {}
};

// Algorithm to be tested

void generate_maze(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt, unsigned seed)
{
  auto const& width = dim.width;
  auto const& height = dim.height;
  if (height * width >= 100) return;
  
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
  
  auto is_inside = [width,height](char** /*maze*/, Point const& pt) { return pt.x < width && pt.y < height; };
  auto is_wall   = [](char** maze, Point const& pt) { return maze[pt.y][pt.x] == to_char(MazeElement::Wall); };
  auto is_inside_wall = [&is_inside,&is_wall](char** maze, Point const& pt) { return is_inside(maze, pt) && is_wall(maze, pt); };
  
  auto push_if = [](auto& container, char** maze, Point const& pt, Delta const& delta, auto&& predicate) {
      if (predicate(maze, Point{pt.x + 2*delta.x, pt.y + 2*delta.y})) { container.push_back(delta); }
  };
  auto build_choices = [&push_if](char** maze, Point const& pt, auto&& predicate) {
    std::vector<Delta> choices;
    push_if(choices, maze, pt, Delta{-1, 0}, predicate);
    push_if(choices, maze, pt, Delta{ 1, 0}, predicate);
    push_if(choices, maze, pt, Delta{ 0,-1}, predicate);
    push_if(choices, maze, pt, Delta{ 0, 1}, predicate);
    return choices;
  };
  
  std::vector<std::pair<Point, std::vector<Delta>>> path_to_end;
  auto current = Point{ start_pt };
  auto choices = build_choices(maze, current, is_inside_wall);
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
    
    // current decision
    path_to_end.emplace_back(current, std::move(choices));
    maze[current.y][current.x] = to_char(MazeElement::Road);
    
    // junction road
    current = Point{ current.x + d.x, current.y + d.y };
    path_to_end.emplace_back(current, decltype(choices){});
    maze[current.y][current.x] = to_char(MazeElement::Road);
    
    // next position
    current = Point{ current.x + d.x, current.y + d.y };
    choices = build_choices(maze, current, is_inside_wall);
  }
  
  // Put start and end
  maze[start_pt.y][start_pt.x] = to_char(MazeElement::Start);
  maze[end_pt.y][end_pt.x] = to_char(MazeElement::End);
}

