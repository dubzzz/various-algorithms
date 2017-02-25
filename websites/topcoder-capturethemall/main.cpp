#include "gtest/gtest.h"

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  ASSERT_EQ(2, fast_knight("a1", "b3", "c5"));
}
TEST(TEST_NAME, Example1)
{
  ASSERT_EQ(3, fast_knight("b1", "c3", "a3"));
}
TEST(TEST_NAME, Example2)
{
  ASSERT_EQ(6, fast_knight("a1", "a2", "b2"));
}
TEST(TEST_NAME, Example3)
{
  ASSERT_EQ(3, fast_knight("a5", "b7", "e4"));
}
TEST(TEST_NAME, Example4)
{
  ASSERT_EQ(6, fast_knight("h8", "e2", "d2"));
}

TEST(TEST_NAME, Extended0)
{
  ASSERT_EQ(8, fast_knight("a1", "h8", "b2"));
}
TEST(TEST_NAME, Extended1)
{
  ASSERT_EQ(8, fast_knight("a1", "h8", "b1"));
}
TEST(TEST_NAME, Extended2)
{
  ASSERT_EQ(10, fast_knight("a1", "a8", "h8"));
}
TEST(TEST_NAME, Extended3)
{
  ASSERT_EQ(6, fast_knight("c8", "g6", "b7"));
}
TEST(TEST_NAME, Extended4)
{
  ASSERT_EQ(7, fast_knight("f5", "c1", "a3"));
}
TEST(TEST_NAME, Extended5)
{
  ASSERT_EQ(8, fast_knight("b2", "h4", "a1"));
}
TEST(TEST_NAME, Extended6)
{
  ASSERT_EQ(5, fast_knight("b6", "d3", "a5"));
}
TEST(TEST_NAME, Extended7)
{
  ASSERT_EQ(4, fast_knight("g7", "e3", "h6"));
}
TEST(TEST_NAME, Extended8)
{
  ASSERT_EQ(7, fast_knight("g2", "g7", "h8"));
}
TEST(TEST_NAME, Extended9)
{
  ASSERT_EQ(3, fast_knight("e4", "c3", "g1"));
}
TEST(TEST_NAME, Extended10)
{
  ASSERT_EQ(6, fast_knight("d1", "f1", "a8"));
}
TEST(TEST_NAME, Extended11)
{
  ASSERT_EQ(5, fast_knight("c3", "e6", "g6"));
}
TEST(TEST_NAME, Extended12)
{
  ASSERT_EQ(6, fast_knight("d2", "f4", "d8"));
}
TEST(TEST_NAME, Extended13)
{
  ASSERT_EQ(4, fast_knight("f1", "e4", "f5"));
}
TEST(TEST_NAME, Extended14)
{
  ASSERT_EQ(5, fast_knight("e3", "b2", "d7"));
}
TEST(TEST_NAME, Extended15)
{
  ASSERT_EQ(7, fast_knight("e8", "g3", "b6"));
}
TEST(TEST_NAME, Extended16)
{
  ASSERT_EQ(5, fast_knight("d1", "f5", "b8"));
}
TEST(TEST_NAME, Extended17)
{
  ASSERT_EQ(7, fast_knight("b8", "f3", "d1"));
}
TEST(TEST_NAME, Extended18)
{
  ASSERT_EQ(6, fast_knight("h6", "b8", "g5"));
}
TEST(TEST_NAME, Extended19)
{
  ASSERT_EQ(7, fast_knight("b2", "g4", "b5"));
}
TEST(TEST_NAME, Extended20)
{
  ASSERT_EQ(5, fast_knight("f4", "c5", "f7"));
}
TEST(TEST_NAME, Extended21)
{
  ASSERT_EQ(6, fast_knight("f4", "a3", "g1"));
}
TEST(TEST_NAME, Extended22)
{
  ASSERT_EQ(8, fast_knight("e6", "d1", "h8"));
}
TEST(TEST_NAME, Extended23)
{
  ASSERT_EQ(5, fast_knight("e3", "d3", "g3"));
}
TEST(TEST_NAME, Extended24)
{
  ASSERT_EQ(6, fast_knight("d3", "h3", "f5"));
}
TEST(TEST_NAME, Extended25)
{
  ASSERT_EQ(4, fast_knight("b7", "g4", "e8"));
}
TEST(TEST_NAME, Extended26)
{
  ASSERT_EQ(7, fast_knight("a8", "e1", "e2"));
}
TEST(TEST_NAME, Extended27)
{
  ASSERT_EQ(5, fast_knight("g6", "f2", "g1"));
}
TEST(TEST_NAME, Extended28)
{
  ASSERT_EQ(6, fast_knight("a6", "c8", "c3"));
}
TEST(TEST_NAME, Extended29)
{
  ASSERT_EQ(5, fast_knight("b6", "g6", "e6"));
}
TEST(TEST_NAME, Extended30)
{
  ASSERT_EQ(5, fast_knight("c2", "a1", "g7"));
}
TEST(TEST_NAME, Extended31)
{
  ASSERT_EQ(5, fast_knight("b1", "e1", "a4"));
}
TEST(TEST_NAME, Extended32)
{
  ASSERT_EQ(5, fast_knight("g6", "e1", "d2"));
}
TEST(TEST_NAME, Extended33)
{
  ASSERT_EQ(3, fast_knight("f3", "d2", "e5"));
}
TEST(TEST_NAME, Extended34)
{
  ASSERT_EQ(6, fast_knight("f2", "e8", "f8"));
}
TEST(TEST_NAME, Extended35)
{
  ASSERT_EQ(5, fast_knight("b3", "b8", "d8"));
}
TEST(TEST_NAME, Extended36)
{
  ASSERT_EQ(6, fast_knight("a6", "a4", "h1"));
}
TEST(TEST_NAME, Extended37)
{
  ASSERT_EQ(6, fast_knight("h3", "b7", "d2"));
}
TEST(TEST_NAME, Extended38)
{
  ASSERT_EQ(2, fast_knight("f5", "d4", "e6"));
}
TEST(TEST_NAME, Extended39)
{
  ASSERT_EQ(3, fast_knight("g7", "e6", "e4"));
}
TEST(TEST_NAME, Extended40)
{
  ASSERT_EQ(5, fast_knight("b6", "e8", "b2"));
}
TEST(TEST_NAME, Extended41)
{
  ASSERT_EQ(4, fast_knight("e6", "e3", "d1"));
}
TEST(TEST_NAME, Extended42)
{
  ASSERT_EQ(4, fast_knight("f5", "e6", "g2"));
}
TEST(TEST_NAME, Extended43)
{
  ASSERT_EQ(6, fast_knight("h8", "e2", "d2"));
}
TEST(TEST_NAME, Extended44)
{
  ASSERT_EQ(11, fast_knight("a1", "h1", "a8"));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
