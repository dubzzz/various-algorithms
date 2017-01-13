#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

template <class Fun> auto build_sequence(Fun&& fun, std::size_t num, std::size_t init, unsigned long long uInit)
{
  std::vector<unsigned long long> vs(num);
  std::iota(vs.begin(), vs.end(), init);

  vs[0] = uInit;
  std::transform(vs.begin(), vs.end()-1, vs.begin()+1, vs.begin()+1, std::forward<Fun>(fun));
  return vs;
}

std::vector<unsigned long long> build_factorials(unsigned num)
{
  return num == 0
      ? std::vector<unsigned long long>{}
      : build_sequence([](auto&& n, auto&& prev) { return n * prev; }, num, 0, 1);
}

