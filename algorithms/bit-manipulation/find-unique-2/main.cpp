#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

// http://www.programcreek.com/2014/03/leetcode-single-number-ii-java/
// Given an array of integers, every element appears three times except for one. Find that single one.

// Algorithm to be tested

template <class It> auto find_unique(It&& beg, It&& end)
{
  using value_type = typename std::iterator_traits<It>::value_type;
  //constexpr unsigned num_bytes = 8 * sizeof(value_type);
  return std::accumulate(
      std::forward<It>(beg)
      , std::forward<It>(end), std::make_pair(value_type(), value_type())
      , [](auto&& acc, auto&& cur)
      {
        /*std::cout << "Bits equal to 1: " << std::cout.widen('\n');
        std::cout << "    0 mod 3 times: " << std::bitset<num_bytes>(~(acc.first | acc.second)) << std::cout.widen('\n');
        std::cout << "    1 mod 3 times: " << std::bitset<num_bytes>(acc.first) << std::cout.widen('\n');
        std::cout << "    2 mod 3 times: " << std::bitset<num_bytes>(acc.second) << std::cout.widen('\n');
        std::cout << "Input:             " << std::bitset<num_bytes>(cur) << std::cout.widen('\n') << std::endl;*/
        return std::make_pair(~acc.second & (acc.first ^ cur), (acc.second & ~cur) | (acc.first & cur));
      }).first;
}

#define ALGO FindUnique_DEFAULT

// Running tests

TEST(ALGO, UniqueValue)
{
  std::vector<int> vs = { 42 };
  ASSERT_EQ(42, find_unique(std::begin(vs), std::end(vs)));
}

TEST(ALGO, VariousValues)
{
  std::vector<int> vs = { 1, 2, 1, 3, 3, 3, 42, 1, 2, 2 };
  ASSERT_EQ(42, find_unique(std::begin(vs), std::end(vs)));
}

RC_GTEST_PROP(ALGO, RandomData, (const std::vector<int>& test, int answer, unsigned seed))
{
  std::vector<int> vs(test);
  std::copy(std::begin(test), std::end(test), std::back_inserter(vs));
  std::copy(std::begin(test), std::end(test), std::back_inserter(vs));
  vs.push_back(answer);
  
  std::mt19937 g(seed);
  std::shuffle(std::begin(vs), std::end(vs), g);

  RC_ASSERT(answer == find_unique(std::begin(vs), std::end(vs)));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

