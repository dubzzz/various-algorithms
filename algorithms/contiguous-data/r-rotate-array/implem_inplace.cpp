#include <cstddef>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

static std::size_t gcd(std::size_t a, std::size_t b)
{
  while (b != 0)
  {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

std::vector<int> r_rotate(std::vector<int> const& in_, std::size_t k)
{
  // Space: O(1)
  // Time : O(n)
  
  // We start from the simple case of k=1:
  // in this case in[i+1] <- in[i] and we need to keep in mind the value of in[i+1]
  // in order to put it into in[i+2]...
  
  // We will apply the very same process replacing +1 by +k
  // However i+0, i+k, i+2k... can omit some elements depending on the gcd of in.size() and k
  // Indeed i+0,... will initialize the terms i, i+g, i+2g, i+3g... where g is the gcd
  // we need to apply such pattern g times in order to rotate the whole array inplace
  
  if (in_.empty()) { return in_; }
  
  std::vector<int> in = in_;
  std::size_t g = gcd(k, in.size());
  
  for (std::size_t idx {} ; idx != g ; ++idx)
  {
    int prev_val = in[idx];
    std::size_t cidx = (idx+k) % in.size();
    while (cidx != idx)
    {
      int cur_val = in[cidx];
      in[cidx] = prev_val;
      prev_val = cur_val;
      cidx = (cidx+k) % in.size();
    }
    in[idx] = prev_val;
  }
  return in;
}

