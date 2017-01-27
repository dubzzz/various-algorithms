#include <algorithm>
#include <random>
#include <vector>

#include "aim.hpp"
#include "maze.hpp"

// Algorithm to be tested

template <class RandGen> bool generate_maze_helper(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt, RandGen& g)
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
  
  // Put start and end
  maze[start_pt.y][start_pt.x] = to_char(MazeElement::Start);
  maze[end_pt.y  ][end_pt.x  ] = to_char(MazeElement::End);
  
  // Random journey in the grid
  std::vector<Point> toscan;
  
  auto is_end = [width,height,maze](Point const& pt) { return pt.x < width && pt.y < height && maze[pt.y][pt.x] == to_char(MazeElement::End); };
  auto is_notwall = [width,height,maze](Point const& pt) { return pt.x < width && pt.y < height && maze[pt.y][pt.x] != to_char(MazeElement::Wall); };
  
  auto is_next_to_end = [&is_end](Point const& pt) { return is_end(Point{pt.x, pt.y-1}) || is_end(Point{pt.x, pt.y+1}) || is_end(Point{pt.x-1, pt.y}) || is_end(Point{pt.x+1, pt.y}); };
  
  auto append_if_wall = [&toscan,width,height,maze](Point const& pt) { if (pt.x < width && pt.y < height && maze[pt.y][pt.x] == to_char(MazeElement::Wall)) { toscan.push_back(pt); } };
  auto append_neighboors = [&append_if_wall,&g,&toscan,maze](Point const& pt) {
      auto before = toscan.size();
      append_if_wall(Point{pt.x-1,   pt.y});
      append_if_wall(Point{pt.x+1,   pt.y});
      append_if_wall(Point{pt.x  , pt.y-1});
      append_if_wall(Point{pt.x  , pt.y+1});
      std::shuffle(toscan.rbegin(), std::next(toscan.rbegin(), toscan.size() - before), g);
  };
  append_neighboors(start_pt);
  
  bool reached_end { is_next_to_end(start_pt) };
  while (! toscan.empty())
  {
    Point last = toscan.back();
    toscan.pop_back();
    
    if (maze[last.y][last.x] != to_char(MazeElement::Wall)) { continue; }
    
    unsigned num_roads {};
    if (is_notwall(Point{last.x  , last.y-1})) { ++num_roads; }
    if (is_notwall(Point{last.x  , last.y+1})) { ++num_roads; }
    if (is_notwall(Point{last.x-1,   last.y})) { ++num_roads; }
    if (is_notwall(Point{last.x+1,   last.y})) { ++num_roads; }
    
    bool invalid_choice = (num_roads > 2);
    if (num_roads == 2)
    {
      if (reached_end) invalid_choice = true;
      else
      {
        reached_end = is_next_to_end(last);
        invalid_choice = !reached_end;
      }
    }
    
    if (invalid_choice)
    {// we reach the end of ongoing path -- cleaning and shuffling of previously possible points
      toscan.erase(
          std::remove_if(toscan.begin(), toscan.end(), [maze](auto const& pt) { return maze[pt.y][pt.x] != to_char(MazeElement::Wall); })
          , toscan.end());
      std::shuffle(toscan.begin(), toscan.end(), g);
      continue;
    }
    
    maze[last.y][last.x] = to_char(MazeElement::Road);
    append_neighboors(last);
  }
  return reached_end;
}

bool removed_enough_walls(char** maze, Dimension const& dim)
{
  auto call_if = [](Point const& pt, Dimension const& dim, auto&& fun) {
      if (pt.x < dim.width && pt.y < dim.height) { fun(pt); }
  };
  
  for (std::size_t j {} ; j != dim.height ; ++j)
  {
    for (std::size_t i {} ; i != dim.width ; ++i)
    {
      if (maze[j][i] != to_char(MazeElement::Wall)) continue;
      
      unsigned walls_in_block {};
      auto count_walls_in_block = [&walls_in_block, maze](Point const& pt) { if (maze[pt.y][pt.x] == to_char(MazeElement::Wall)) ++walls_in_block; };
      
      call_if(Point{i-1,j-1}, dim, count_walls_in_block);
      call_if(Point{i-1,  j}, dim, count_walls_in_block);
      call_if(Point{i-1,j+1}, dim, count_walls_in_block);
      call_if(Point{i  ,j-1}, dim, count_walls_in_block);
      call_if(Point{i  ,j+1}, dim, count_walls_in_block);
      call_if(Point{i+1,j-1}, dim, count_walls_in_block);
      call_if(Point{i+1,  j}, dim, count_walls_in_block);
      call_if(Point{i+1,j+1}, dim, count_walls_in_block);
      
      if (walls_in_block == 8)
      {
        return false;
      }
    }
  }
  return true;
}

void generate_maze(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt, unsigned seed)
{
  std::mt19937 g(seed);
  
  bool correct {};
  while (! correct)
  {
    correct = generate_maze_helper(maze, dim, start_pt, end_pt, g) && removed_enough_walls(maze, dim);
  }
}

