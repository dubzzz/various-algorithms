#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <string>

// Replace all spaces of a std::string <in> by &nbsp;

// Algorithm to be tested:
// static std::string replace_spaces(std::string const&);

// Running tests

#ifndef ALGO
# define ALGO ReplaceInplace
#endif

namespace {
TEST(ALGO, EmptyString)
{
  ASSERT_EQ("", replace_spaces(""));
}

TEST(ALGO, SingleCharacterNoSpace)
{
  ASSERT_EQ("A", replace_spaces("A"));
}

TEST(ALGO, SingleSpace)
{
  ASSERT_EQ("&nbsp;", replace_spaces(" "));
}

TEST(ALGO, NoSpaces)
{
  ASSERT_EQ("ThisIsATestWhereIDidNotUseSpaceCharacter", replace_spaces("ThisIsATestWhereIDidNotUseSpaceCharacter"));
}

TEST(ALGO, MultipleSpaces)
{
  ASSERT_EQ("This&nbsp;Is&nbsp;A&nbsp;Test&nbsp;With&nbsp;Multiple&nbsp;Space&nbsp;Characters", replace_spaces("This Is A Test With Multiple Space Characters"));
}

TEST(ALGO, ConsecutiveSpaces)
{
  ASSERT_EQ("Hello&nbsp;&nbsp;&nbsp;World&nbsp;!", replace_spaces("Hello   World !"));
}

TEST(ALGO, StartsAndEndsBySpaces)
{
  ASSERT_EQ("&nbsp;&nbsp;&nbsp;Let's&nbsp;Try&nbsp;It!&nbsp;&nbsp;", replace_spaces("   Let's Try It!  "));
}

RC_GTEST_PROP(ALGO, RandomData, (const std::string& test))
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
}

