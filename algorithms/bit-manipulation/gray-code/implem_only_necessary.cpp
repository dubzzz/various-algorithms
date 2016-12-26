#include <algorithm>
#include <iterator>
#include <vector>

// Algorithm to be tested

unsigned corresponding_pow(unsigned num)
{
  for ( ; (num & (num -1)) != 0 ; num &= num -1) {}
  return num;
}

std::vector<unsigned> build_grays(unsigned num)
{
  if (num == 0)
  {
    return {};
  }
  std::vector<unsigned> codes(1);
  codes.reserve(num);
  // Need to preallocate necessary memory in order to prevent from:
  // If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated. Otherwise only the past-the-end iterator is invalidated.
  
  unsigned corresponding = corresponding_pow(num);
  unsigned more = 1;
  while (codes.size() < corresponding)
  {
    std::transform(codes.rbegin(), codes.rend()
        , std::back_inserter(codes)
        , [more](auto prev){ return prev + more; });
    more <<= 1;
  }
  std::transform(codes.rbegin(), std::next(codes.rbegin(), num - corresponding)
      , std::back_inserter(codes)
      , [more](auto prev){ return prev + more; });
  return codes;
}

#include "tests.hpp"

