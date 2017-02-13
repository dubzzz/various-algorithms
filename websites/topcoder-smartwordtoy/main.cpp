#include "gtest/gtest.h"

#include <string>
#include <utility>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto forbidden = std::vector<std::string>{"a a a z", "a a z a", "a z a a", "z a a a", "a z z z", "z a z z", "z z a z", "z z z a"};
  ASSERT_EQ(8, min_presses("aaaa", "zzzz", forbidden));
}
TEST(TEST_NAME, Example1)
{
  auto forbidden = std::vector<std::string>{};
  ASSERT_EQ(4, min_presses("aaaa", "bbbb", forbidden));
}
TEST(TEST_NAME, Example2)
{
  auto forbidden = std::vector<std::string>{};
  ASSERT_EQ(50, min_presses("aaaa", "mmnn", forbidden));
}
TEST(TEST_NAME, Example3)
{
  auto forbidden = std::vector<std::string>{"bz a a a", "a bz a a", "a a bz a", "a a a bz"};
  ASSERT_EQ(-1, min_presses("aaaa", "zzzz", forbidden));
}
TEST(TEST_NAME, Example4)
{
  auto forbidden = std::vector<std::string>{
      "cdefghijklmnopqrstuvwxyz a a a"
       , "a cdefghijklmnopqrstuvwxyz a a"
       , "a a cdefghijklmnopqrstuvwxyz a"
       , "a a a cdefghijklmnopqrstuvwxyz" };
  ASSERT_EQ(6, min_presses("aaaa", "zzzz", forbidden));
}
TEST(TEST_NAME, Example5)
{
  auto forbidden = std::vector<std::string>{"b b b b"};
  ASSERT_EQ(-1, min_presses("aaaa", "bbbb", forbidden));
}
TEST(TEST_NAME, Example6)
{
  auto forbidden = std::vector<std::string>{
      "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"
      , "abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"};
  ASSERT_EQ(-1, min_presses("zzzz", "aaaa", forbidden));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
