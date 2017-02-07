#include "gtest/gtest.h"

#include <string>
#include <utility>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto data = std::vector<std::string>{"ITA JPN AUS", "KOR TPE UKR", "KOR KOR GBR", "KOR CHN TPE"};
  auto expected = std::vector<std::string>{"KOR 3 1 0", "ITA 1 0 0", "TPE 0 1 1", "CHN 0 1 0", "JPN 0 1 0", "AUS 0 0 1", "GBR 0 0 1", "UKR 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Example1)
{
  auto data = std::vector<std::string>{"USA AUT ROM"};
  auto expected = std::vector<std::string>{"USA 1 0 0",  "AUT 0 1 0",  "ROM 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Example2)
{
  auto data = std::vector<std::string>{"GER AUT SUI", "AUT SUI GER", "SUI GER AUT"};
  auto expected = std::vector<std::string>{"AUT 1 1 1",  "GER 1 1 1",  "SUI 1 1 1"};
  ASSERT_EQ(expected, medal_table(data));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
