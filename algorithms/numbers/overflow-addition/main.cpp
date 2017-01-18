#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <limits>
#include <random>
#include <vector>

#include SPECIFIC_HEADER

// Running tests


static_assert(sizeof(short) == 2, "short supposed to be on 16 bits");
static_assert(std::numeric_limits<short>::min() == -32768, "short supposed to have min value of -32768");
static_assert(std::numeric_limits<short>::max() == 32767, "short supposed to have max value of 32767");

TEST(TEST_NAME, EmptyArray)
{
  constexpr short tab[] = {};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_FALSE(overflow(tab, length));
}

TEST(TEST_NAME, MaxAndOne)
{
  constexpr short tab[] = {32767, 1};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_TRUE(overflow(tab, length));
}

TEST(TEST_NAME, MaxAndZeros)
{
  constexpr short tab[] = {0, 0, 0, 32767, 0};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_FALSE(overflow(tab, length));
}

TEST(TEST_NAME, MinAndMinusOne)
{
  constexpr short tab[] = {-32768, -1};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_TRUE(overflow(tab, length));
}

TEST(TEST_NAME, MinAndZeros)
{
  constexpr short tab[] = {0, 0, 0, -32768, 0};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_FALSE(overflow(tab, length));
}

TEST(TEST_NAME, SimpleNoOverflow)
{
  constexpr short tab[] = {10, 50, 90, 2};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_FALSE(overflow(tab, length));
}

TEST(TEST_NAME, MixedSignesNoOverflow)
{
  constexpr short tab[] = {10000, 25000, -32768, 4500};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_FALSE(overflow(tab, length));
}

TEST(TEST_NAME, MixedSignesNearMinOverflow)
{
  constexpr short tab[] = {10000, -2768, 25000, -32768, -2232, -30000};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_FALSE(overflow(tab, length));
}

TEST(TEST_NAME, MixedSignesOverflow)
{
  constexpr short tab[] = {10000, -2768, 25000, -32768, -2, 1, -2232, -30000};
  constexpr unsigned length = sizeof(tab)/sizeof(tab[0]);
  ASSERT_TRUE(overflow(tab, length));
}

constexpr int max_generated = 500;
static_assert(static_cast<short>(std::numeric_limits<short>::min() + std::numeric_limits<short>::min()) == 0, "Sum of two negative shorts always >=0");
static_assert(static_cast<short>(std::numeric_limits<short>::max() + std::numeric_limits<short>::max()) == -2, "Sum of two positive shorts always <0");

auto build_positives()
{
  auto max_runs = *rc::gen::inRange(2, max_generated).as("upper bound of number of elements");
  return rc::gen::apply([](std::vector<short> const& helper) {
        std::vector<short> out {};
        short sum {};
        for (auto&& elt : helper)
        {
          if (short(sum + elt) < sum)
          {
            return out;
          }
          out.push_back(elt);
          sum += elt;
        }
        return out;
      }
      , rc::gen::container<std::vector<short>>(max_runs, rc::gen::inRange(short(), std::numeric_limits<short>::max()))).as("array of positives shorts without overflow");
}
auto build_positives_overflow()
{
  auto max_runs = *rc::gen::inRange(2, max_generated).as("upper bound of number of elements");
  short min_value = static_cast<short>(std::numeric_limits<short>::max() / max_runs);
  return rc::gen::apply([](std::vector<short> const& helper) {
        std::vector<short> out {};
        short sum {};
        for (auto&& elt : helper)
        {
          out.push_back(elt);
          if (short(sum + elt) < sum)
          {
            return out;
          }
          sum += elt;
        }
        return out;
      }
      , rc::gen::container<std::vector<short>>(max_runs, rc::gen::inRange(short(min_value +1), std::numeric_limits<short>::max()))).as("array of positives shorts with one overflow");
}

