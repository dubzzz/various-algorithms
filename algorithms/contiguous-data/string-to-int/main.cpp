#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <sstream>
#include <type_traits>
#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Zero)
{
  ASSERT_EQ(0, string_to_int("0"));
}

TEST(TEST_NAME, PositiveNumber)
{
  ASSERT_EQ(42, string_to_int("42"));
}

TEST(TEST_NAME, NegativeNumber)
{
  ASSERT_EQ(-42, string_to_int("-42"));
}

TEST(TEST_NAME, PositiveNumberSmallCustomBase)
{
  ASSERT_EQ(8, string_to_int("10", 8));
}

TEST(TEST_NAME, NegativeNumberSmallCustomBase)
{
  ASSERT_EQ(-8, string_to_int("-10", 8));
}

TEST(TEST_NAME, PositiveNumberLargeCustomBase)
{
  ASSERT_EQ(255, string_to_int("ff", 16));
}

RC_GTEST_PROP(TEST_NAME, RandomNumberBase8, (int value))
{
  std::ostringstream oss;
  if (value >= 0)
  {
    oss << std::oct << value;
  }
  else
  {
    oss << std::oct << '-' << -value;
  }
  RC_ASSERT(string_to_int(oss.str(), 8) == value);
}

RC_GTEST_PROP(TEST_NAME, RandomNumberBase10, (int value))
{
  std::ostringstream oss;
  oss << std::dec << value;
  RC_ASSERT(string_to_int(oss.str()) == value);
}

RC_GTEST_PROP(TEST_NAME, RandomNumberBase16, (int value))
{
  std::ostringstream oss;
  if (value >= 0)
  {
    oss << std::hex << value;
  }
  else
  {
    oss << std::hex << '-' << -value;
  }
  RC_ASSERT(string_to_int(oss.str(), 16) == value);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
