#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <cstddef>

// Algorithm to be tested

// Inspired from CodinGame: https://www.codingame.com/training/medium/shadows-of-the-knight-episode-1

// Given an instance of Space<number_dimensions>, space, having dimensions space.dimensions()
// you need to find as quickly as possible the position of an hidden tale
// at each turn you can std::array<Where,number_dimensions> guess(std::array<int,number_dimensions>)

struct GAssert
{
  static inline ::testing::AssertionResult apply(const char*, const char*, bool condition, std::string const& msg)
  {
    if (condition) { return ::testing::AssertionSuccess(); }
    else { return ::testing::AssertionFailure() << msg; }
  }
  static inline bool expect(bool condition, std::string const& msg) { EXPECT_PRED_FORMAT2(apply, condition, msg.c_str()); return condition; };
};
struct RcAssert
{
  static inline bool expect(bool condition, std::string const& /*msg*/) { RC_ASSERT(condition); return condition; };
};

// Running tests

TEST(TEST_NAME, 2DSpaceIsAPoint)
{
  Space<2, GAssert> space({{1, 1}}, {{0, 0}});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

TEST(TEST_NAME, 2DSpaceIsALine)
{
  Space<2, GAssert> space({{10, 1}}, {{9, 0}});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

TEST(TEST_NAME, 2DSpaceIsAColumn)
{
  Space<2, GAssert> space({{1, 10}}, {{0, 9}});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

TEST(TEST_NAME, 2DSpace)
{
  Space<2, GAssert> space({{1000, 1000}}, {{1, 1}});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

RC_GTEST_PROP(TEST_NAME, Random2DSpace, (std::size_t const& w, std::size_t const &h))
{
  RC_PRE(w > static_cast<std::size_t>(0) && h > static_cast<std::size_t>(0));
  std::size_t x = *rc::gen::inRange(std::size_t(), w);
  std::size_t y = *rc::gen::inRange(std::size_t(), h);
    
  Space<2, RcAssert> space({{w, h}}, {{x, y}});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

