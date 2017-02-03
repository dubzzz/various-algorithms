#include <algorithm>
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
  
  // Random journey in the grid
  std::mt19937 g(seed);
  std::vector<Point> toscan;
  
  auto is_inside = [width,height](char** /*maze*/, Point const& pt) { return pt.x < width && pt.y < height; };
  auto is_wall   = [](char** maze, Point const& pt) { return maze[pt.y][pt.x] == to_char(MazeElement::Wall); };
  auto is_inside_wall = [&is_inside,&is_wall](char** maze, Point const& pt) { return is_inside(maze, pt) && is_wall(maze, pt); };
  
  auto push_if = [&toscan](char** maze, Point const& pt, Delta const& delta, auto&& predicate) {
      if (predicate(maze, Point{pt.x + 2*delta.x, pt.y + 2*delta.y}))
      {
        toscan.push_back(Point{pt.x + delta.x, pt.y + delta.y});
        return 1;
      }
      return 0;
  };
  auto compute_direction = [&is_wall](char**maze, Point const& pt) {//hypothesis: pt.x%2==0 ^ pt.y%2==0
      if (pt.x % 2 == 0)// we move along y axis keeping x constant, both y-1 and y+1 exist
        return !is_wall(maze, Point{pt.x, pt.y-1}) ? Delta{0,1} : Delta{0,-1};
      return !is_wall(maze, Point{pt.x-1, pt.y}) ? Delta{1,0} : Delta{-1,0};
  };
  
  // When at start point we know that are immediate neighboors
  // cannot be something else than walls (or outside the map)
  push_if(maze, start_pt, Delta{-1,  0}, is_inside);
  push_if(maze, start_pt, Delta{ 1,  0}, is_inside);
  push_if(maze, start_pt, Delta{ 0, -1}, is_inside);
  push_if(maze, start_pt, Delta{ 0,  1}, is_inside);
  std::shuffle(toscan.begin(), toscan.end(), g);
  
  bool found_the_end {};
  bool last_failed {};
  while (! toscan.empty())
  {
    Point pt = toscan.back();
    toscan.pop_back();
    
    // pt always satisfy
    // (pt.x % 2 != 0 && pt.y % 2 == 0) || (pt.x % 2 == 0 && pt.y % 2 != 0)
    // we are on an intermediate point and will build the road until the next valid point
    Delta delta { compute_direction(maze, pt) };
    Point valid_pt { pt.x + delta.x, pt.y + delta.y };
    bool goes_to_end { (valid_pt.x == end_pt.x) && (valid_pt.y == end_pt.y) };
    
    if (! is_wall(maze, valid_pt) || (found_the_end && goes_to_end))
    {// this direction is not valid anymore, it reaches an already visited zone
      if (! last_failed)
      {
        last_failed = true;
        std::shuffle(toscan.begin(), toscan.end(), g);
      }
      continue;
    }
    found_the_end |= goes_to_end;
    
    // point is valid, we build the path
    last_failed = false; // used to avoid running mutliple consecutive shuffles on the full array
    maze[pt.y][pt.x] = to_char(MazeElement::Road);
    maze[valid_pt.y][valid_pt.x] = to_char(MazeElement::Road);
    if (goes_to_end)
    {
      std::shuffle(toscan.begin(), toscan.end(), g);
      continue;
    }
     
    // push valid neighboors
    unsigned num_added {};
    num_added += push_if(maze, valid_pt, Delta{-1,  0}, is_inside_wall);
    num_added += push_if(maze, valid_pt, Delta{ 1,  0}, is_inside_wall);
    num_added += push_if(maze, valid_pt, Delta{ 0, -1}, is_inside_wall);
    num_added += push_if(maze, valid_pt, Delta{ 0,  1}, is_inside_wall);
    std::shuffle(toscan.rbegin(), std::next(toscan.rbegin(), num_added), g);
  }
  maze[end_pt.y][end_pt.x] = to_char(MazeElement::End);
}