auto build_negatives()
{
  auto max_runs = *rc::gen::inRange(2, max_generated).as("upper bound of number of elements");
  return rc::gen::apply([](std::vector<short> const& helper) {
        std::vector<short> out {};
        short sum {};
        for (auto&& elt : helper)
        {
          if (short(sum + elt) > sum)
          {
            return out;
          }
          out.push_back(elt);
          sum += elt;
        }
        return out;
      }
      , rc::gen::container<std::vector<short>>(max_runs, rc::gen::inRange(std::numeric_limits<short>::min(), short(1)))).as("array of negatives shorts without overflow");
}
auto build_negatives_overflow()
{
  auto max_runs = *rc::gen::inRange(2, max_generated).as("upper bound of number of elements");
  short min_value = static_cast<short>(std::numeric_limits<short>::min() / max_runs);
  return rc::gen::apply([](std::vector<short> const& helper) {
        std::vector<short> out {};
        short sum {};
        for (auto&& elt : helper)
        {
          out.push_back(elt);
          if (short(sum + elt) > sum)
          {
            return out;
          }
          sum += elt;
        }
        return out;
      }
      , rc::gen::container<std::vector<short>>(max_runs, rc::gen::inRange(std::numeric_limits<short>::min(), min_value))).as("array of negatives shorts with one overflow");
}

RC_GTEST_PROP(TEST_NAME, OnlyPositivesNoOverflow, ())
{
  auto&& values = *build_positives();
  RC_ASSERT(! overflow(values.data(), values.size()));
}

RC_GTEST_PROP(TEST_NAME, OnlyNegativesNoOverflow, ())
{
  auto&& values = *build_negatives();
  RC_ASSERT(! overflow(values.data(), values.size()));
}

RC_GTEST_PROP(TEST_NAME, MixedNoOverflow, ())
{
  auto values = *rc::gen::apply([](auto values, auto&& values_neg, unsigned seed)
        {
          values.insert(values.end(), values_neg.begin(), values_neg.end()); // sum in [-32768 ; 32765]
          
          std::mt19937 g(seed);
          std::shuffle(values.begin(), values.end(), g);
          
          return values;
        }
        , build_positives_overflow() // sum in [32767+1 ; 32767+32767] = [32768 ; 65534]
        , build_negatives_overflow() // sum in [-32768-32768 ; -32768-1] = [-65536 ; -32769]
        , rc::gen::arbitrary<unsigned>())
      .as("mixed values no overflow: sum in range [-32768 ; 32765]");
  
  RC_ASSERT(! overflow(values.data(), values.size()));
}

RC_GTEST_PROP(TEST_NAME, OnlyPositivesOverflow, ())
{
  auto&& values = *build_positives_overflow();
  RC_ASSERT(overflow(values.data(), values.size()));
}

RC_GTEST_PROP(TEST_NAME, OnlyNegativesOverflow, ())
{
  auto&& values = *build_negatives_overflow();
  RC_ASSERT(overflow(values.data(), values.size()));
}

RC_GTEST_PROP(TEST_NAME, MixedOverflow, (unsigned seed))
{
  auto values = *rc::gen::apply([](auto values, auto&& values_neg)
        {
          values.insert(values.end(), values_neg.begin(), values_neg.end()); // sum in [-32768 ; 32765]
          return values;
        }
        , build_positives_overflow()  // sum in [32767+1 ; 32767+32767] = [32768 ; 65534]
        , build_negatives_overflow()) // sum in [-32768-32768 ; -32768-1] = [-65536 ; -32769]
      .as("mixed values no overflow: sum in range [-32768 ; 32765]");
  
  if (std::accumulate(values.begin(), values.end() , short()) > 0)
  {
    auto&& values_overflow = *build_positives_overflow();
    values.insert(values.end(), values_overflow.begin(), values_overflow.end());
  }
  else
  {
    auto&& values_overflow = *build_negatives_overflow();
    values.insert(values.end(), values_overflow.begin(), values_overflow.end());
  }
  
  std::mt19937 g(seed);
  std::shuffle(values.begin(), values.end(), g);
  
  RC_ASSERT(overflow(values.data(), values.size()));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

