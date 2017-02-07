#include "gtest/gtest.h"

#include <string>
#include <utility>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto data = std::vector<std::string>{"9 2 3", "4 8 7"};
  ASSERT_EQ(std::make_pair(4, 7), tall_people(data));
}
TEST(TEST_NAME, Example1)
{
  auto data = std::vector<std::string>{"1 2", "4 5", "3 6"};
  ASSERT_EQ(std::make_pair(4, 4), tall_people(data));
}
TEST(TEST_NAME, Example2)
{
  auto data = std::vector<std::string>{"1 1", "1 1"};
  ASSERT_EQ(std::make_pair(1, 1), tall_people(data));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
