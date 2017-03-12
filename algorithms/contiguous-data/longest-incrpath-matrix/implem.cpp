#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested
// Test based on BFS which is not a right idea at all for this kind of problem

using Location = std::pair<std::size_t, std::size_t>;

bool is_local_min(std::vector<std::vector<int>> const& matrix, std::size_t i, std::size_t j)
{
  const auto H = matrix.size();
  const auto W = matrix[0].size();
  const int& current = matrix[j][i];
  return (i == 0 || current <= matrix[j][i-1])
      && (j == 0 || current <= matrix[j-1][i])
      && (i == W-1 || current <= matrix[j][i+1])
      && (j == H-1 || current <= matrix[j+1][i]);
}

bool is_better(std::vector<std::vector<int>> const& matrix, std::size_t nx, std::size_t ny, std::size_t x, std::size_t y)
{
  const auto H = matrix.size();
  const auto W = matrix[0].size();
  return (nx < W && ny < H && matrix[y][x] < matrix[ny][nx]);
}

std::size_t longest_incr(std::vector<std::vector<int>> const& matrix)
{
  const auto H = matrix.size();
  const auto W = matrix[0].size();
  
  std::size_t remain_at_depth = 0;
  std::size_t next_depth = 0;
  std::size_t longest = 0;
  std::queue<Location> locations;
  
  // Push initial starting point
  // It is possible to take every point of the matrix
  // as starting locations
  // An optimized approch consist in starting by local minima
  for (std::size_t j {} ; j != H ; ++j)
  {
    for (std::size_t i {} ; i != W ; ++i)
    {
      if (is_local_min(matrix, i, j))
      {
        ++next_depth;
        locations.emplace(i, j);
      }
    }
  }
  
  while (! locations.empty())
  {
    if (! remain_at_depth)
    {
      remain_at_depth = next_depth;
      next_depth = 0;
      ++longest;
    }
    auto x = locations.front().first;
    auto y = locations.front().second;
    locations.pop();
    --remain_at_depth;
    
    // push possible paths from this point
    if (is_better(matrix, x-1, y, x, y))
    {
      ++next_depth;
      locations.emplace(x-1, y);
    }
    if (is_better(matrix, x+1, y, x, y))
    {
      ++next_depth;
      locations.emplace(x+1, y);
    }
    if (is_better(matrix, x, y-1, x, y))
    {
      ++next_depth;
      locations.emplace(x, y-1);
    }
    if (is_better(matrix, x, y+1, x, y))
    {
      ++next_depth;
      locations.emplace(x, y+1);
    }
  }
  
  return longest;
}

