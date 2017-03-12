#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyArray)
{
  ASSERT_EQ(0, largest(std::vector<unsigned>{}));
}
TEST(TEST_NAME, WebsiteExample)
{
  ASSERT_EQ(10, largest(std::vector<unsigned>{2,1,5,6,2,3}));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
