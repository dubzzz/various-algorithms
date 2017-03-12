#include <cstddef>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::vector<int> r_rotate(std::vector<int> const& in, std::size_t k)
{
  // Space: O(n)
  // Time : O(n)

  // Note: because modulo is an expensive operation, we can maybe split the code into two loops
  //       one for the first elements of out, the other for the remaining
  
  std::vector<int> out = in;
  for (std::size_t idx {} ; idx != in.size() ; ++idx)
  {
    out[(idx+k)%in.size()] = in[idx];
  }
  return out;
}

