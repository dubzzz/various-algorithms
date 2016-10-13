#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

// Algorithm to be tested

// In-place

void replace_spaces_inplace(std::string& in)
{
  // Replace all spaces of std::string <in> using only <in>
  // and being able to resize it if required

  const std::string replace_by = "&nbsp;";
  
  std::size_t previous_size { in.size() };
  std::size_t expected_size { in.size() + (replace_by.size() -1) * std::count(in.begin(), in.end(), ' ') };
  in.resize(expected_size);

  for (std::size_t pos = previous_size, current = expected_size ; pos > 0 ; --pos)
  {
    if (in[pos-1] == ' ')
    {
      for (auto rit = replace_by.rbegin() ; rit != replace_by.rend() ; ++rit)
      {
        in[--current] = *rit;
      }
    }
    else
    {
      in[--current] = in[pos-1];
    }
  }
}

// STL

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
#ifdef INPLACE
  #define ALGO ReplaceSpaces_INPLACE
  std::string copy { in };
  replace_spaces_inplace(copy);
  return copy;
#else
  #define ALGO ReplaceSpaces_STL
  return replace_spaces_using_stl(in);
#endif
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

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

