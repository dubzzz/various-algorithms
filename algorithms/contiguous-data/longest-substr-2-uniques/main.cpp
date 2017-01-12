#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyString)
{
  ASSERT_EQ(0, longest_size(""));
}

TEST(TEST_NAME, UniqueCharacter)
{
  ASSERT_EQ(5, longest_size("aaaaa"));
}

TEST(TEST_NAME, TwoCharacters)
{
  ASSERT_EQ(7, longest_size("abbaaba"));
}

TEST(TEST_NAME, SubstringOfMainString)
{
  ASSERT_EQ(10, longest_size("abcbbbbcccbdddadacb"));
}

RC_GTEST_PROP(TEST_NAME, RandomData, (char c1, char c2))
{
  RC_PRE(c1 != c2);
  
  char moved_c1 = c1, moved_c2 = c2;
  std::string answer_str = *rc::gen::apply(
      [](auto&& vs) { return std::string(std::begin(vs), std::end(vs)); }
      , rc::gen::container<std::vector<char>>(rc::gen::element<char>(std::move(moved_c1), std::move(moved_c2))))
    .as("longest part with 2 different chars");
  RC_PRE(answer_str.find(c1) != std::string::npos);
  RC_PRE(answer_str.find(c2) != std::string::npos);
  
  std::size_t pre_length = *rc::gen::inRange<std::size_t>(0, answer_str.size())
    .as("length for the part before longest");
  std::string pre_str = *rc::gen::apply(
      [](auto&& vs) { return std::string(std::begin(vs), std::end(vs)); }
      , rc::gen::container<std::vector<char>>(pre_length, rc::gen::arbitrary<char>()))
    .as("before longest chars");
  if (! pre_str.empty())
  {
    RC_PRE(pre_str.back() != c1 && pre_str.back() != c2);
  }
  if (pre_str.size() >= std::size_t(2))
  {
    RC_PRE(pre_str[pre_str.size() -1] != pre_str[pre_str.size() -2]);
    RC_PRE(pre_str[pre_str.size() -2] != c1 && pre_str[pre_str.size() -2] != c2); //[pre_str.size() -1] already tested
  }
  
  std::size_t post_length = *rc::gen::inRange<std::size_t>(0, answer_str.size())
    .as("length of the part after longest");
  std::string post_str = *rc::gen::apply(
      [](auto&& vs) { return std::string(std::begin(vs), std::end(vs)); }
      , rc::gen::container<std::vector<char>>(post_length, rc::gen::arbitrary<char>()))
    .as("after longest chars");
  if (! post_str.empty())
  {
    RC_PRE(post_str.front() != c1 && post_str.front() != c2);
  }
  if (post_str.size() >= std::size_t(2))
  {
    RC_PRE(post_str[0] != post_str[1]);
    RC_PRE(post_str[1] != c1 && post_str[1] != c2); //[0] already tested
  }
  
  std::string data = pre_str + answer_str + post_str;
  RC_ASSERT(answer_str.size() == longest_size(data));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
