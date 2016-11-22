#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <climits>
#include <iterator>
#include <map>
#include <numeric>
#include <random>
#include <string>
#include <vector>

// http://www.programcreek.com/2014/05/leetcode-isomorphic-strings-java/
// Given two strings s and t, determine if they are isomorphic. Two strings are isomorphic if the characters in s can be replaced to get t.
// For example,"egg" and "add" are isomorphic, "foo" and "bar" are not.

// Algorithm to be tested

bool isomorphics(std::string const& s1, std::string const& s2)
{
  if (s1.size() != s2.size())
  {
    return false;
  }
  
  std::unordered_map<char, char> matches;
  for (std::size_t i {} ; i != s1.size() ; ++i)
  {
    const char& c1 = s1[i];
    const char& c2 = s2[i];
    auto&& match = matches.find(c1);
    if (match != matches.end())
    {
      if (match->second != c2) { return false; }
    }
    else
    {
      matches[c1] = c2;
    }
  }
  return true;
}

#define ALGO Isomorphics_DEFAULT

// Running tests

TEST(ALGO, EmptyStrings)
{
  ASSERT_TRUE(isomorphics("", ""));
}

TEST(ALGO, OneCharacterStrings)
{
  ASSERT_TRUE(isomorphics("a", "z"));
}

TEST(ALGO, SameStrings)
{
  ASSERT_TRUE(isomorphics("azerty", "azerty"));
}

TEST(ALGO, IsomorphicOnlyStrings)
{
  ASSERT_TRUE(isomorphics("egg", "add"));
}

TEST(ALGO, DifferentSizesStrings)
{
  ASSERT_FALSE(isomorphics("aaa", "bb"));
}

TEST(ALGO, NonIsomorphicStrings)
{
  ASSERT_FALSE(isomorphics("foo", "bar"));
}

RC_GTEST_PROP(ALGO, AlwaysIsomorphicRandomData, (const std::string& s1, unsigned seed))
{
  std::vector<char> remap(UCHAR_MAX +1);
  std::iota(std::begin(remap), std::end(remap), CHAR_MIN);
  std::mt19937 g(seed);
  std::shuffle(std::begin(remap), std::end(remap), g);

  std::string s2;
  std::transform(std::begin(s1), std::end(s1), std::back_inserter(s2), [&remap](char cur) { return remap[static_cast<int>(cur) - CHAR_MIN]; });

  RC_ASSERT(isomorphics(s1, s2));
}

RC_GTEST_PROP(ALGO, OneNonIsomorphicRandomData, (const std::string& s, unsigned seed))
{
  RC_PRE(! s.empty());
  
  std::vector<char> remap(UCHAR_MAX +1);
  std::iota(std::begin(remap), std::end(remap), CHAR_MIN);
  std::mt19937 g(seed);
  std::shuffle(std::begin(remap), std::end(remap), g);
  
  std::string s1(s);
  std::string s2;
  std::transform(std::begin(s1), std::end(s1), std::back_inserter(s2), [&remap](char cur) { return remap[static_cast<int>(cur) - CHAR_MIN]; });
  
  std::uniform_int_distribution<std::size_t> dist_select_elt(0, s2.size() -1);
  std::uniform_int_distribution<int> dist_elt(1, 255);
  auto selected_id = dist_select_elt(g);
  s1 += s1[selected_id];
  s2 += s2[selected_id];
  s2[selected_id] += dist_elt(g);
  
  RC_ASSERT(! isomorphics(s1, s2));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

