#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

// Compute the most significant bit of an unsigned
// eg.: most significant bit of 9 is 8

// Algorithm to be tested
// unsigned most_significant(unsigned)

// Running tests

TEST(TEST_NAME, Zero)
{
  ASSERT_EQ(0, most_significant(0));
}

TEST(TEST_NAME, PowerOfTwo)
{
  ASSERT_EQ(128, most_significant(128));
}

TEST(TEST_NAME, Nine)
{
  ASSERT_EQ(8, most_significant(9));
}

RC_GTEST_PROP(TEST_NAME, AnswerIsPowerOfTwo, (unsigned N))
{
  auto answer = most_significant(N);
  RC_ASSERT((answer & (answer-1)) == decltype(answer)());
}

RC_GTEST_PROP(TEST_NAME, AnswerIsBitOfInput, (unsigned N))
{
  auto answer = most_significant(N);
  RC_ASSERT((N | answer) == N);
}

RC_GTEST_PROP(TEST_NAME, AnswerIsTheHighestBit, (unsigned N))
{
  RC_PRE(N > unsigned());
  auto answer = most_significant(N);
  RC_ASSERT((N ^ answer) < answer);
}

