#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyPattern)
{
  ASSERT_EQ(0, find_substr("AZERTY", ""));
}
TEST(TEST_NAME, MatchItself)
{
  ASSERT_EQ(0, find_substr("AZERTY", "AZERTY"));
}
TEST(TEST_NAME, PatternMoreThan32Characters)
{
  ASSERT_EQ(0, find_substr("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB"));
}
TEST(TEST_NAME, PatternMoreThan64Characters)
{
  ASSERT_EQ(0, find_substr("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB"));
}
TEST(TEST_NAME, MatchAtTheBeginning)
{
  ASSERT_EQ(0, find_substr("AZERTY", "AZ"));
}
TEST(TEST_NAME, MatchInside)
{
  ASSERT_EQ(2, find_substr("AZERTY", "ERT"));
}
TEST(TEST_NAME, MatchAtTheEnd)
{
  ASSERT_EQ(3, find_substr("AZERTY", "RTY"));
}
TEST(TEST_NAME, RepeatedFirstChar)
{
  ASSERT_EQ(1, find_substr("AAB", "AB"));
}
TEST(TEST_NAME, RepeatedFirstChars)
{
  ASSERT_EQ(2, find_substr("FEFEFA", "FEFA"));
}
TEST(TEST_NAME, CyclicPattern)
{
  ASSERT_EQ(4, find_substr("ABABABABBABABAB", "ABABB"));
}
TEST(TEST_NAME, FirstMatchIfMultiple)
{
  ASSERT_EQ(1, find_substr("ABABABABBABABAB", "BA"));
}
TEST(TEST_NAME, NoMatch)
{
  ASSERT_EQ(std::string::npos, find_substr("ABABABABBABABAB", "BAA"));
}

RC_GTEST_PROP(TEST_NAME, FindMatch, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::inRange('A', (char)('Z' +1)));
  std::string s1 = *gen;
  std::string s2 = *gen;
  std::string s3 = *gen;
  RC_ASSERT(find_substr(s1+s2+s3, s2) != std::string::npos);
}
RC_GTEST_PROP(TEST_NAME, FindFirstMatch, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::inRange('A', (char)('Z' +1)));
  std::string s1 = *gen;
  std::string s2 = *gen;
  std::string s3 = *gen;
  RC_PRE(! s2.empty());
  RC_ASSERT(find_substr(s1+s2+s3, s2) <= s1.size());
}
RC_GTEST_PROP(TEST_NAME, IfAnswerItIsBeginningOfMatch, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::inRange('A', (char)('Z' +1)));
  std::string input = *gen;
  std::string pattern = *gen;
  std::size_t pos { find_substr(input, pattern) };
  bool correct = pos == std::string::npos;
  if (! correct && pattern.size() + pos <= input.size())
  {
    correct = std::mismatch(pattern.begin(), pattern.end(), input.begin() +pos).first == pattern.end();
  }
  RC_ASSERT(correct);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
