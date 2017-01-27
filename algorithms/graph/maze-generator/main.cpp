#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <stack>

#include "array2d.hpp"
#include "maze.hpp"
#include SPECIFIC_HEADER

// Running tests

constexpr std::size_t max_dim { 50 };

namespace rc {

template<> struct Arbitrary<Dimension>
{
  static Gen<Dimension> arbitrary()
  {
    return gen::build<Dimension>(
        gen::set(&Dimension::width, gen::inRange(std::size_t(2), max_dim)),
        gen::set(&Dimension::height, gen::inRange(std::size_t(2), max_dim)));
  }
};

} // namespce rc

std::ostream& operator<<(std::ostream& oss, Dimension const& dim) { return (oss << "{width: " << dim.width << ", height: " << dim.height << "}"); }
std::ostream& operator<<(std::ostream& oss, Point const& pt) { return (oss << "{x: " << pt.x << ", y: " << pt.y << "}"); }

auto random_point(Dimension const& dim)
{
  return rc::gen::apply([](std::size_t x, std::size_t y) { return Point{x,y}; }
      , rc::gen::inRange(std::size_t(), dim.width), rc::gen::inRange(std::size_t(), dim.height));
}

RC_GTEST_PROP(TEST_NAME, UniqueStart, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);
  
  RC_ASSERT(array2d.data()[start_pt.y][start_pt.x] == to_char(MazeElement::Start));
  RC_ASSERT(std::count(array2d.begin(), array2d.end(), to_char(MazeElement::Start)) == std::ptrdiff_t(1));
}

RC_GTEST_PROP(TEST_NAME, UniqueEnd, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);
  
  RC_ASSERT(array2d.data()[end_pt.y][end_pt.x] == to_char(MazeElement::End));
  RC_ASSERT(std::count(array2d.begin(), array2d.end(), to_char(MazeElement::End)) == std::ptrdiff_t(1));
}

RC_GTEST_PROP(TEST_NAME, OnlyMazeElements, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);
  
  RC_ASSERT(std::find_if_not(
      array2d.begin(), array2d.end()
      , [](char c) { return c == to_char(MazeElement::Wall) || c == to_char(MazeElement::Road) || c == to_char(MazeElement::Start) || c == to_char(MazeElement::End); }) == array2d.end());
}

template <class Fun> void call_if(Point const& pt, Dimension const& dim, Fun&& callback)
{
  if (pt.x < dim.width && pt.y < dim.height) // -1 is larger than dim.width or dim.height
  {
    callback(pt);
  }
}

template <class EndCondition> unsigned count_paths_to_end(Dimension const& dim, Point const& start_pt, char** grid, EndCondition&& fun)
{
  unsigned num_paths {};
  std::stack<Point> toscan;
  toscan.push(start_pt);
  while (! fun(num_paths) && ! toscan.empty())
  {
    Point pt = toscan.top();
    toscan.pop();
    
    auto append_point = [&num_paths, &toscan, grid=grid](Point const& pt) {
        if (grid[pt.y][pt.x] == to_char(MazeElement::End))
        {
          ++num_paths;
        }
        else if (grid[pt.y][pt.x] == to_char(MazeElement::Road))
        {
          toscan.push(pt);
          grid[pt.y][pt.x] = to_char(MazeElement::Undefined);
        }
    };
    call_if(Point{pt.x-1, pt.y}, dim, append_point);
    call_if(Point{pt.x+1, pt.y}, dim, append_point);
    call_if(Point{pt.x, pt.y-1}, dim, append_point);
    call_if(Point{pt.x, pt.y+1}, dim, append_point);
  }
  return num_paths;
}

RC_GTEST_PROP(TEST_NAME, AtLeastOnePathFromStartToEnd, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);

  RC_ASSERT(count_paths_to_end(dim, start_pt, array2d.data(), [](unsigned num) { return !!num; }) > unsigned());
}

RC_GTEST_PROP(TEST_NAME, ExactlyOnePathFromStartToEnd, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);

  RC_ASSERT(count_paths_to_end(dim, start_pt, array2d.data(), [](unsigned) { return false; }) == unsigned(1));
}

RC_GTEST_PROP(TEST_NAME, OnlyOneRoadLeavesEnd, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);

  unsigned road_leaving {};
  auto count_roads = [&road_leaving, grid=array2d.data()](Point const& pt) { if (grid[pt.y][pt.x] != to_char(MazeElement::Wall)) ++road_leaving; };
  
  auto const& i = end_pt.x;
  auto const& j = end_pt.y;
  
  call_if(Point{i-1,  j}, dim, count_roads);
  call_if(Point{i  ,j-1}, dim, count_roads);
  call_if(Point{i  ,j+1}, dim, count_roads);
  call_if(Point{i+1,  j}, dim, count_roads);
  
  RC_ASSERT(road_leaving == unsigned(1));
}

/*RC_GTEST_PROP(TEST_NAME, NotTooManyWalls, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  RC_PRE(dim.width >= std::size_t(4)); // in order to fullfill OnlyOneRoadLeavesEnd this property needs larger maze
  RC_PRE(dim.height >= std::size_t(4));
  
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);
  
  for (std::size_t j {} ; j != dim.height ; ++j)
  {
    for (std::size_t i {} ; i != dim.width ; ++i)
    {
      if (array2d.data()[j][i] != to_char(MazeElement::Wall)) continue;
      
      unsigned walls_in_block {};
      auto count_walls_in_block = [&walls_in_block, grid=array2d.data()](Point const& pt) { if (grid[pt.y][pt.x] == to_char(MazeElement::Wall)) ++walls_in_block; };
      
      call_if(Point{i-1,j-1}, dim, count_walls_in_block);
      call_if(Point{i-1,  j}, dim, count_walls_in_block);
      call_if(Point{i-1,j+1}, dim, count_walls_in_block);
      call_if(Point{i  ,j-1}, dim, count_walls_in_block);
      call_if(Point{i  ,j+1}, dim, count_walls_in_block);
      call_if(Point{i+1,j-1}, dim, count_walls_in_block);
      call_if(Point{i+1,  j}, dim, count_walls_in_block);
      call_if(Point{i+1,j+1}, dim, count_walls_in_block);
      
      RC_ASSERT(walls_in_block != unsigned(8));
    }
  }
}*/

RC_GTEST_PROP(TEST_NAME, AllRoadsAreAccessible, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);
  
  std::stack<Point> toscan;
  toscan.push(start_pt);
  while (! toscan.empty())
  {
    Point pt = toscan.top();
    toscan.pop();
    
    auto append_point = [&toscan, grid=array2d.data()](Point const& pt) {
        if (grid[pt.y][pt.x] == to_char(MazeElement::End) || grid[pt.y][pt.x] == to_char(MazeElement::Road))
        {
          toscan.push(pt);
          grid[pt.y][pt.x] = to_char(MazeElement::Undefined);
        }
    };
    call_if(Point{pt.x-1, pt.y}, dim, append_point);
    call_if(Point{pt.x+1, pt.y}, dim, append_point);
    call_if(Point{pt.x, pt.y-1}, dim, append_point);
    call_if(Point{pt.x, pt.y+1}, dim, append_point);
  }

  RC_ASSERT(std::find(array2d.begin(), array2d.end(), to_char(MazeElement::Road)) == array2d.end());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

