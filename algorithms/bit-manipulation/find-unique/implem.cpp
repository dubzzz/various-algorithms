#include <iterator>
#include <numeric>

// Algorithm to be tested

template <class It> auto find_unique(It&& beg, It&& end)
{
  using value_type = typename std::iterator_traits<It>::value_type;
  return std::accumulate(beg, end, value_type(), [](auto&& acc, auto&& cur) { acc ^= cur; return acc; });
}

#include "tests.hpp"

