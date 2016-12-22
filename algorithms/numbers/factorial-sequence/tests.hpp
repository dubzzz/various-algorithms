#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

// Build a std::vector<unsigned> containing the N first factorial values starting from 0!...

// Algorithm to be tested
// std::vector<unsigned long long> build_factorials(unsigned N)

unsigned max_entries()
{
  unsigned long long current { 1 };
  unsigned factor { 1 };
  while (++factor)
  {
    auto previous = std::exchange(current, factor * current);
    if (current / previous != factor || current % previous != 0 || current < previous)
    {
      return factor -1;
    }
  }
  return 0;
}

// Running tests

TEST(TEST_NAME, NoValue)
{
  std::vector<unsigned long long> expected = {  };
  ASSERT_EQ(expected, build_factorials(0));
}

TEST(TEST_NAME, SpecificNumberOfValues)
{
  std::vector<unsigned long long> expected = { 1, 1, 2, 6, 24, 120, 720 };
  ASSERT_EQ(expected, build_factorials(7));
}

RC_GTEST_PROP(TEST_NAME, RightNumberOfValues, ())
{
  unsigned N = *rc::gen::inRange(unsigned(), max_entries());
  RC_ASSERT(build_factorials(N).size() == N);
}

RC_GTEST_PROP(TEST_NAME, MultipleOfPreviousEntry, ())
{
  unsigned N = *rc::gen::inRange(unsigned(1), max_entries());
  auto&& out = build_factorials(N);
  std::vector<std::pair<unsigned long long, unsigned long long>> successives;
  std::transform(std::begin(out), std::prev(std::end(out))
      , std::next(std::begin(out))
      , std::back_inserter(successives)
      , [](auto&& elt, auto&& next_elt) { return std::make_pair(elt, next_elt); });
  RC_ASSERT(std::find_if(std::begin(successives), std::end(successives)
      , [](auto&& entries) {
          return (entries.second % entries.first) != 0;
      }) == std::end(successives));
}

RC_GTEST_PROP(TEST_NAME, IncrementingListOfFactors, ())
{
  unsigned N = *rc::gen::inRange(unsigned(1), max_entries());
  auto&& out = build_factorials(N);
  std::vector<unsigned long long> factors;
  std::transform(std::begin(out), std::prev(std::end(out))
      , std::next(std::begin(out))
      , std::back_inserter(factors)
      , [](auto&& elt, auto&& next_elt) { return next_elt / elt; });
  std::vector<unsigned long long> expected(N -1);
  std::iota(std::begin(expected), std::end(expected), 1);
  RC_ASSERT(expected == factors);
}

