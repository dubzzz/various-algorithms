#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, SameStrings)
{
  ASSERT_EQ(6, longest_common_substr("AZERTY", "AZERTY").first);
}
TEST(TEST_NAME, CommonPartAtTheBeginning)
{
  ASSERT_EQ(6, longest_common_substr("AZERTY123", "AZERTY456789").first);
}
TEST(TEST_NAME, CommonPartAtTheEnd)
{
  ASSERT_EQ(6, longest_common_substr("123AZERTY", "456789AZERTY").first);
}
TEST(TEST_NAME, NoCommonPart)
{
  ASSERT_EQ(0, longest_common_substr("AZERTY", "UIO").first);
}
TEST(TEST_NAME, OnlyOneContiguousPartInCommon)
{
  ASSERT_EQ(3, longest_common_substr("AZERTYUIOP", "WNBERTX").first);
}
TEST(TEST_NAME, MultipleCommonSubstrings)
{
  ASSERT_EQ(3, longest_common_substr("AZERTY", "123RTY1AZ9ER5TYTREZA4").first);
}

RC_GTEST_PROP(TEST_NAME, FindLongest, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::inRange('A', (char)('Z' +1)));
  std::string s1 = *gen;
  std::string s2 = *gen;
  std::string s3 = *gen;
  std::string s4 = *gen;
  std::string common = *gen;
  RC_ASSERT(longest_common_substr(s1+common+s2, s3+common+s4).first >= common.size());
}
RC_GTEST_PROP(TEST_NAME, LongestIsAtMostTheMinOfInputs, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::inRange('A', (char)('Z' +1)));
  std::string s1 = *gen;
  std::string s2 = *gen;
  RC_ASSERT(longest_common_substr(s1, s2).first <= std::min(s1.size(), s2.size()));
}
RC_GTEST_PROP(TEST_NAME, CommonPartStartsAtStartPoints, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::inRange('A', (char)('Z' +1)));
  std::string s1 = *gen;
  std::string s2 = *gen;
  auto answer = longest_common_substr(s1, s2);
  RC_ASSERT(answer.first + answer.second.first <= s1.size());
  RC_ASSERT(answer.first + answer.second.second <= s2.size());
  
  std::string common1 = s1.substr(answer.second.first, answer.first);
  std::string common2 = s2.substr(answer.second.second, answer.first);
  RC_ASSERT(common1 == common2);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
