#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

// http://www.programcreek.com/2013/02/longest-substring-which-contains-2-unique-characters/
// Given a string, find the longest substring that contains only two unique characters.
// For example, given "abcbbbbcccbdddadacb", the longest substring that contains 2 unique character is "bcbbbbcccb".

// Algorithm to be tested:
// static std::size_t longest_size(std::string const& in);

// Running tests


#ifndef ALGO
# define ALGO LongestSubstr2Uniques
#endif

namespace {
TEST(ALGO, EmptyString)
{
  ASSERT_EQ(0, longest_size(""));
}

TEST(ALGO, UniqueCharacter)
{
  ASSERT_EQ(5, longest_size("aaaaa"));
}

TEST(ALGO, TwoCharacters)
{
  ASSERT_EQ(7, longest_size("abbaaba"));
}

TEST(ALGO, SubstringOfMainString)
{
  ASSERT_EQ(10, longest_size("abcbbbbcccbdddadacb"));
}

RC_GTEST_PROP(ALGO, RandomData, (char c1, char c2))
{
  RC_PRE(c1 != c2);
  
  std::string answer_str = *rc::gen::apply(
      [](auto&& vs) { return std::string(std::begin(vs), std::end(vs)); }
      , rc::gen::container<std::vector<char>>(rc::gen::element<char>(char(c1), char(c2))))
    .as("longest part with 2 different chars");
  RC_PRE(answer_str.find(c1) != std::string::npos);
  RC_PRE(answer_str.find(c2) != std::string::npos);
  
  std::size_t pre_length = *rc::gen::inRange<std::size_t>(0, answer_str.size())
    .as("length for the part before longest");
  std::string pre_str = *rc::gen::apply(
      [](auto&& vs) { return std::string(std::begin(vs), std::end(vs)); }
      , rc::gen::container<std::vector<char>>(pre_length, rc::gen::arbitrary<char>()))
    .as("before longest chars");
  RC_PRE(pre_str.size() == std::size_t() || (pre_str.back() != c1 && pre_str.back() != c2));
  
  std::size_t post_length = *rc::gen::inRange<std::size_t>(0, answer_str.size())
    .as("length of the part after longest");
  std::string post_str = *rc::gen::apply(
      [](auto&& vs) { return std::string(std::begin(vs), std::end(vs)); }
      , rc::gen::container<std::vector<char>>(post_length, rc::gen::arbitrary<char>()))
    .as("after longest chars");
  RC_PRE(post_str.size() == std::size_t() || (post_str.front() != c1 && post_str.front() != c2));
  
  std::string data = pre_str + answer_str + post_str;
  RC_ASSERT(answer_str.size() == longest_size(data));
}
}

