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

#ifdef ENABLE_EXTENDED
TEST(TEST_NAME, Extended0)
{
  auto favorites = std::vector<std::string>{"1 2 3", "0 1 2", "0 1", "2 0000000000000000000000000000000000000000000002"};
  ASSERT_EQ(17, calculate_time(favorites));
}
TEST(TEST_NAME, Extended1)
{
  auto favorites = std::vector<std::string>{"2", "10", "12", "1", "5", "14", "7", "6", "13", "2", "9", "3", "11", "8", "0"};
  ASSERT_EQ(158, calculate_time(favorites));
}
TEST(TEST_NAME, Extended2)
{
  auto favorites = std::vector<std::string>{"2", "10", "12", "1", "5", "14", "7", "6", "13", "9", "3", "11", "8", "0", "4"};
  ASSERT_EQ(173, calculate_time(favorites));
}
TEST(TEST_NAME, Extended3)
{
  auto favorites = std::vector<std::string>{"2 8", "10 7 0", "12 2", "1 6", "5 4", "14 9", "7 8 1", "6 11 14", "13 10", "9 13", "3 5", "11 1", "8 13 2", "0 3", "4 12"};
  ASSERT_EQ(119, calculate_time(favorites));
}
TEST(TEST_NAME, Extended4)
{
  auto favorites = std::vector<std::string>{"9", "1 2", "2 0 6", "7 4", "0 9 1 9 4", "3 0 3 2 0", "6 4 6 8 3", "3 4 9 6 7", "5 3", "2 2 1 3 9", "0 0 1 9"};
  ASSERT_EQ(68, calculate_time(favorites));
}
TEST(TEST_NAME, Extended5)
{
  auto favorites = std::vector<std::string>{"3", "8", "1 4 10 4 0", "2 5", "6 9 8", "4 12 11 13", "3 5", "2", "5 4 7", "11", "9", "10 3 1 9 7", "5 1", "7 7 8 9 6", "0 6"};
  ASSERT_EQ(108, calculate_time(favorites));
}
TEST(TEST_NAME, Extended6)
{
  auto favorites = std::vector<std::string>{"5 0", "12", "9 8", "12", "5", "3 1 9 7 5", "5 6 9", "8", "8 6 2 1", "0 6 11 5", "6", "10", "9 8", "11"};
  ASSERT_EQ(136, calculate_time(favorites));
}
TEST(TEST_NAME, Extended7)
{
  auto favorites = std::vector<std::string>{"6 6 11", "11 8 13", "0 0 12 6", "8 1 0 7 0", "8 2 4", "8", "8 5 13", "2 4", "6", "0 6 7 0", "9 13", "7 14 6 10 5", "14 1 14", "14 2 0 11", "9 9 4 5"};
  ASSERT_EQ(91, calculate_time(favorites));
}
TEST(TEST_NAME, Extended8)
{
  auto favorites = std::vector<std::string>{"3 7 10 2", "0", "1", "5 8 7 10 0", "8 0 3 9", "9 2", "10 11", "5 2 10 5", "4 11 12 12", "9 6", "0 5 3 5 7", "7 6", "12 4 9 4", "3 4"};
  ASSERT_EQ(89, calculate_time(favorites));
}
TEST(TEST_NAME, Extended9)
{
  auto favorites = std::vector<std::string>{"3 7", "0", "9 7", "5 8", "1", "14 12 10 1", "0 7", "3", "3 11 3 11", "3", "14 4", "3 1 3", "11 14 1 2", "11 12", "11 0 0"};
  ASSERT_EQ(108, calculate_time(favorites));
}
TEST(TEST_NAME, Extended10)
{
  auto favorites = std::vector<std::string>{"10 9 0 3 9", "2 0 5 9 2", "0", "4 1 4 8 3", "4", "9", "3", "1 0 4 10 4", "7 9", "10 6 7 8 3", "7 9 10", "2 3 2 4 3"};
  ASSERT_EQ(87, calculate_time(favorites));
}
TEST(TEST_NAME, Extended11)
{
  auto favorites = std::vector<std::string>{"7 5 11", "4 10", "11 8", "11 8 11 7 0", "0 8 10 1 4", "2 3 2 0", "1 3 4", "10 4 11", "8 3", "11 8", "3 9", "8", "8"};
  ASSERT_EQ(83, calculate_time(favorites));
}
TEST(TEST_NAME, Extended12)
{
  auto favorites = std::vector<std::string>{"9 4 1 13 11", "8", "14", "7 7", "13 14 9 7", "5 2 4 3", "1", "1 0", "6", "8", "9", "3 8 12 14", "8 4", "7 6", "6 0"};
  ASSERT_EQ(123, calculate_time(favorites));
}
TEST(TEST_NAME, Extended13)
{
  auto favorites = std::vector<std::string>{"14 12", "13 10 12", "12 12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1", "0"};
  ASSERT_EQ(236, calculate_time(favorites));
}
TEST(TEST_NAME, Extended14)
{
  auto favorites = std::vector<std::string>{"9", "12", "12", "6", "11", "13", "5", "5", "7", "8", "6", "3", "10", "3"};
  ASSERT_EQ(171, calculate_time(favorites));
}
TEST(TEST_NAME, Extended15)
{
  auto favorites = std::vector<std::string>{"1", "10", "8", "0", "9", "5", "2", "11", "14", "2", "1", "9", "7", "14", "1"};
  ASSERT_EQ(204, calculate_time(favorites));
}
TEST(TEST_NAME, Extended16)
{
  auto favorites = std::vector<std::string>{"0 1 2 3 4 5 6 7 10 11 12 14", "0 1 2 3 5 8 12", "0 1 2 3 4 5 7 8 11 12 13 14", "0 1 5 7 8 9 10 11 12 13 14", "2 3 5 6 7 10 12 13 14", "0 1 2 3 5 6 7 9 11 13 14", "0 1 2 4 5 6 7 8 10 12", "0 1 2 3 4 5 6 7 9 11 13", "0 1 3 7 8 9 10 11 13 14", "0 2 3 5 8 11 12", "1 2 3 4 5 6 7 9 11 13 14", "0 1 3 4 5 6 9 10 11 12 14", "0 2 7 10 12", "1 2 3 5 8 10 11 12 13 14", "3 8 9 10 11 12"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended17)
{
  auto favorites = std::vector<std::string>{"1 2 7 9 12 13 14", "1 2 3 4 7 9 11 12 13 14", "3 5 8 10 11 12 13 14", "0 4 6 7 13 14", "2 4 6 7 9 10 11", "0 2 6 7 8 14", "1 3 4 7 8 11 12 14", "0 1 2 3 4 5 14", "2 6 8 9 11 13", "0 2 3 6 7 10 13", "1 2 3 8 9 11 13", "1 2 3 6 7 8 9 11 12 13 14", "0 1 3 4 6 9 10 13 14", "0 6 10 12 13", "1 2 3 6 8 9 13"};
  ASSERT_EQ(41, calculate_time(favorites));
}
TEST(TEST_NAME, Extended18)
{
  auto favorites = std::vector<std::string>{"1 2 7 9 12 13 14", "1 2 3 4 7 9 11 12 13 14", "3 5 8 10 11 12 13 14", "0 4 6 7 13 14", "2 4 6 7 9 10 11", "0 2 6 7 8 14", "1 3 4 7 8 11 12 14", "0 1 2 3 4 5 14", "2 6 8 9 11 13", "0 2 3 6 7 10 13", "1 2 3 8 9 11 13", "1 2 3 6 7 8 9 11 12 13 14", "0 1 3 4 6 9 10 13 14", "0 6 10 12 13", "1 2 3 6 8 9 13"};
  ASSERT_EQ(41, calculate_time(favorites));
}
TEST(TEST_NAME, Extended19)
{
  auto favorites = std::vector<std::string>{"1 2 3 4 5 6 7 8 10 12 14", "0 2 4 5 7 8 9 13", "0 1 2 3 4 5 6 7 9 10 11 12 14", "0 1 5 7 8 9 11 13 14", "1 4 5 6 9 10 13", "1 3 5 6 7 8 9 10 12 14", "0 5 7 8 9 13", "1 2 3 4 6 7 11 12 13", "0 6 7 8 10 11 12 14", "0 1 2 5 9 11 12 14", "0 3 5 8 10 11 12 13 14", "2 3 4 5 6 7 8 9 10 12 13 14", "0 1 2 3 4 7 8 9 10 13 14", "0 2 3 4 5 6 7 8 9 10 11 13 14", "0 1 4 5 6 7 8 9 11 12"};
  ASSERT_EQ(36, calculate_time(favorites));
}
TEST(TEST_NAME, Extended20)
{
  auto favorites = std::vector<std::string>{"2", "0", "11", "2", "13", "5", "13", "2", "14", "5", "6", "11", "6", "0", "7"};
  ASSERT_EQ(156, calculate_time(favorites));
}
TEST(TEST_NAME, Extended21)
{
  auto favorites = std::vector<std::string>{"4 7", "8 10", "2 10 14", "10", "6", "14", "2 9 13", "4 10 13", "6 8 12 13", "0 3 13", "5 6", "1", "1", "7 8 12 14", "4 12"};
  ASSERT_EQ(124, calculate_time(favorites));
}
TEST(TEST_NAME, Extended22)
{
  auto favorites = std::vector<std::string>{"4 7", "8 10", "2 10 14", "10", "6", "14", "2 9 13", "4 10 13", "6 8 12 13", "0 3 13", "5 6", "1", "1", "7 8 12 14", "4 12"};
  ASSERT_EQ(124, calculate_time(favorites));
}
TEST(TEST_NAME, Extended23)
{
  auto favorites = std::vector<std::string>{"1 8 10", "7 8 11", "7 10", "2 13", "8 12 13", "3 10 12", "2 12", "4 11 12", "0 1 8 11", "5 7 8 12", "5 9 11", "8 10", "0 13", "12 13 14", "1 3 11 12"};
  ASSERT_EQ(103, calculate_time(favorites));
}
TEST(TEST_NAME, Extended24)
{
  auto favorites = std::vector<std::string>{"2", "1 4 14", "5 8 13", "9", "8 11", "14", "4 7", "6", "2 4", "0", "5", "5 13", "5 8 11", "8", "4"};
  ASSERT_EQ(141, calculate_time(favorites));
}
TEST(TEST_NAME, Extended25)
{
  auto favorites = std::vector<std::string>{"1 3 5 11", "0 3 5 6 7 8 10 13 14", "0 1 3 8 9", "1 4 9", "10 14", "4 7 9 12 13", "8", "3 4 7", "8 14", "2 10", "2 7 12", "3 8 11", "0 2 6 14", "3 5 9", "1 5 9 12"};
  ASSERT_EQ(85, calculate_time(favorites));
}
TEST(TEST_NAME, Extended26)
{
  auto favorites = std::vector<std::string>{"0 2 5 8 14", "6 7", "0 1 4 5 8", "4 9 11 12", "5 13", "1 4 8 10", "10", "0 1 4 13", "3 11", "0 6 8 9", "7 14", "1 9", "3 4 11", "0 1 3 12", "3 4 6 9"};
  ASSERT_EQ(86, calculate_time(favorites));
}
TEST(TEST_NAME, Extended27)
{
  auto favorites = std::vector<std::string>{"1 2 10 12 14", "1 12", "0 2 3 4 5 6 9 13", "2 4 9 13", "0 2 4 6 8 9 10 13 14", "0 1 10 12 13", "3 4 5 7 9 13", "0 1 3 4 10 12 14", "2 5 8 10 12 13 14", "1 6 10", "1 7 12", "2 3 6 8 12", "7 14", "3 5 11 14", "2 8 10"};
  ASSERT_EQ(56, calculate_time(favorites));
}
TEST(TEST_NAME, Extended28)
{
  auto favorites = std::vector<std::string>{"1 4 5 7 8 9 11 12 13", "0 1 2 4 5 6 7 9 12 13", "1 4 5 6 8 9 10 11 12 13 14", "1 4 5 6 7 8 9 10 11 12 13 14", "1 2 3 4 5 6 8 10 12", "0 1 2 3 4 5 6 7 9 10 11 12", "2 4 5 10 12 13", "0 1 2 5 6 8 9 10 11 12 13 14", "0 6 7 8 9 10 11 12 13", "0 1 3 4 5 6 7 12 13", "2 3 4 5 8 9 10 11 13", "1 2 3 4 5 6 8 10 12 13 14", "0 1 2 3 4 5 9 10 12 13", "1 3 4 5 10 11 14", "0 4 5 6 9 10"};
  ASSERT_EQ(36, calculate_time(favorites));
}
TEST(TEST_NAME, Extended29)
{
  auto favorites = std::vector<std::string>{"11", "1 2 3 5 7 8 9 10", "0 2 3 4 5 8 9 13", "2 4 5 6 9 11", "1 5 7 8 9 11", "0 3 5 6", "1 3 4 5 6 9", "0 1 4 5 6 10 11 12 13", "4 8 9 10 12", "0 3 7 8 9 10", "1 6 9 12 13", "3 4 8 9 10 12 14", "6 7 8 9 12 14", "0 1 2 4 10 11 14", "0 2 5 9 13 14"};
  ASSERT_EQ(54, calculate_time(favorites));
}
TEST(TEST_NAME, Extended30)
{
  auto favorites = std::vector<std::string>{"2 3 4 5 6 7 8 10 13 14", "0 2 3 4 5 6 7 8 9 10 11 13 14", "0 3 4 6 7 8 10 11 12", "0 1 3 4 5 6 7 8 9 10 11 13 14", "0 1 2 3 4 5 7 8 9 10 11 12 13 14", "0 1 3 4 5 7 8 12 14", "0 1 4 5 6 7 9 10 11 12 13 14", "0 1 3 4 5 7 12 13 14", "0 1 3 4 6 7 8 10 11 12 13 14", "0 1 2 5 6 7 9 10 11 12 13 14", "0 1 2 3 5 6 7 9 11 13 14", "0 1 2 3 4 5 6 7 8 10 11 12 14", "0 1 4 5 6 8 10 12 13 14", "1 2 3 4 5 6 7 9 11 14", "0 1 2 6 11 12 14"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended31)
{
  auto favorites = std::vector<std::string>{"2 4 8 10 11 12", "7 9", "2 3 4 5 6 7 8", "1 5 6 7 8 12 13 14", "6 7 10 12 14", "0 2 10 11", "4 9 11 12 13", "1 4 8 10 11 12 14", "3 6 12 13 14", "1 5 7 9 12", "0 3 7 8 9 11 12 13", "0 2 4 6 8 10 13", "0 1 4 5 9 10 11 12", "0 1 2 3 4 6 8 10 11 12", "3 4 5 6 9 10 11 13 14"};
  ASSERT_EQ(54, calculate_time(favorites));
}
TEST(TEST_NAME, Extended32)
{
  auto favorites = std::vector<std::string>{"0 1 2 6 13", "1 4 6 7 8 11 12 14", "0 1 2 3 5 6 8 13", "0 1 2 3 5 6 7 9 10 12 14", "2 3 4 8 13 14", "4 5 7 10 12", "0 3 4 7 8 10 11 13 14", "0 1 2 3 5 6 7 9 10 13 14", "0 3 5 6 7 8 9 11 12 13 14", "1 2 3 4 5 8 10 11", "2 4 8 9 10 14", "0 2 4 8 10 11 12 13 14", "0 1 2 3 6 9 10 11 12 13", "2 3 4 6 7 8 9 11 12", "1 2 3 5 7 8 9 10 11 12 14"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended33)
{
  auto favorites = std::vector<std::string>{"0 1 2 3 4 5 6 7 8 9 10 11 13 14", "0 1 3 4 6 7 9 10 11 12 13 14", "0 1 3 5 6 7 8 9 10 12", "0 1 2 3 5 6 7 8 10 12 13 14", "0 1 3 4 8 9 12", "0 1 3 4 5 10 12 13", "0 3 4 7 8 9 11 12 13", "0 1 2 3 4 5 7 8 9 12 13", "0 1 2 4 5 8 9 11 14", "0 2 3 4 6 7 8 9 10 12 13 14", "0 2 3 4 5 6 7 9 11 12 13 14", "0 1 2 3 5 6 7 10", "0 4 5 6 7 9 10 11 12 14", "1 2 3 4 5 6 7 8 9 11 12 13 14", "0 2 4 6 7 8 9 10 11 12 13 14"};
  ASSERT_EQ(35, calculate_time(favorites));
}
TEST(TEST_NAME, Extended34)
{
  auto favorites = std::vector<std::string>{"8", "1 2 9 10 11 14", "1 6 10 14", "1 3 5 6 11 12", "7 8 10 12", "0 1 6 7 9", "1 5 6 9 11", "6 11", "6 10 12 13", "1 6", "10 11", "0 3 10", "2 9", "0 3 7 11 13", "2 12"};
  ASSERT_EQ(89, calculate_time(favorites));
}
TEST(TEST_NAME, Extended35)
{
  auto favorites = std::vector<std::string>{"1 2 3 5 8 10 14", "2 4 5 7 10 11 12 14", "0 1 2 3 5 6 9 10 14", "1 2 5 7 9 13 14", "1 2 5 6 9 10 11 12 13", "0 1 2 4 8 11 13 14", "0 8 9 10 12", "0 1 9 10", "6 8 9 11 13", "1 4 5 6 8 10 11", "6 7 8 12 13", "1 2 3 5 6 11 12", "1 3 4", "0 1 2 4 10 13", "0 4 5 7 10 11 12"};
  ASSERT_EQ(52, calculate_time(favorites));
}
TEST(TEST_NAME, Extended36)
{
  auto favorites = std::vector<std::string>{"10", "6 7 8 14", "1", "4 9", "0 4 8 13", "2 5 8 14", "1 3 9", "5 8", "1 2 4 9 10 12 14", "1 5 8 10 11", "4", "3 5 8 12", "0 2 5 11 12", "0 2 13", "1 4 10"};
  ASSERT_EQ(106, calculate_time(favorites));
}
TEST(TEST_NAME, Extended37)
{
  auto favorites = std::vector<std::string>{"1 2 5 6 8 9 10 11 12", "0 1 8 9 10 11 12", "2 3 4 6 10 11 12 14", "1 7 9 10 11", "2 3 7 12 13 14", "1 2 3 4 5 6 9", "1 2 3 4 7 9 10 14", "1 3 4 6 9 10 11 12", "0 2 6 7 10 11 14", "2 4 6 8 10 11", "0 4 5 7 10", "1 2 3 8 14", "5 11 12 13", "1 4 5 6 10 11 12 13", "0 2 4 13"};
  ASSERT_EQ(51, calculate_time(favorites));
}
TEST(TEST_NAME, Extended38)
{
  auto favorites = std::vector<std::string>{"1 2 3 5 6 7 9 10 11 12 13 14", "0 2 4 5 6 7 8 9 10 14", "1 2 3 4 5 6 8 9 12 13 14", "0 2 3 4 7 8 9 10 11 12 13 14", "0 1 2 4 5 6 7 8 9 10 11 12 13", "1 2 3 4 5 6 7 8 9 10 11 12 13", "0 1 2 4 5 7 8 9 10 13 14", "0 1 2 4 5 6 8 9 11 12 13 14", "0 1 3 4 5 6 9 11 13", "1 2 3 5 6 7 10 13 14", "0 3 5 6 7 8 9 10 12 14", "0 1 3 4 5 6 7 8 9 10 12 13", "0 1 3 4 5 7 11 12 13 14", "0 1 2 3 4 5 7 9 10 12", "0 4 5 6 7 8 10 13"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended39)
{
  auto favorites = std::vector<std::string>{"2 3 4 7 10 12 13", "0 1 3 6 7 8 10 12 13 14", "0 1 2 3 6 7 8 10 13 14", "0 1 2 3 4 5 6 7 8 9 10 11 13 14", "1 3 4 5 9 10 11 12 13 14", "0 1 2 4 5 6 12 14", "0 1 2 4 5 6 7 10 11 12 13 14", "0 1 2 5 6 8 11 12 14", "0 2 4 5 6 7 9 10 11 12 13 14", "2 3 5 6 8 9 11 13 14", "0 1 2 3 4 6 8 9 11 12 13", "0 4 5 6 7 8 9 11 13", "0 1 2 4 5 6 7 8 11", "0 1 2 3 6 9 10 11 12 13 14", "1 4 8 13 14"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended40)
{
  auto favorites = std::vector<std::string>{"0 2 8 10 11 13", "0 2 3 5 7 9 10 11", "4 7 9 10 12", "0 1 3 5 7", "2 3 5 6 7 11 14", "2 6 8 10 11 13", "2 6 11 12", "3 5 7 11 14", "1 4 6 9", "0 2 6 8 13", "0 2 3 4 6 7 8", "1 2 3 5 7 10 14", "0 2 3 4 8 11 12 13", "4 5 7 9 11", "2 3 6 8 10 12"};
  ASSERT_EQ(53, calculate_time(favorites));
}
TEST(TEST_NAME, Extended41)
{
  auto favorites = std::vector<std::string>{"0 2 3 5 6 9 10 11 12 13 14", "1 2 3 5 6 7 9 11 12 13", "1 4 6 8 9 10 11 12 14", "0 1 2 3 4 5 6 7 8 9 11 12 13 14", "0 1 2 3 4 6 7 8 9 10 11 12 14", "0 1 2 3 4 5 6 7 8 9 12 13 14", "0 1 2 3 4 5 7 10 11 12 13 14", "0 1 2 3 4 5 6 7 8 9 10 12 14", "0 1 2 3 4 7 9 10 11 13 14", "0 2 3 4 5 6 7 10 11 12 14", "0 2 3 4 5 6 7 8 9 10 13", "0 1 2 3 4 5 6 7 8 9 10 12", "0 1 2 3 4 5 6 7 8 10 11 12 13 14", "2 3 4 6 8 9 13 14", "1 2 3 4 6 8 11 12 13 14"};
  ASSERT_EQ(35, calculate_time(favorites));
}
TEST(TEST_NAME, Extended42)
{
  auto favorites = std::vector<std::string>{"2 4 9 10 11", "8", "0 1 12", "1 2 3 6 7 9 11 14", "0 1 2 3 7 8 9 12 13", "3 5 12 13", "2 3 7 13", "0 2 6 7 9 10 14", "0 7 8 14", "0 2 6 8 9 11", "1 7 9 12", "1 4 8 9", "3 6 7 8 9 11 12", "0 1 4 7 8", "1"};
  ASSERT_EQ(73, calculate_time(favorites));
}
TEST(TEST_NAME, Extended43)
{
  auto favorites = std::vector<std::string>{"3 5 8 10 13", "5 10 12 14", "1 2 3 4 5 9 10 11 12", "1 6 7 10 12", "1 3 8 9 11 12", "2 7 8 12 14", "1 5 7 13", "2 3 5 8 9 11 13", "0 7 8 9 12", "2 7 8 9 11 14", "0 1 4 7 10 11 13", "1 3 6 8 9 11 12", "0 6 7 12 14", "3 6 9 10 11 12 13", "0 1 3 11 12 13"};
  ASSERT_EQ(54, calculate_time(favorites));
}
TEST(TEST_NAME, Extended44)
{
  auto favorites = std::vector<std::string>{"0 1 2 5 6 7 8 9 11 13", "0 2 3 4 6 7 8 9 11 12 14", "0 2 3 5 6 7 8 11 13 14", "0 1 3 4 5 6 9 11 12 14", "1 2 3 4 5 6 7 9 14", "1 2 3 5 7 9 12 13", "1 2 3 4 5 7 8 9 10 11 13 14", "0 1 2 3 4 6 8 10 12 14", "3 4 5 6 8 9 10 11 14", "0 2 4 6 7 8 9 11 13 14", "1 3 5 6 7 8 10 11 13 14", "1 4 5 6 7 8 9 10 11 13 14", "4 5 6 7 8 9 10 11 12 13 14", "0 1 3 4 5 6 7 8 9 10 12", "0 1 3 4 5 6 7 8 9 10 11"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended45)
{
  auto favorites = std::vector<std::string>{"0 1 2 3 5 6 7 8 9 10 11 14", "0 1 2 3 5 9 10 12 13 14", "2 3 5 8 9 10 12", "0 1 2 5 6 7 10 11", "1 5 9 10 12 14", "0 2 3 4 6 7 8 9 11 12 13", "0 2 3 5 7 10 12 14", "0 1 2 5 7 9 10 11 12 13 14", "0 1 4 5 7 8 11 12 13", "0 2 4 6 7 8 9 11 12 13 14", "1 2 3 4 7 8 10 11 12 13 14", "0 1 2 5 6 7 8 10 11 14", "0 1 2 5 6 7 11 13", "0 6 8 9 10 11 12", "0 1 3 4 5 6 9 10 11 12 14"};
  ASSERT_EQ(37, calculate_time(favorites));
}
TEST(TEST_NAME, Extended46)
{
  auto favorites = std::vector<std::string>{"1 2 3 4 7 8 9", "1 3 5 11 12 13", "0 1 4 10 11 12", "5 9 12 13", "1 2 3 5 8 11 12 13 14", "5 7 9 10 14", "0 3 5 13 14", "9 10 11 13 14", "1 2 8 11 12 14", "2 3 5 6 8 11 12 13 14", "2 3 6 10 11 13", "0 5 7 11", "2 3 4 6 8 9 11", "0 2 6 9 13 14", "2 11 14"};
  ASSERT_EQ(51, calculate_time(favorites));
}
TEST(TEST_NAME, Extended47)
{
  auto favorites = std::vector<std::string>{"1 3 4", "2 6 11", "2 3 4 12", "1 6 8", "0 8 10 14", "4 5 6 8", "3 6 8 10", "0 8 10 11 13 14", "1 4", "0 7 11 12 13", "13 14", "0", "1 3", "9 11 14", "0 2 14"};
  ASSERT_EQ(72, calculate_time(favorites));
}
TEST(TEST_NAME, Extended48)
{
  auto favorites = std::vector<std::string>{"1 2 4 5 6 7 9 10 11 12 13 14", "1 2 3 5 6 7 8 9 10 11 12 13 14", "0 1 3 5 7 9 10 11 12 13 14", "0 1 2 3 4 5 7 8 9 10 11 12 13", "0 1 2 3 4 5 6 7 8 9 10 11 12 14", "0 1 2 3 4 5 7 8 9 10 11 13 14", "0 2 3 4 5 6 7 8 9 11 12 13 14", "0 1 3 4 5 6 7 9 11 12 13 14", "1 2 4 5 6 7 8 9 10 11 12 14", "0 1 2 4 5 7 8 10 11 12 13 14", "0 1 2 3 4 5 7 9 10 11 12 13", "0 1 2 3 4 5 7 8 9 11 12 14", "1 2 3 4 5 6 9 10 11 12 13 14", "0 1 2 3 4 7 9 10 11 12 13 14", "1 2 4 5 6 7 9 11"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended49)
{
  auto favorites = std::vector<std::string>{"0 1 2 3 7 8 9 10 12 13 14", "0 1 2 3 4 5 6 8 10 14", "0 1 2 3 4 5 6 9 10 11 12 13 14", "2 3 5 6 7 9 10 11 14", "0 1 2 3 4 5 6 7 8 10 14", "0 2 3 4 5 7 8 9 10 11 12 13 14", "0 1 3 4 5 7 9 10 12 13 14", "0 1 2 3 4 9 10 11 13 14", "0 1 2 3 5 6 8 9 10 11 12 13 14", "0 1 3 4 7 8 11 12 14", "0 1 3 5 7 9 10 13 14", "0 3 6 7 9 13", "0 1 2 3 4 5 6 8 9 11 12 13 14", "0 2 3 5 6 7 8 10 11 12 13 14", "0 1 3 4 5 6 9 10 11 12"};
  ASSERT_EQ(35, calculate_time(favorites));
}
TEST(TEST_NAME, Extended50)
{
  auto favorites = std::vector<std::string>{"7 8 11", "0 13", "1 5 9 14", "1 10", "0 9 11", "7 12 13 14", "1 5 8 10 11", "3 4 7 9 13", "0 2 8 10", "1 7 11 14", "3 8 10", "1 7 9 12 13", "2 7 8 9", "1 3 4 11 13 14", "5 6 8 11 12"};
  ASSERT_EQ(70, calculate_time(favorites));
}
TEST(TEST_NAME, Extended51)
{
  auto favorites = std::vector<std::string>{"1 5 7 10 12", "1 3 5 6 8 9", "1 4 5 6 7 9 10 12 14", "0 2 5 6 13 14", "0 1 2 3 9 11 13", "1 2 5 10 13", "4 8 13", "0 2 4 5 8 10 12", "0 8 9 14", "0 1 3 7 8 11", "1 5 9 11", "2 3 7 12", "1 3 4 7 9 12 13 14", "0 1 3 4 5 7 11 14", "0 1 5 9 10 14"};
  ASSERT_EQ(53, calculate_time(favorites));
}
TEST(TEST_NAME, Extended52)
{
  auto favorites = std::vector<std::string>{"1 3 6 7 8 9 10 11 12 13 14", "0 1 2 3 4 6 7 8 11 12 13 14", "0 1 2 4 5 6 7 8 10 13", "0 2 8 10 11 12", "0 1 2 3 4 5 7 9 11 13", "0 1 2 3 4 5 7 8 9 10 12", "0 1 4 5 6 7 8 14", "0 1 3 5 6 7 8 9 12 13 14", "0 2 3 4 5 6 7 9 10 11", "0 4 6 7 8 9 11", "0 1 2 4 5 6 7 13", "0 1 2 3 5 6 7 8 9 10 11", "0 1 2 3 5 6 7 9 10 12 13 14", "0 2 5 7 8 9 12", "1 3 4 6 7 8 9 11 12 13 14"};
  ASSERT_EQ(35, calculate_time(favorites));
}
TEST(TEST_NAME, Extended53)
{
  auto favorites = std::vector<std::string>{"2 3 6 8 10 11 14", "0 1 2 3 4 6 7 11 13", "1 2 3 4 6 10 11 14", "0 1 2 4 5 8 9 10 14", "0 3 8 9 11 13", "0 1 2 6 13", "1 2 5 7 8 9 10 12", "0 2 6 12 14", "1 2 3 4 7 8 9 13 14", "0 1 2 4 6 7 9 12 14", "2 3 6 7 8 10 13 14", "0 2 5 8 9 10 12 14", "0 3 7 10 13 14", "0 3 4 5 8 9 11", "0 3 4 7 8 9 10 12 13 14"};
  ASSERT_EQ(51, calculate_time(favorites));
}
TEST(TEST_NAME, Extended54)
{
  auto favorites = std::vector<std::string>{"1 2 3 6 8 9 11 12 13", "0 2 4 8 9 10 11 13", "0 2 3 6 7 10 12 14", "2 3 4 6 7 8 11 12 13", "0 1 2 3 4 5 10 11 12 13 14", "2 4 5 9 10", "0 2 3 6 7 9 10 12 13", "0 1 2 5 7 11 12 13 14", "0 1 2 5 7 9 11 13 14", "0 1 3 4 8 9 10 11 13 14", "1 3 8 9 10 11 14", "0 1 2 3 5 6 10 11 12", "0 1 3 7 8 9 10 11 12 14", "0 1 2 6 7 9 11", "1 3 4 7 9"};
  ASSERT_EQ(36, calculate_time(favorites));
}
TEST(TEST_NAME, Extended55)
{
  auto favorites = std::vector<std::string>{"0 1 4 5 6 7 8 9 10 12 13", "0 1 2 3 4 7 8 13 14", "0 1 3 4 5 6 7 8 10 12 13", "1 2 3 5 6 7 8 9 11 12 13 14", "0 1 2 4 5 6 9 11 12 13", "3 5 6 8 9 10 12 13 14", "0 1 3 5 6 8 10 11 12 13 14", "1 2 3 4 5 6 9 10 11 12 13 14", "0 1 2 3 4 5 6 7 9 10 11 12 14", "1 2 3 4 5 6 7 8 9 10 11 13 14", "0 2 3 4 5 7 8 9 11 13", "2 3 4 5 6 7 8 9 11 12", "0 1 2 3 4 7 10 11 12 13", "0 1 3 4 5 6 8 9 10 12 13 14", "1 3 4 5 8 9 11"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended56)
{
  auto favorites = std::vector<std::string>{"2 3 6 7 10 11 12", "0 1 2 3 4 5 6 8 9 10 11 13 14", "0 3 5 6 7 8 9 11 12", "1 2 3 4 6 7 9 10 11 12 13 14", "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14", "0 1 2 3 4 6 7 8 9 10 14", "0 1 2 3 4 5 7 8 9 11 12 14", "0 1 2 3 4 5 6 8 9 11 12", "0 1 2 3 5 6 7 8 9 10 12 13 14", "0 1 2 3 6 9 10 11 12 14", "1 2 3 4 5 6 7 9 12 13 14", "1 3 4 5 6 7 8 9 10 11 12 13", "0 2 5 6 7 8 9 10 11 13 14", "2 3 7 8 9 10 11 12 13 14", "0 2 3 4 5 7 10 11 12 14"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended57)
{
  auto favorites = std::vector<std::string>{"0 1 3 7 9 10", "0 1 2 5 7 8 9 10 13", "0 5 7 9 12", "0 4 11 13", "0 4 6 9 11", "0 1 2 3 4 5 6 8 11", "0 2 5 11 13", "0 1 2 3 4 5 7 13", "0 1 2 3 5 6 7 9 11 12 13", "1 2 6 7 10 11 12 14", "0 1 4 5 7 9 10 14", "0 2 5 6 7 10 13", "0 1 2 4 5 6 7 8 10 11 12", "1 2 4 6 9 10 11 12 13", "5 7 12 13 14"};
  ASSERT_EQ(54, calculate_time(favorites));
}
TEST(TEST_NAME, Extended58)
{
  auto favorites = std::vector<std::string>{"3 4 6 7 8 9 10 13 14", "0 2 3 7 10 11 12 13 14", "3 5 6 7 9 10 12 13 14", "0 1 2 3 5 6 7 8 9 10 11 12 13 14", "0 2 7 8 12 13 14", "0 1 2 3 4 6 7 9 11 12 13 14", "1 5 6 7 8 9 10 11 14", "1 2 3 4 5 8 10 11 13 14", "0 1 2 3 4 5 6 9 10 11 12 14", "1 2 3 6 7 9 10 11 12 14", "0 1 3 5 6 7 8 9 10 11 12 13 14", "0 2 3 4 5 7 8 9 11 13 14", "2 3 5 6 7 8 10 12 13 14", "1 2 5 6 7 8 9 10 12 13", "0 2 3 6 8 10 11 12 13 14"};
  ASSERT_EQ(35, calculate_time(favorites));
}
TEST(TEST_NAME, Extended59)
{
  auto favorites = std::vector<std::string>{"1 5 6 7 10 11 13 14", "0 1 2 3 4 5 6 7 8 10 11 12 14", "0 1 2 3 5 8 9 11 12", "0 5 6 7 8 10 11 12 14", "0 1 2 3 4 5 6 7 8 9 11 14", "0 3 4 5 6 8 13 14", "1 2 5 6 7 9 10 11 13 14", "0 1 2 4 5 9 11 12 13 14", "0 1 2 3 5 6 8 9 11 12 14", "0 3 4 6 7 8 9 10 11 12 13 14", "1 3 4 6 8 9 10 11 12 13 14", "0 2 3 4 5 6 8 9 11 13 14", "0 3 5 8 9 12", "0 1 4 5 8 9 10 11 13 14", "0 1 2 4 5 6 7 8 9 10 11 14"};
  ASSERT_EQ(35, calculate_time(favorites));
}
TEST(TEST_NAME, Extended60)
{
  auto favorites = std::vector<std::string>{"2 10", "2 3 10 14", "2 8 10 11", "3 6", "4 5 11 12 14", "11", "0 3 4", "7 11", "1 5 6 7 11", "10", "2 5 8 11 12", "0 12", "7 11 14", "8 12", "1 4 8 9 11 14"};
  ASSERT_EQ(90, calculate_time(favorites));
}
TEST(TEST_NAME, Extended61)
{
  auto favorites = std::vector<std::string>{"0 1 2 3 4 5 6 10 12 13 14", "0 3 4 6 7 8 9 10 12 14", "1 3 4 7 8 9 11 12 13 14", "2 3 5 6 8 10 11 13 14", "0 2 4 5 6 7 8 9 10 13", "1 2 3 4 6 9 10 11 14", "1 2 3 4 6 7 8 9 11 12 13 14", "1 3 6 9 10 11 12 14", "0 1 2 3 4 5 7 8 9 11 12 13 14", "1 3 4 6 7 8 9 11 12 13 14", "0 1 2 4 6 7 8 9 10 12 13 14", "0 3 5 6 8 9 12 13 14", "1 4 5 6 7 8 9 10 12 13", "0 1 2 4 6 7 8 9 12 13 14", "3 8 9 10"};
  ASSERT_EQ(36, calculate_time(favorites));
}
TEST(TEST_NAME, Extended62)
{
  auto favorites = std::vector<std::string>{"0 1 4 5 6 7 8 9 10 11 13 14", "0 2 4 6 7 8 9 10 12 13", "0 2 4 5 6 7 9 10 11 13", "0 1 4 5 6 8 11 12 13 14", "0 1 2 4 6 7 11 12 13 14", "0 1 2 3 4 6 7 8 10 11 12 13 14", "1 3 4 5 6 7 8 9 10 11 12", "2 3 4 6 7 8 10 11 13 14", "1 2 3 5 6 8 9 10 11 13 14", "0 1 3 4 5 10 11 12 13", "0 1 3 5 6 7 9 10 11 12 13 14", "0 2 3 4 7 8 9 13", "0 1 2 3 4 5 7 8 10 12 13 14", "0 2 3 4 5 6 9 10 11 13", "0 1 2 3 4 6 8 10 11 12 13"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended63)
{
  auto favorites = std::vector<std::string>{"0 2 3 4 6 7 11 14", "1 3 4 6 7 8 9 10 12 13 14", "0 1 3 5 6 7 8 9 10 12 14", "0 2 3 4 6 7 8 9 10 11 12 13 14", "0 1 2 3 4 5 6 9 10 13 14", "0 1 2 3 4 5 6 8 9 10 12 13 14", "1 2 4 7 8 9 11 12", "1 2 3 4 6 7 9 10 13 14", "1 2 3 4 5 7 9 12 13 14", "0 1 2 4 5 6 7 9 11 12 14", "0 4 5 7 8 9 10 13 14", "1 2 3 4 5 7 8 9 10 11 13 14", "0 1 3 6 7 8 9 10 11 13", "0 1 2 3 4 5 6 7 8 11", "0 1 2 3 4 6 8 9 10 11 13 14"};
  ASSERT_EQ(34, calculate_time(favorites));
}
TEST(TEST_NAME, Extended64)
{
  auto favorites = std::vector<std::string>{"1 4 6 9 10 11", "1 5 7 8 12 13 14", "2 4 5 7 10 11", "6 8 9", "0 1 4 5 7 8 9 12 13", "2 4 5 8 9 10 13", "0 2 3 7 8 11 13", "2 5 6 10 11 12", "0 1 4 7 10 11 13 14", "2 3 7 10 11", "1 10", "2 4 5 9 13", "2 4 8 10", "0 7 9", "0 2 4 6 10 13 14"};
  ASSERT_EQ(54, calculate_time(favorites));
}
TEST(TEST_NAME, Extended65)
{
  auto favorites = std::vector<std::string>{"5", "6", "1 2 6", "1 6", "1 3 4", "0 1 4", "1 3"};
  ASSERT_EQ(51, calculate_time(favorites));
}
TEST(TEST_NAME, Extended66)
{
  auto favorites = std::vector<std::string>{"0 1", "3", "0 3", "0 1 6", "0 3 6", "0", "0 6"};
  ASSERT_EQ(51, calculate_time(favorites));
}
TEST(TEST_NAME, Extended67)
{
  auto favorites = std::vector<std::string>{"14", "13", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1", "0"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended68)
{
  auto favorites = std::vector<std::string>{"7", "6", "5", "4", "3", "2", "1", "0", "14", "13", "12", "11", "10", "9", "8"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended69)
{
  auto favorites = std::vector<std::string>{"2", "0", "7", "1", "4", "2", "9", "3", "12", "4", "1", "3", "6", "14", "7"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended70)
{
  auto favorites = std::vector<std::string>{"2", "4", "7", "3", "8", "6", "1", "6", "0", "7", "4", "7", "3", "6", "11"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended71)
{
  auto favorites = std::vector<std::string>{"2", "9", "1", "13", "1", "8", "0", "7", "0", "10", "14", "1", "3", "9", "12"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended72)
{
  auto favorites = std::vector<std::string>{"2", "9", "9", "4", "10", "14", "9", "2", "4", "7", "10", "10", "1", "10", "4"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended73)
{
  auto favorites = std::vector<std::string>{"2", "10", "14", "11", "0", "8", "12", "5", "13", "13", "5", "12", "12", "12", "6"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended74)
{
  auto favorites = std::vector<std::string>{"2", "13", "7", "2", "4", "6", "1", "3", "11", "7", "2", "2", "6", "2", "7"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended75)
{
  auto favorites = std::vector<std::string>{"2", "13", "7", "7", "3", "13", "9", "1", "4", "4", "11", "9", "4", "13", "5"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended76)
{
  auto favorites = std::vector<std::string>{"2", "13", "7", "7", "11", "1", "14", "6", "14", "3", "8", "12", "7", "13", "2"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended77)
{
  auto favorites = std::vector<std::string>{"4", "1", "3", "6", "3", "7", "2", "4", "2", "7", "3", "3", "3", "8", "4"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended78)
{
  auto favorites = std::vector<std::string>{"4", "1", "3", "10", "14", "11", "9", "4", "4", "14", "4", "13", "10", "12", "7"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended79)
{
  auto favorites = std::vector<std::string>{"4", "9", "13", "10", "3", "11", "8", "10", "3", "3", "10", "12", "9", "11", "4"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended80)
{
  auto favorites = std::vector<std::string>{"4", "13", "10", "6", "9", "1", "4", "13", "8", "8", "5", "12", "14", "5", "8"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended81)
{
  auto favorites = std::vector<std::string>{"6", "1", "6", "2", "11", "2", "8", "3", "3", "10", "3", "1", "6", "11", "2"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended82)
{
  auto favorites = std::vector<std::string>{"6", "3", "3", "12", "9", "13", "4", "4", "8", "8", "14", "3", "0", "9", "9"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended83)
{
  auto favorites = std::vector<std::string>{"6", "3", "7", "7", "3", "3", "6", "10", "3", "6", "3", "5", "8", "5", "0"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended84)
{
  auto favorites = std::vector<std::string>{"6", "4", "6", "13", "5", "5", "13", "4", "6", "8", "3", "1", "6", "9", "1"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended85)
{
  auto favorites = std::vector<std::string>{"6", "14", "12", "0", "9", "7", "13", "10", "12", "2", "6", "12", "12", "12", "8"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended86)
{
  auto favorites = std::vector<std::string>{"8", "0", "8", "6", "0", "7", "11", "7", "3", "6", "11", "9", "1", "5", "8"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended87)
{
  auto favorites = std::vector<std::string>{"8", "5", "11", "13", "7", "12", "3", "8", "10", "5", "10", "1", "10", "12", "5"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended88)
{
  auto favorites = std::vector<std::string>{"8", "12", "9", "2", "5", "9", "6", "10", "10", "7", "0", "8", "3", "8", "8"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended89)
{
  auto favorites = std::vector<std::string>{"12", "0", "6", "11", "0", "12", "7", "2", "10", "12", "0", "9", "3", "13", "8"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended90)
{
  auto favorites = std::vector<std::string>{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"};
  ASSERT_EQ(253, calculate_time(favorites));
}
TEST(TEST_NAME, Extended91)
{
  auto favorites = std::vector<std::string>{"7", "9", "5", "0", "1", "2", "000000000014", "8", "4", "3", "6", "2", "00000000013", "00000000011", "000000012"};
  ASSERT_EQ(157, calculate_time(favorites));
}
TEST(TEST_NAME, Extended92)
{
  auto favorites = std::vector<std::string>{"5", "8", "14", "12", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1", "0"};
  ASSERT_EQ(204, calculate_time(favorites));
}
TEST(TEST_NAME, Extended93)
{
  auto favorites = std::vector<std::string>{"0 1", "0"};
  ASSERT_EQ(17, calculate_time(favorites));
}
TEST(TEST_NAME, Extended94)
{
  auto favorites = std::vector<std::string>{"0 1 2 5 6 8", "2 3 4 7 9 11", "9 7", "9 7", "9 7", "9 7", "9 7", "9 7", "9 7", "9 7", "9 7", "9 7", "9 7", "9 7"};
  ASSERT_EQ(106, calculate_time(favorites));
}
TEST(TEST_NAME, Extended95)
{
  auto favorites = std::vector<std::string>{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"};
  ASSERT_EQ(219, calculate_time(favorites));
}
TEST(TEST_NAME, Extended96)
{
  auto favorites = std::vector<std::string>{"01", "1"};
  ASSERT_EQ(32, calculate_time(favorites));
}
TEST(TEST_NAME, Extended97)
{
  auto favorites = std::vector<std::string>{"0", "2", "2", "4", "0"};
  ASSERT_EQ(32, calculate_time(favorites));
}
TEST(TEST_NAME, Extended98)
{
  auto favorites = std::vector<std::string>{"0 004", "2 3", "0 01", "1 2 3 4", "1 1", "6 3 6", "6 8 9", "11", "13 14", "10 11 12 14", "1 14 13", "2 14", "13 3", "5 7 8", "6"};
  ASSERT_EQ(109, calculate_time(favorites));
}
#endif

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
