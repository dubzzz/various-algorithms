#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

// Taken from http://www.programcreek.com/2014/07/leetcode-product-of-array-except-self-java/
// Given an array of n integers where n > 1, nums, return an array output such that
// output[i] is equal to the product of all the elements of nums except nums[i].
//
// Do not consider overflow issues
// Solve it without division and in O(n).
//
// For example, given [1,2,3,4], return [24,12,8,6].

// Algorithm to be tested
// std::vector<int> product_except(std::vector<int> const&)

// Running tests

TEST(TEST_NAME, OneElementArray)
{
  std::vector<int> expected { 1 };
  ASSERT_EQ(expected, product_except({ 42 }));
}

TEST(TEST_NAME, ExampleCase)
{
  std::vector<int> expected { 24, 12, 8, 6 };
  ASSERT_EQ(expected, product_except({{ 1, 2, 3, 4 }}));
}

RC_GTEST_PROP(TEST_NAME, HasSizeOfInput, (std::vector<int> in))
{
  RC_ASSERT(in.size() == product_except(in).size());
}

RC_GTEST_PROP(TEST_NAME, CheckValues, (std::vector<int> const& in))
{
  auto compute_without = [](auto tab, std::size_t without_id)
  {
    tab.erase(std::next(std::begin(tab), without_id));
    return std::accumulate(std::begin(tab), std::end(tab), 1, [](auto acc, auto cur) { return acc * cur; });
  };
  
  int n {};
  std::vector<int> expected;
  std::generate_n(std::back_inserter(expected), in.size(), [&](){ return compute_without(in, n++); });
  
  RC_ASSERT(expected == product_except(in));
}

