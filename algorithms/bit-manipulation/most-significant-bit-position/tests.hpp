#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

// Compute the most significant bit position of an unsigned
// eg.: most significant bit of 9 (0b1001) is 4th bit so answer is 4

// Algorithm to be tested
// unsigned most_significant_position(unsigned)

// Constexpr tests

#if ! defined(NO_CONSTEXPR)
  static_assert(most_significant_position(0) == 0, "most_significant_position(0) is 0");
  static_assert(most_significant_position(8) == 4, "most_significant_position(8) is 4");
#endif

// Running tests

TEST(TEST_NAME, Zero)
{
  ASSERT_EQ(0, most_significant_position(0));
}

TEST(TEST_NAME, PowerOfTwo)
{
  ASSERT_EQ(8, most_significant_position(128));
}

TEST(TEST_NAME, Nine)
{
  ASSERT_EQ(4, most_significant_position(9));
}

TEST(TEST_NAME, LargeNumber)
{
  ASSERT_EQ(32, most_significant_position(2147483648));
}

RC_GTEST_PROP(TEST_NAME, AnswerIsNotNullForNotNull, (unsigned N))
{
  RC_PRE(N > unsigned());
  RC_ASSERT(most_significant_position(N) > unsigned());
}

RC_GTEST_PROP(TEST_NAME, AnswerIsBitOfInput, (unsigned N))
{
  RC_PRE(N > unsigned());
  auto answer_pos = most_significant_position(N);
  auto answer = 1 << (answer_pos -1);
  RC_ASSERT((N | answer) == N);
}

RC_GTEST_PROP(TEST_NAME, AnswerIsTheHighestBit, (unsigned N))
{
  RC_PRE(N > unsigned());
  auto answer_pos = most_significant_position(N);
  auto answer = unsigned(1) << (answer_pos -1);
  RC_ASSERT((N ^ answer) < answer);
}

