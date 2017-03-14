#include <algorithm>
#include <cstddef>
#include <stack>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

static std::size_t largest_in_histogram(std::vector<unsigned> const& in)
{
  // Space: O(N)
  // Time : O(N)
  
  std::size_t max_size = 0;
  std::stack<unsigned> prev;
  for (std::size_t idx {} ; idx != in.size() ; ++idx)
  {
    while (! prev.empty() && in[prev.top()] > in[idx])
    {
      auto t = prev.top();
      prev.pop();
      max_size = std::max(max_size, in[t] * (idx  - t));
    }
    prev.push(idx);
  }
  while (! prev.empty())
  {
    auto t = prev.top();
    prev.pop();
    max_size = std::max(max_size, in[t] * (in.size() - t));
  }
  return max_size;
}

std::size_t largest_area(std::vector<std::vector<bool>> const& matrix)
{
  // Complexity in average:
  //  Space: O(M)
  //  Time : O(N * M)
  // With M = matrix[0].size()
  //  and N = matrix.size()
  
  // This implementation is totally based on the rectangle in histogram problem
  
  std::size_t max_area = 0;
  std::vector<unsigned> histogram(matrix[0].size());
  for (auto const& line : matrix)
  {
    // histogram contains the histogram corresponding to line taken as baseline
    for (std::size_t idx {} ; idx != line.size() ; ++idx)
    {
      if (line[idx]) ++histogram[idx];
      else histogram[idx] = 0;
    }
    max_area = std::max(max_area, largest_in_histogram(histogram));
  }
  return max_area;
}
