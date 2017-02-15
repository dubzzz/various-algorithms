#include "gtest/gtest.h"

#include <string>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto favorites = std::vector<std::string>{"0 2", "1", "0 1"};
  ASSERT_EQ(32, calculate_time(favorites));
}
TEST(TEST_NAME, Example1)
{
  auto favorites = std::vector<std::string>{"0", "0", "0"};
  ASSERT_EQ(49, calculate_time(favorites));
}
TEST(TEST_NAME, Example2)
{
  auto favorites = std::vector<std::string>{"4", "1", "2", "3", "0"};
  ASSERT_EQ(50, calculate_time(favorites));
}
TEST(TEST_NAME, Example3)
{
  auto favorites = std::vector<std::string>{"0 004", "2 3", "0 01", "1 2 3 4", "1 1"};
  ASSERT_EQ(35, calculate_time(favorites));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
