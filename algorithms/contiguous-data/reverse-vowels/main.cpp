#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyString)
{
  ASSERT_EQ(std::string(""), reverse_vowels(""));
}
TEST(TEST_NAME, NoVowels)
{
  ASSERT_EQ(std::string("zrtp"), reverse_vowels("zrtp"));
}
TEST(TEST_NAME, VowelsAtEnds)
{
  ASSERT_EQ(std::string("azrtopi"), reverse_vowels("izrtopa"));
}
TEST(TEST_NAME, EvenNumberOfVowels)
{
  ASSERT_EQ(std::string("wazrtiopicc"), reverse_vowels("wizrtoipacc"));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
