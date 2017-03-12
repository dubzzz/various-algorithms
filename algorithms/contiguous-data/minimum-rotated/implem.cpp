#include <vector>

#include "aim.hpp"

// Algorithm to be tested

int min_rotated_helper(std::vector<int> const& in, std::size_t lo, std::size_t hi)
{
  if (lo >= hi) return in[lo];
  
  std::size_t mid = lo + (hi - lo)/2;
  if (in[mid] < in[lo]) return min_rotated_helper(in, lo+1, mid);
  else if (in[mid] > in[hi]) return min_rotated_helper(in, mid+1, hi);
  else if (in[lo] < in[hi]) return in[lo]; // eq. in[mid] != in[lo] || in[mid] != in[hi]
  
  while (lo < mid && in[lo] == in[mid]) { ++lo; }
  while (hi > mid && in[hi] == in[mid]) { --hi; }
  return min_rotated_helper(in, lo, hi);
}

int min_rotated(std::vector<int> const& in)
{
  return min_rotated_helper(in, 0, in.size() -1);
}

