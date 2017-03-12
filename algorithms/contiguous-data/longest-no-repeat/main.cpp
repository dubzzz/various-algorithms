#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyString)
{
  ASSERT_EQ(0, longest_no_repeat(""));
}
TEST(TEST_NAME, AllCharactersAreUnique)
{
  ASSERT_EQ(10, longest_no_repeat("azertyuiop"));
}
TEST(TEST_NAME, BestIsAtTheBeginning)
{
  ASSERT_EQ(3, longest_no_repeat("abcabcbb"));
}
TEST(TEST_NAME, BestIsAtTheEnd)
{
  ASSERT_EQ(5, longest_no_repeat("abcabcbbabcde"));
}
TEST(TEST_NAME, IdenticalCharacters)
{
  ASSERT_EQ(1, longest_no_repeat("eeeeeeeeee"));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
