#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

// Compute the most significant bit of an unsigned
// eg.: most significant bit of 9 is 1

// Algorithm to be tested
// unsigned less_significant(unsigned)

// Running tests

TEST(TEST_NAME, Zero)
{
  ASSERT_EQ(0, less_significant(0));
}

TEST(TEST_NAME, PowerOfTwo)
{
  ASSERT_EQ(128, less_significant(128));
}

TEST(TEST_NAME, Nine)
{
  ASSERT_EQ(1, less_significant(9));
}

RC_GTEST_PROP(TEST_NAME, AnswerIsPowerOfTwo, (unsigned N))
{
  auto answer = less_significant(N);
  RC_ASSERT((answer & (answer-1)) == decltype(answer)());
}

RC_GTEST_PROP(TEST_NAME, AnswerIsBitOfInput, (unsigned N))
{
  auto answer = less_significant(N);
  RC_ASSERT((N | answer) == N);
}

RC_GTEST_PROP(TEST_NAME, AnswerIsTheLowestBit, (unsigned N))
{
  RC_PRE(N > unsigned());
  RC_PRE(N & (N-1)); //not a power of two
  auto answer = less_significant(N);
  RC_ASSERT((N ^ answer) > answer);
}

RC_GTEST_PROP(TEST_NAME, AnswerIsItselfForPowerOfTwo, ())
{
  auto power = *rc::gen::inRange(decltype(sizeof(unsigned))(), 8 * sizeof(unsigned));
  unsigned N = 1 << power;
  RC_ASSERT(N == less_significant(N));
}

