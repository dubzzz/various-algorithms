#include <cstddef>
#include <stack>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::size_t largest(std::vector<unsigned> const& in)
{
  // Space: O(n)
  // Time : O(n)
  
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

