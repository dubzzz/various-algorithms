#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyString)
{
  ASSERT_EQ(std::string(""), reverse_words(""));
}
TEST(TEST_NAME, OneWord)
{
  ASSERT_EQ(std::string("hello"), reverse_words("hello"));
}
TEST(TEST_NAME, TwoWords)
{
  ASSERT_EQ(std::string("world hello"), reverse_words("hello world"));
}
TEST(TEST_NAME, EvenNumberOfWords)
{
  ASSERT_EQ(std::string("blue is sky the"), reverse_words("the sky is blue"));
}
TEST(TEST_NAME, OddNumberOfWords)
{
  ASSERT_EQ(std::string("blue is sky the"), reverse_words("the sky is blue"));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
