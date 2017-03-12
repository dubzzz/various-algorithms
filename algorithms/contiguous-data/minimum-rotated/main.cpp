#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, NotRotated)
{
  ASSERT_EQ(1, min_rotated(std::vector<int>{1,6,10,99}));
}
TEST(TEST_NAME, RotatedArray)
{
  ASSERT_EQ(2, min_rotated(std::vector<int>{105,109,2,6,10,99}));
}
TEST(TEST_NAME, RotatedWithDuplicates)
{
  ASSERT_EQ(-1, min_rotated(std::vector<int>{99,99,105,1000,-1,-1,-1,6,6,10,99}));
}

RC_GTEST_PROP(TEST_NAME, MinimumOfTheRotatedArray, (std::vector<int> const& in, std::size_t k))
{
  RC_PRE(! in.empty());
  
  std::vector<int> sorted = in;
  std::sort(sorted.begin(), sorted.end());
  
  std::vector<int> rotated(sorted.size());
  for (std::size_t idx {} ; idx != sorted.size() ; ++idx)
  {
    rotated[(idx+k)%sorted.size()] = sorted[idx];
  }
  RC_ASSERT(sorted[0] == min_rotated(rotated));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
