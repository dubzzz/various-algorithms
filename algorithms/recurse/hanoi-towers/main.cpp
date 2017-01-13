#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include "hanoi_impl.hpp"
#include SPECIFIC_HEADER

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

TEST(ALGO, NoTower)
{
  HanoiTower<GAssert> tower(0);
  hanoi(tower);
  tower.assert_done();
}

TEST(ALGO, OneDisk)
{
  HanoiTower<GAssert> tower(1);
  hanoi(tower);
  tower.assert_done();
}

TEST(ALGO, TwoDisks)
{
  HanoiTower<GAssert> tower(2);
  hanoi(tower);
  tower.assert_done();
}

TEST(ALGO, FiveDisks)
{
  HanoiTower<GAssert> tower(5);
  hanoi(tower);
  tower.assert_done();
}

RC_GTEST_PROP(ALGO, RandomNumberOfDisks, ())
{
  unsigned short height = *rc::gen::inRange(0, 20);
  HanoiTower<RcAssert> tower(height);
  hanoi(tower);
  tower.assert_done();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

