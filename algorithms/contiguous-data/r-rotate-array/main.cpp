#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyArray)
{
  auto expected = std::vector<int>{};
  ASSERT_EQ(expected, r_rotate(std::vector<int>{}, 5));
}
TEST(TEST_NAME, KandNPrimesTogether)
{
  auto expected = std::vector<int>{5,6,7,1,2,3,4};
  ASSERT_EQ(expected, r_rotate(std::vector<int>{1,2,3,4,5,6,7}, 3));
}
TEST(TEST_NAME, KandNnotPrimesTogether)
{
  auto expected = std::vector<int>{7,8,9,1,2,3,4,5,6};
  ASSERT_EQ(expected, r_rotate(std::vector<int>{1,2,3,4,5,6,7,8,9}, 3));
}

RC_GTEST_PROP(TEST_NAME, InAndOutHaveTheSameSize, (std::vector<int> const& in, std::size_t k))
{
  auto out = r_rotate(in, k);
  RC_ASSERT(out.size() == in.size());
}
RC_GTEST_PROP(TEST_NAME, KStepsToTheRight, (std::vector<int> const& in, std::size_t k))
{
  auto out = r_rotate(in, k);
  for (std::size_t idx {} ; idx != in.size() ; ++idx)
  {
    RC_ASSERT(out[(idx+k)%in.size()] == in[idx]);
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
