#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyString)
{
  ASSERT_EQ("", replace_spaces(""));
}

TEST(TEST_NAME, SingleCharacterNoSpace)
{
  ASSERT_EQ("A", replace_spaces("A"));
}

TEST(TEST_NAME, SingleSpace)
{
  ASSERT_EQ("&nbsp;", replace_spaces(" "));
}

TEST(TEST_NAME, NoSpaces)
{
  ASSERT_EQ("ThisIsATestWhereIDidNotUseSpaceCharacter", replace_spaces("ThisIsATestWhereIDidNotUseSpaceCharacter"));
}

TEST(TEST_NAME, MultipleSpaces)
{
  ASSERT_EQ("This&nbsp;Is&nbsp;A&nbsp;Test&nbsp;With&nbsp;Multiple&nbsp;Space&nbsp;Characters", replace_spaces("This Is A Test With Multiple Space Characters"));
}

TEST(TEST_NAME, ConsecutiveSpaces)
{
  ASSERT_EQ("Hello&nbsp;&nbsp;&nbsp;World&nbsp;!", replace_spaces("Hello   World !"));
}

TEST(TEST_NAME, StartsAndEndsBySpaces)
{
  ASSERT_EQ("&nbsp;&nbsp;&nbsp;Let's&nbsp;Try&nbsp;It!&nbsp;&nbsp;", replace_spaces("   Let's Try It!  "));
}

RC_GTEST_PROP(TEST_NAME, RandomData, (const std::string& test))
{
  std::string expected;

  std::size_t token_start = 0;
  for (std::size_t token_end = test.find(" ") ; token_end != std::string::npos ; token_start = token_end +1, token_end = test.find(" ", token_start))
  {
    expected += test.substr(token_start, token_end-token_start) + "&nbsp;";
  }
  expected += test.substr(token_start);
  
  RC_ASSERT(replace_spaces(test) == expected);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
