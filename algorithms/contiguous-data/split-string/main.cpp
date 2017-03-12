#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, NoSplit)
{
  auto expected = std::vector<std::string>{"nosplit"};
  ASSERT_EQ(expected, split("nosplit", '*'));
}
TEST(TEST_NAME, SingleSplit)
{
  auto expected = std::vector<std::string>{"with","split"};
  ASSERT_EQ(expected, split("with-split", '-'));
}
TEST(TEST_NAME, SplitAtStart)
{
  auto expected = std::vector<std::string>{"","start"};
  ASSERT_EQ(expected, split("/start", '/'));
}
TEST(TEST_NAME, SplitAtEnd)
{
  auto expected = std::vector<std::string>{"end",""};
  ASSERT_EQ(expected, split("end+", '+'));
}
TEST(TEST_NAME, MultipleSplits)
{
  auto expected = std::vector<std::string>{"","hello","world","!"};
  ASSERT_EQ(expected, split("*hello*world*!", '*'));
}
TEST(TEST_NAME, SplitOnOnlyChar)
{
  auto expected = std::vector<std::string>{"","",""};
  ASSERT_EQ(expected, split("aa", 'a'));
}

RC_GTEST_PROP(TEST_NAME, BalancedNumberOfCutsLength, (std::string const& in, char delim))
{
  RC_PRE(! in.empty());
  auto result = split(in, delim);
  RC_ASSERT(in.size() == result.size() -1 + std::accumulate(result.begin(), result.end(), std::size_t{}, [](auto acc, auto sp){ return acc + sp.size(); }));
}
RC_GTEST_PROP(TEST_NAME, CutsAtRightPlace, (std::string const& in, char delim))
{
  RC_PRE(! in.empty());
  auto result = split(in, delim);
  if (result.size() < 2) { return; }
  
  std::size_t poscut, idx;
  for (poscut = result[0].size(), idx = 1 ; idx < result.size() ; poscut += result[idx++].size() +1)
  {
    RC_ASSERT(in[poscut] == delim);
  }
}
RC_GTEST_PROP(TEST_NAME, NoRemainingCutsPossible, (std::string const& in, char delim))
{
  RC_PRE(! in.empty());
  auto result = split(in, delim);
  
  for (auto const& r : result)
  {
    RC_ASSERT(r.find(delim) == std::string::npos);
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
