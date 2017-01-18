#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <tuple>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, SumGreater)
{
  ASSERT_EQ(2, closest_3sum(1, {-1, 2, 1, -4}));
}

TEST(TEST_NAME, SumEqual)
{
  ASSERT_EQ(1, closest_3sum(1, {-1, 2, 9, -4, -10}));
}

TEST(TEST_NAME, SumLess)
{
  ASSERT_EQ(10, closest_3sum(11, {-1, 2, 9, -4, -10}));
}

template <class IntType> bool overflow(IntType a, IntType b)
{
  return (a > 0 && std::numeric_limits<IntType>::max() -a < b)
      || (a < 0 && std::numeric_limits<IntType>::min() -a > b);
}
template <class IntType> bool overflow(IntType a, IntType b, IntType c)
{
  return a <= b && b <= c
      ? overflow(a,c) || overflow(a+c, b)
      : (a > b ? overflow(b,a,c) : overflow(a,c,b));
}

RC_GTEST_PROP(TEST_NAME, ExactSumCanBeFound, (std::vector<int> const& in))
{
  RC_PRE(in.size() >= unsigned(3));
  
  std::vector<int> cpin = in;
  std::size_t N = cpin.size();
  std::sort(cpin.begin(), cpin.end());
  RC_PRE(!overflow(cpin[0], cpin[1], cpin[2]));
  RC_PRE(!overflow(cpin[N-3], cpin[N-2], cpin[N-1]));
  
  int possible_sum = *rc::gen::apply([&in](unsigned seed)
        {
          std::mt19937 g(seed);
          auto cin = in;
          std::shuffle(cin.begin(), cin.end(), g);
          return cin[0]+cin[1]+cin[2];
        }
        , rc::gen::arbitrary<unsigned>())
      .as("possible sum");
  
  RC_ASSERT(closest_3sum(possible_sum, in) == possible_sum);
}

RC_GTEST_PROP(TEST_NAME, AskForLessThanMinSum, (std::vector<int> const& in))
{
  RC_PRE(in.size() >= unsigned(3));
  
  std::vector<int> cpin = in;
  std::size_t N = cpin.size();
  std::sort(cpin.begin(), cpin.end());
  RC_PRE(!overflow(cpin[0], cpin[1], cpin[2]));
  RC_PRE(!overflow(cpin[N-3], cpin[N-2], cpin[N-1]));
  
  auto min_possible_sum = cpin[0] + cpin[1] + cpin[2];
  auto delta = *rc::gen::inRange(std::numeric_limits<int>::min(), 1);
  RC_PRE(!overflow(min_possible_sum, delta));
  
  RC_ASSERT(closest_3sum(min_possible_sum + delta, in) == min_possible_sum);
}

RC_GTEST_PROP(TEST_NAME, AskForMoreThanMaxSum, (std::vector<int> const& in))
{
  RC_PRE(in.size() >= unsigned(3));
  
  std::vector<int> cpin = in;
  std::size_t N = cpin.size();
  std::sort(cpin.begin(), cpin.end());
  RC_PRE(!overflow(cpin[0], cpin[1], cpin[2]));
  RC_PRE(!overflow(cpin[N-3], cpin[N-2], cpin[N-1]));
  
  auto max_possible_sum = cpin[N-3] + cpin[N-2] + cpin[N-1];
  auto delta = *rc::gen::inRange(0, std::numeric_limits<int>::max());
  RC_PRE(!overflow(max_possible_sum, delta));
  
  RC_ASSERT(closest_3sum(max_possible_sum + delta, in) == max_possible_sum);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
