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
// bool isomorphics(std::string const& s1, std::string const& s2)

// Running tests

TEST(TEST_NAME, EmptyStrings)
{
  ASSERT_TRUE(isomorphics("", ""));
}

TEST(TEST_NAME, OneCharacterStrings)
{
  ASSERT_TRUE(isomorphics("a", "z"));
}

TEST(TEST_NAME, SameStrings)
{
  ASSERT_TRUE(isomorphics("azerty", "azerty"));
}

TEST(TEST_NAME, IsomorphicOnlyStrings)
{
  ASSERT_TRUE(isomorphics("egg", "add"));
}

TEST(TEST_NAME, DifferentSizesStrings)
{
  ASSERT_FALSE(isomorphics("aaa", "bb"));
}

TEST(TEST_NAME, NonIsomorphicStrings)
{
  ASSERT_FALSE(isomorphics("foo", "bar"));
}

RC_GTEST_PROP(TEST_NAME, AlwaysIsomorphicRandomData, (const std::string& s))
{
  std::string s2 = *rc::gen::apply([s](unsigned seed) {
    std::vector<char> remap(UCHAR_MAX +1);
    std::iota(std::begin(remap), std::end(remap), CHAR_MIN);
    std::mt19937 g(seed);
    std::shuffle(std::begin(remap), std::end(remap), g);
    
    std::string s2;
    std::transform(std::begin(s), std::end(s), std::back_inserter(s2), [&remap](char cur) { return remap[static_cast<int>(cur) - CHAR_MIN]; });
    return s2;
  }, rc::gen::arbitrary<unsigned>()).as("isomorphic transformation of s (s2)");

  RC_ASSERT(isomorphics(s, s2));
}

RC_GTEST_PROP(TEST_NAME, OneNonIsomorphicRandomData, (const std::string& s))
{
  RC_PRE(! s.empty());
  
  std::size_t selected_id = *rc::gen::inRange<std::size_t>(0, s.size()).as("selected position for copy (selected_id)");
  std::size_t selected_swap_id = *rc::gen::inRange<std::size_t>(0, s.size()).as("selected position for swap (selected_swap_id)");
  
  std::string s1 = *rc::gen::apply([selected_id,selected_swap_id,s]() {
    std::string s1 = s + s[selected_id];
    std::swap(*s1.rbegin(), s1[selected_swap_id]);
    return s1;
  }).as("extension of s (s1)");
  std::string s2 = *rc::gen::apply([selected_id,selected_swap_id,s](unsigned seed, unsigned char inc) {
    std::vector<char> remap(UCHAR_MAX +1);
    std::iota(std::begin(remap), std::end(remap), CHAR_MIN);
    std::mt19937 g(seed);
    std::shuffle(std::begin(remap), std::end(remap), g);
    
    std::string s2;
    std::transform(std::begin(s), std::end(s), std::back_inserter(s2), [&remap](char cur) { return remap[static_cast<int>(cur) - CHAR_MIN]; });
    s2 += s2[selected_id];
    s2[selected_id] += inc;
    std::swap(*s2.rbegin(), s2[selected_swap_id]);
    return s2;
  }, rc::gen::arbitrary<unsigned>(), rc::gen::inRange(1, 256)).as("non-isomorphic transformation of s (s2)");

  RC_ASSERT(! isomorphics(s1, s2));
}

