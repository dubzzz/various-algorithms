#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

// Algorithm to be tested

std::vector<unsigned long long> build_factorials(unsigned num)
{
  if (num == 0)
  {
    return {};
  }
  std::vector<unsigned long long> vs(num);
  vs[0] = 1;
  std::iota(std::next(std::begin(vs)), std::end(vs), 1);
  std::transform(std::begin(vs), std::prev(std::end(vs))
      , std::next(std::begin(vs))
      , std::next(std::begin(vs))
      , std::multiplies<unsigned long long>());
  return vs;
}

#include "tests.hpp"

