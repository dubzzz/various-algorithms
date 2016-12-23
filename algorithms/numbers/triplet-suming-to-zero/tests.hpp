#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <climits>
#include <numeric>
#include <tuple>
#include <vector>

// Taken from http://www.programcreek.com/2012/12/leetcode-3sum/
// Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

// Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
// The solution set must not contain duplicate triplets.

// a+b+c overflows giving 0 are not considered as solutions

// Algorithm to be tested
// std::vector<td::tuple<int,int,int>> sum3(std::vector<int> const&)

// Running tests

TEST(TEST_NAME, InputItSelf)
{
  auto expected = std::make_tuple(-2, 1, 1);
  auto&& out = sum3({{ 1, -2, 1 }});
  ASSERT_EQ(1, out.size());
  ASSERT_TRUE(expected == out[0]);
}

TEST(TEST_NAME, OverflowReachingZeroIsInvalid)
{
  int b = -1097024319;
  int a = -b -b;
  ASSERT_TRUE(a < 0);
  auto&& out = sum3({{ b, b, a }});
  ASSERT_TRUE(out.size() == 0);
}

TEST(TEST_NAME, MultipleTriplets)
{
  std::vector<std::tuple<int,int,int>> expected = { std::tuple<int,int,int>{-1, 0, 1}, std::tuple<int,int,int>{-1, -1, 2} };
  auto&& out = sum3({{ -1, 0, 1, 2, -1, -4 }});
  ASSERT_EQ(2, out.size());
  ASSERT_TRUE(out[0] != out[1]);
  ASSERT_TRUE(expected[0] == out[0] || expected[0] == out[1]);
  ASSERT_TRUE(expected[1] == out[0] || expected[1] == out[1]);
}

RC_GTEST_PROP(TEST_NAME, SumToZero, (std::vector<int> const& in))
{
  RC_PRE(in.size() >= 3);
  auto&& out = sum3(in);
  RC_ASSERT(std::find_if_not(std::begin(out), std::end(out)
      , [](auto t) { return std::get<0>(t) + std::get<1>(t) + std::get<2>(t) == 0;
  }) == std::end(out));
}

RC_GTEST_PROP(TEST_NAME, Ordered, (std::vector<int> const& in))
{
  RC_PRE(in.size() >= 3);
  auto&& out = sum3(in);
  RC_ASSERT(std::find_if_not(std::begin(out), std::end(out)
      , [](auto t) { return std::get<0>(t) <= std::get<1>(t) && std::get<1>(t) <= std::get<2>(t);
  }) == std::end(out));
}

RC_GTEST_PROP(TEST_NAME, Unicity, (std::vector<int> const& in))
{
  RC_PRE(in.size() >= 3);
  auto&& out = sum3(in);
  std::sort(std::begin(out), std::end(out));
  RC_ASSERT(std::unique(std::begin(out), std::end(out)) == std::end(out));
}

RC_GTEST_PROP(TEST_NAME, ComeFromInput, (std::vector<int> const& in))
{
  RC_PRE(in.size() >= 3);
  auto&& out = sum3(in);
  auto sin = in;
  std::sort(std::begin(sin), std::end(sin));
  RC_ASSERT(std::find_if_not(std::begin(out), std::end(out)
      , [&sin](auto t) {
          auto it = std::find(std::begin(sin), std::end(sin), std::get<0>(t));
          it = std::find(it, std::end(sin), std::get<1>(t));
          return std::find(std::begin(sin), std::end(sin), std::get<2>(t)) != std::end(sin);
  }) == std::end(out));
}

bool same_sign(int a, int b)
{
  return (a < 0 && b < 0) || (a > 0 && b > 0);
}

RC_GTEST_PROP(TEST_NAME, FindAnswerWhenItExist, (std::vector<int> in, int a, int b))
{
  int c = -a -b;
  RC_PRE((a == 0 && b == 0 && c == 0) || !same_sign(a,b) || !same_sign(b,c) || !same_sign(c,a));

  int tab[] = {a, b ,c};
  std::sort(tab, tab+3);
  auto possible_answer = std::make_tuple(tab[0], tab[1], tab[2]);
  
  std::size_t pa = *rc::gen::inRange(std::size_t(), in.size());
  in.insert(std::next(std::begin(in), pa), a);
  std::size_t pb = *rc::gen::inRange(std::size_t(), in.size());
  in.insert(std::next(std::begin(in), pb), b);
  std::size_t pc = *rc::gen::inRange(std::size_t(), in.size());
  in.insert(std::next(std::begin(in), pc), c);
  
  auto&& out = sum3(in);
  RC_ASSERT(out.size());
  RC_ASSERT(std::find(std::begin(out), std::end(out), possible_answer) != std::end(out));
}

