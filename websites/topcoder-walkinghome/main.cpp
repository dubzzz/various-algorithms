#include "gtest/gtest.h"

#include <string>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Statement0)
{
  auto map = std::vector<std::string>{
      "S.||.H"
  };
  ASSERT_EQ(1, fewest_crossings(map));
}
TEST(TEST_NAME, Statement1)
{
  auto map = std::vector<std::string>{
      "S||",
      "||H"
  };
  ASSERT_EQ(-1, fewest_crossings(map));
}
TEST(TEST_NAME, Statement2)
{
  auto map = std::vector<std::string>{
      "S.F",
      ".F.",
      "F.H"
  };
  ASSERT_EQ(-1, fewest_crossings(map));
}
TEST(TEST_NAME, Example0)
{
  auto map = std::vector<std::string>{
      "S.|..",
      "..|.H"
  };
  ASSERT_EQ(1, fewest_crossings(map));
}
TEST(TEST_NAME, Example1)
{
  auto map = std::vector<std::string>{
      "S.|..",
      "..|.H",
      "..|..",
      "....."
  };
  ASSERT_EQ(0, fewest_crossings(map));
}
TEST(TEST_NAME, Example2)
{
  auto map = std::vector<std::string>{
      "S.||...",
      "..||...",
      "..||...",
      "..||..H"
  };
  ASSERT_EQ(1, fewest_crossings(map));
}
TEST(TEST_NAME, Example3)
{
  auto map = std::vector<std::string>{
      "S.....",
      "---*--",
      "...|..",
      "...|.H"
  };
  ASSERT_EQ(1, fewest_crossings(map));
}
TEST(TEST_NAME, Example4)
{
  auto map = std::vector<std::string>{
      "S.F..",
      "..F..",
      "--*--",
      "..|..",
      "..|.H"
  };
  ASSERT_EQ(2, fewest_crossings(map));
}
TEST(TEST_NAME, Example5)
{
  auto map = std::vector<std::string>{
      "H|.|.|.|.|.|.|.|.|.|.|.|.|.",
      "F|F|F|F|F|F|F|F|F|F|F|F|F|-",
      "S|.|.|.|.|.|.|.|.|.|.|.|.|."
  };
  ASSERT_EQ(27, fewest_crossings(map));
}
TEST(TEST_NAME, Example6)
{
  auto map = std::vector<std::string>{
      "S-H"
  };
  ASSERT_EQ(-1, fewest_crossings(map));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
