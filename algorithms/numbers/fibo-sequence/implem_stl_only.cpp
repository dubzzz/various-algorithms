#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::vector<unsigned long long> build_fibos(unsigned num)
{
  if (num == 0)
  {
    return {};
  }
  std::vector<unsigned long long> vs(num, 1);
  std::adjacent_difference(vs.begin(), vs.end()-1, vs.begin()+1, std::plus<unsigned long long>());
  return vs;
}

