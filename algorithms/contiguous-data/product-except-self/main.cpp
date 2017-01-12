#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, OneElementArray)
{
  std::vector<int> expected { 1 };
  ASSERT_EQ(expected, product_except({ 42 }));
}

TEST(TEST_NAME, ExampleCase)
{
  std::vector<int> expected { 24, 12, 8, 6 };
  ASSERT_EQ(expected, product_except({{ 1, 2, 3, 4 }}));
}

RC_GTEST_PROP(TEST_NAME, HasSizeOfInput, (std::vector<int> in))
{
  RC_ASSERT(in.size() == product_except(in).size());
}

RC_GTEST_PROP(TEST_NAME, CheckValues, (std::vector<int> const& in))
{
  auto compute_without = [](auto tab, std::size_t without_id)
  {
    tab.erase(std::next(std::begin(tab), without_id));
    return std::accumulate(std::begin(tab), std::end(tab), 1, [](auto acc, auto cur) { return acc * cur; });
  };
  
  int n {};
  std::vector<int> expected;
  std::generate_n(std::back_inserter(expected), in.size(), [&](){ return compute_without(in, n++); });
  
  RC_ASSERT(expected == product_except(in));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
