#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

// http://www.programcreek.com/2012/12/leetcode-solution-of-single-number-in-java/
// Given an array of integers, every element appears twice except for one. Find that single one.

// Algorithm to be tested
// template <class It> auto find_unique(It&& beg, It&& end)

// Running tests

TEST(TEST_NAME, UniqueValue)
{
  std::vector<int> vs = { 42 };
  ASSERT_EQ(42, find_unique(std::begin(vs), std::end(vs)));
}

TEST(TEST_NAME, VariousValues)
{
  std::vector<int> vs = { 1, 2, 3, 3, 42, 1, 2 };
  ASSERT_EQ(42, find_unique(std::begin(vs), std::end(vs)));
}

RC_GTEST_PROP(TEST_NAME, RandomData, (const std::vector<int>& test, int answer, unsigned seed))
{
  std::vector<int> vs(test);
  std::copy(std::begin(test), std::end(test), std::back_inserter(vs));
  vs.push_back(answer);
  
  std::mt19937 g(seed);
  std::shuffle(std::begin(vs), std::end(vs), g);

  RC_ASSERT(answer == find_unique(std::begin(vs), std::end(vs)));
}

