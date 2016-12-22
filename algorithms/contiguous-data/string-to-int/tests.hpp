#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <sstream>
#include <type_traits>
#include <string>

// Implements string_to_int, string_to_long, string_to_longlong
// to convert input strings to respectively int, long, long long
// Input strings assumptions:
// - contains only figures valid for the base (0-9 and a-z) or - (only possible for first element)
// - never empty
// - always valid entries (no overflow)
// - null terminated

// string_to_* accept an optional parameters for the base (must be defaulted to 10 - maximum value is 36)

// Functions must be defined as constexpr for char*
// and normal functions for std::string

// Algorithm to be tested
// int string_to_int(const char*, unsigned base=10)
// int string_to_int(std::string const&, unsigned base=10)
// long string_to_long(const char*, unsigned base=10)
// long string_to_long(std::string const&, unsigned base=10)
// long long string_to_longlong(const char*, unsigned base=10)
// long long string_to_longlong(std::string const&, unsigned base=10)

// Constexpr tests

// check output type
static_assert(std::is_same<int, decltype(string_to_int(""))>::value, "atoi :: must return int");
static_assert(std::is_same<long, decltype(string_to_long(""))>::value, "atol :: must return long");
static_assert(std::is_same<long long, decltype(string_to_longlong(""))>::value, "atoll :: must return long long");

// base 10
static_assert(string_to_int("1") == 1, "atoi :: 1 digit number <positive>");
static_assert(string_to_int("15") == 15, "atoi :: 2 digits number <positive>");
static_assert(string_to_int("-42") == -42, "atoi :: negative number");

// base 16
static_assert(string_to_int("e", 16) == 14, "atoi(base:16) :: 1 digit number <positive>");
static_assert(string_to_int("ff", 16) == 255, "atoi(base:16) :: 2 digits number <positive>");
static_assert(string_to_int("-ffff", 16) == -65535, "atoi(base:16) :: negative number");

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

