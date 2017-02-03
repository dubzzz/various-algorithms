#include <iostream>
#include <random>

#include "array2d.hpp"
#include "maze.hpp"
#include SPECIFIC_HEADER

int main()
{
  auto dim = Dimension{79,79};
  auto start_pt = Point{0,0};
  auto end_pt = Point{78,78};

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, std::random_device{}());
  array2d.print(std::cout);
  
  return array2d.data()[start_pt.y][start_pt.x] == to_char(MazeElement::Start)
      && array2d.data()[end_pt.y][end_pt.x] == to_char(MazeElement::End);
}

