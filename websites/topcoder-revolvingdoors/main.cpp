#include "gtest/gtest.h"

#include <string>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto map = std::vector<std::string>{
      "    ### ",
      "    #E# ",
      "   ## # ",
      "####  ##",
      "# S -O-#",
      "# ###  #",
      "#      #",
      "########"
  };
  ASSERT_EQ(2, turns(map));
}
TEST(TEST_NAME, Example1)
{
  auto map = std::vector<std::string>{
      "#### ",
      "#S|##",
      "# O #",
      "##|E#",
      " ####"
  };
  ASSERT_EQ(32, turns(map));
}
TEST(TEST_NAME, Example2)
{
  auto map = std::vector<std::string>{
      " |  |  |     |  |  |  |  |  | ",
      " O  O EO -O- O  O  O  O  OS O ",
      " |  |  |     |  |  |  |  |  | "
  };
  ASSERT_EQ(7, turns(map));
}
TEST(TEST_NAME, Example3)
{
  auto map = std::vector<std::string>{
      "###########",
      "#    #    #",
      "#  S | E  #",
      "#    O    #",
      "#    |    #",
      "#         #",
      "###########"
  };
  ASSERT_EQ(0, turns(map));
}
TEST(TEST_NAME, Example4)
{
  auto map = std::vector<std::string>{
      "        E",
      "    |    ",
      "    O    ",
      "    |    ",
      " -O-S-O- ",
      "    |    ",
      "    O    ",
      "    |    ",
      "         "
  };
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Example5)
{
  auto map = std::vector<std::string>{
      "##E#   ",
      "#  ##  ",
      " -O-## ",
      " #  ## ",
      " ##  ##",
      "  -O-  ",
      "##  ## ",
      " # ### ",
      " #  S  "
  };
  ASSERT_EQ(5, turns(map));
}
TEST(TEST_NAME, Example6)
{
  auto map = std::vector<std::string>{
      "#############",
      "#  #|##|#   #",
      "#   O  O    #",
      "# E || || S #",
      "#    O  O   #",
      "#   #|##|#  #",
      "#############"
  };
  ASSERT_EQ(4, turns(map));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

