#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, NoRectangle)
{
  auto data = std::vector<std::vector<bool>>{
      {false, false, false, false, false},
      {false, false, false, false, false}
  };
  ASSERT_EQ(0, largest_area(data));
}
TEST(TEST_NAME, RectangleItself)
{
  auto data = std::vector<std::vector<bool>>{
      { true,  true,  true,  true,  true},
      { true,  true,  true,  true,  true}
  };
  ASSERT_EQ(10, largest_area(data));
}
TEST(TEST_NAME, Example1)
{
  auto data = std::vector<std::vector<bool>>{
      { true, false,  true,  true, false},
      {false, false, false,  true,  true}
  };
  ASSERT_EQ(2, largest_area(data));
}
TEST(TEST_NAME, Example2)
{
  auto data = std::vector<std::vector<bool>>{
      { true, false,  true,  true, false},
      { true, false,  true,  true, false},
      {false, false,  true,  true, false},
      {false, false, false,  true,  true},
      { true, false,  true,  true, false},
      { true, false,  true, false, false}
  };
  ASSERT_EQ(6, largest_area(data));
}
TEST(TEST_NAME, Example3)
{
  auto data = std::vector<std::vector<bool>>{
      { true,  true,  true,  true, false},
      {false,  true,  true,  true,  true}
  };
  ASSERT_EQ(6, largest_area(data));
}
TEST(TEST_NAME, Example4)
{
  auto data = std::vector<std::vector<bool>>{
      { true, false,  true,  true, false},
      { true, false,  true, false, false},
      {false, false, false,  true,  true},
      {false, false, false,  true,  true},
      {false,  true, false, false, false},
      {false, false, false,  true,  true},
      { true, false,  true,  true, false},
      {false, false, false,  true,  true}
  };
  ASSERT_EQ(4, largest_area(data));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

