#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <memory>
#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyString)
{
  std::string test = "";
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strncpy(in.get(), test.c_str(), test.size() +1);
  char* before = in.get();
  ASSERT_EQ("", std::string(reverse(in.get())));
  ASSERT_EQ(before, in.get());
}

TEST(TEST_NAME, OneCharacter)
{
  std::string test = "a";
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strncpy(in.get(), test.c_str(), test.size() +1);
  char* before = in.get();
  ASSERT_EQ("a", std::string(reverse(in.get())));
  ASSERT_EQ(before, in.get());
}

TEST(TEST_NAME, EvenNumberOfCharacters)
{
  std::string test = "122345";
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strncpy(in.get(), test.c_str(), test.size() +1);
  char* before = in.get();
  ASSERT_EQ("543221", std::string(reverse(in.get())));
  ASSERT_EQ(before, in.get());
}

TEST(TEST_NAME, OddNumberOfCharacters)
{
  std::string test = "1223457";
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strncpy(in.get(), test.c_str(), test.size() +1);
  char* before = in.get();
  ASSERT_EQ("7543221", std::string(reverse(in.get())));
  ASSERT_EQ(before, in.get());
}

RC_GTEST_PROP(TEST_NAME, RandomData, (const std::string& test))
{
  RC_PRE(std::find(test.begin(), test.end(), '\0') == test.end());
  std::string rev = test;
  std::reverse(rev.begin(), rev.end());
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strncpy(in.get(), test.c_str(), test.size() +1);
  char* before = in.get();
  RC_ASSERT(std::string(reverse(in.get())) == rev);
  RC_ASSERT(in.get() == before);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
