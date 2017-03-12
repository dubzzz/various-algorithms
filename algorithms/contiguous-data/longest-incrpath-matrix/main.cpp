#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example1)
{
  auto m = std::vector<std::vector<int>>{
      std::vector<int>{1,2,3},
      std::vector<int>{4,5,6},
      std::vector<int>{7,8,9}
  };
  ASSERT_EQ(5, longest_incr(m));
}
TEST(TEST_NAME, Example2)
{
  auto m = std::vector<std::vector<int>>{
      std::vector<int>{1,2,3},
      std::vector<int>{8,9,4},
      std::vector<int>{7,6,5}
  };
  ASSERT_EQ(9, longest_incr(m));
}
TEST(TEST_NAME, Example3)
{
  auto m = std::vector<std::vector<int>>{
      std::vector<int>{0,0,0,0},
      std::vector<int>{0,0,0,0},
      std::vector<int>{0,0,0,0}
  };
  ASSERT_EQ(1, longest_incr(m));
}
TEST(TEST_NAME, Example4)
{
  auto m = std::vector<std::vector<int>>{
      std::vector<int>{9,9,8,2,2},
      std::vector<int>{9,1,5,2,9},
      std::vector<int>{9,9,4,3,8}
  };
  ASSERT_EQ(6, longest_incr(m));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

