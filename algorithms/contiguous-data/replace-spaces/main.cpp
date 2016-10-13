#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

// Algorithm to be tested

template <char delimiter> struct DelimitedString : std::string {};
template <char delimiter> std::istream& operator>>(std::istream& stream, DelimitedString<delimiter>& s)
{
  return getline(stream, static_cast<std::string&>(s), delimiter);
}

std::string replace_spaces_using_stl(std::string const& in)
{
  const std::string replace_by = "&nbsp;";
  std::istringstream iss(in);
  std::ostringstream oss;
  std::copy(std::istream_iterator<DelimitedString<' '>>(iss)
      , std::istream_iterator<DelimitedString<' '>>()
      , std::ostream_iterator<std::string>(oss, replace_by.c_str()));
  std::string out = oss.str();
  return out.empty() || in[in.size()-1] == ' ' ? out : out.substr(0, out.size() -replace_by.size());
}

inline std::string replace_spaces(std::string const& in)
{
  #define ALGO ReplaceSpaces_STL
  return replace_spaces_using_stl(in);
}

// Running tests

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

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

