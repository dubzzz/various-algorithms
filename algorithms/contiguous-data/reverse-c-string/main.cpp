#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <memory>
#include <string>

// Algorithm to be tested

// In-place

char* reverse_inplace(char* in)
{
  // Reverse a null-terminated string in-place
  
  char* pos = in;
  while (*pos)
  {
    ++pos;
  }
  --pos;
  
  char* direct = in;
  while (direct < pos)
  {
    char tmp = *direct;
    *direct++ = *pos;
    *pos-- = tmp;
  }
  return in;
}

inline char* reverse(char* in)
{
  #define ALGO ReverseCString_INPLACE
  return reverse_inplace(in);
}

// Running tests

TEST(ALGO, EmptyString)
{
  std::string test = "";
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strcpy(in.get(), test.c_str());
  char* before = in.get();
  ASSERT_EQ("", std::string(reverse(in.get())));
  ASSERT_EQ(before, in.get());
}

TEST(ALGO, OneCharacter)
{
  std::string test = "a";
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strcpy(in.get(), test.c_str());
  char* before = in.get();
  ASSERT_EQ("a", std::string(reverse(in.get())));
  ASSERT_EQ(before, in.get());
}

TEST(ALGO, EvenNumberOfCharacters)
{
  std::string test = "122345";
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strcpy(in.get(), test.c_str());
  char* before = in.get();
  ASSERT_EQ("543221", std::string(reverse(in.get())));
  ASSERT_EQ(before, in.get());
}

TEST(ALGO, OddNumberOfCharacters)
{
  std::string test = "1223457";
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strcpy(in.get(), test.c_str());
  char* before = in.get();
  ASSERT_EQ("7543221", std::string(reverse(in.get())));
  ASSERT_EQ(before, in.get());
}

RC_GTEST_PROP(ALGO, RandomData, (const std::string& test))
{
  RC_PRE(std::find(test.begin(), test.end(), '\0') == test.end());
  std::string rev = test;
  std::reverse(rev.begin(), rev.end());
  std::unique_ptr<char[]> in { new char[test.size()+1] };
  strcpy(in.get(), test.c_str());
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

