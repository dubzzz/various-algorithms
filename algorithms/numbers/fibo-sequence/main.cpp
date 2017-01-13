#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

#include SPECIFIC_HEADER

unsigned max_entries()
{
  unsigned long long a { 1 };
  unsigned long long b { 1 };
  unsigned count { 2 };
  while (++count)
  {
    if (std::numeric_limits<unsigned long long>::max() - b < a)
    {
      return count -1;
    }
    unsigned long long c = a + b;
    a = b;
    b = c;
  }
  return 0;
}

// Running tests

TEST(TEST_NAME, NoValue)
{
  std::vector<unsigned long long> expected = {  };
  ASSERT_EQ(expected, build_fibos(0));
}

TEST(TEST_NAME, SpecificNumberOfValues)
{
  std::vector<unsigned long long> expected = { 1, 1, 2, 3, 5, 8, 13 };
  ASSERT_EQ(expected, build_fibos(7));
}

RC_GTEST_PROP(TEST_NAME, RightNumberOfValues, ())
{
  unsigned N = *rc::gen::inRange(unsigned(), max_entries());
  RC_ASSERT(build_fibos(N).size() == N);
}

RC_GTEST_PROP(TEST_NAME, IncrementsAreHigherAndHigher, ())
{
  unsigned N = *rc::gen::inRange(unsigned(1), max_entries());
  auto&& out = build_fibos(N);
  std::vector<unsigned long long> factors;
  std::transform(std::begin(out), std::prev(std::end(out))
      , std::next(std::begin(out))
      , std::back_inserter(factors)
      , [](auto&& elt, auto&& next_elt) { return next_elt - elt; });
  RC_ASSERT(std::is_sorted(std::begin(factors), std::end(factors)));
}

RC_GTEST_PROP(TEST_NAME, FormulaWellApplied, ())
{
  unsigned N = *rc::gen::inRange(unsigned(2), max_entries());
  auto&& out = build_fibos(N);
  for (std::size_t idx {2} ; idx != out.size() ; ++idx)
  {
    RC_ASSERT(out[idx] == out[idx-1] + out[idx-2]);
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

