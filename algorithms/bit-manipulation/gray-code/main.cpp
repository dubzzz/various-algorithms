#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iterator>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, NoValue)
{
  std::vector<unsigned> expected = {  };
  ASSERT_EQ(expected, build_grays(0));
}

TEST(TEST_NAME, SpecificNumberOfValues)
{
  std::vector<unsigned> expected = { 0b000, 0b001, 0b011, 0b010, 0b110, 0b111, 0b101 };
  ASSERT_EQ(expected, build_grays(7));
}

RC_GTEST_PROP(TEST_NAME, RightNumberOfValues, (unsigned short N))
{
  RC_ASSERT(build_grays(N).size() == N);
}

RC_GTEST_PROP(TEST_NAME, AllEntriesAreUnique, (unsigned short N))
{
  auto&& out = build_grays(N);
  std::sort(std::begin(out), std::end(out));
  RC_ASSERT(std::adjacent_find(std::begin(out), std::end(out)) == std::end(out));
}

RC_GTEST_PROP(TEST_NAME, OneBitDifferBetweenTwoSuccessives, (unsigned short N))
{
  RC_PRE(N != (unsigned short()));
  auto&& out = build_grays(N);
  std::vector<std::pair<unsigned, unsigned>> successives;
  std::transform(std::begin(out), std::prev(std::end(out))
      , std::next(std::begin(out))
      , std::back_inserter(successives)
      , [](auto&& elt, auto&& next_elt) { return std::make_pair(elt, next_elt); });
  RC_ASSERT(std::find_if(std::begin(successives), std::end(successives)
      , [](auto&& entries) {
          auto n = entries.first ^ entries.second; // most be even
          return n & (n-1);
      }) == std::end(successives));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
