#include "gtest/gtest.h"

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  ASSERT_EQ(2, fast_knight("a1", "b3", "c5"));
}
TEST(TEST_NAME, Example1)
{
  ASSERT_EQ(3, fast_knight("b1", "c3", "a3"));
}
TEST(TEST_NAME, Example2)
{
  ASSERT_EQ(6, fast_knight("a1", "a2", "b2"));
}
TEST(TEST_NAME, Example3)
{
  ASSERT_EQ(3, fast_knight("a5", "b7", "e4"));
}
TEST(TEST_NAME, Example4)
{
  ASSERT_EQ(6, fast_knight("h8", "e2", "d2"));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
