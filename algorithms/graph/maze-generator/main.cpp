#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <stack>
#include <utility>

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

bool has_path_to_end(Dimension const& dim, Point const& start_pt, char** grid)
{
  bool path_to_end {};
  std::stack<Point> toscan;
  toscan.push(start_pt);
  while (! path_to_end && ! toscan.empty())
  {
    Point pt = toscan.top();
    toscan.pop();
    
    auto append_point = [&path_to_end, &toscan, grid=grid](Point const& pt) {
        if (grid[pt.y][pt.x] == to_char(MazeElement::End))
        {
          path_to_end = true;
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
  return path_to_end;
}

RC_GTEST_PROP(TEST_NAME, AtLeastOnePathFromStartToEnd, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);

  RC_ASSERT(has_path_to_end(dim, start_pt, array2d.data()));
}

RC_GTEST_PROP(TEST_NAME, ExactlyOnePathFromStartToEnd, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);
  
  unsigned** nums = new unsigned*[dim.height]; // num paths starting at start and reaching this cell
  std::generate(nums, std::next(nums, dim.height)
      , [width=dim.width](){
        unsigned* line = new unsigned[width];
        std::fill(line, std::next(line, width), 0);
        return line;
  });
  
  std::stack<std::pair<Point, std::set<Point>>> toscan;
  toscan.emplace(start_pt, std::set<Point>{});
  while (! toscan.empty())
  {
    auto current = std::move(toscan.top());
    current.second.insert(current.first);
    toscan.pop();
    
    Point const& pt = current.first;
    std::set<Point> const& visited = current.second;
  
    ++nums[pt.y][pt.x];
    
    auto append_point = [&visited, &toscan, grid=array2d.data()](Point const& pt) {
        if (grid[pt.y][pt.x] != to_char(MazeElement::Wall) && visited.find(pt) == visited.end())
        {
          toscan.emplace(pt, visited);
        }
    };
    call_if(Point{pt.x-1, pt.y}, dim, append_point);
    call_if(Point{pt.x+1, pt.y}, dim, append_point);
    call_if(Point{pt.x, pt.y-1}, dim, append_point);
    call_if(Point{pt.x, pt.y+1}, dim, append_point);
  }
  RC_ASSERT(nums[end_pt.y][end_pt.x] == unsigned(1));
  
  std::for_each(nums, std::next(nums, dim.height), [](unsigned* line) { delete[] line; });
  delete[] nums;
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

RC_GTEST_PROP(TEST_NAME, NotTooManyWalls, (unsigned seed))
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
}

RC_GTEST_PROP(TEST_NAME, NotTooManyPaths, (unsigned seed))
{
  auto dim = *rc::gen::arbitrary<Dimension>();
  auto start_pt = *random_point(dim);
  auto end_pt = *random_point(dim);
  RC_PRE(start_pt != end_pt);

  Array2D array2d(dim);
  generate_maze(array2d.data(), dim, start_pt, end_pt, seed);
  
  for (std::size_t j {} ; j != dim.height ; ++j)
  {
    for (std::size_t i {} ; i != dim.width ; ++i)
    {
      if (array2d.data()[j][i] == to_char(MazeElement::Wall)) continue;
      
      unsigned paths_in_block {};
      auto count_paths_in_block = [&paths_in_block, grid=array2d.data()](Point const& pt) { if (grid[pt.y][pt.x] != to_char(MazeElement::Wall)) ++paths_in_block; };
      
      call_if(Point{i  ,j+1}, dim, count_paths_in_block);
      call_if(Point{i+1,  j}, dim, count_paths_in_block);
      call_if(Point{i+1,j+1}, dim, count_paths_in_block);
      
      RC_ASSERT(paths_in_block != unsigned(3));
    }
  }
}

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

