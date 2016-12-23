#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

// Rebuild Hanoi tower correctly
// The towers are labeled 0, 1 and 2
// The aim is to move all the disks of 0 towards 2 by following the rules below:
// - one disk can be moved by step
// - a disk cannot be moved onto a smaller one
// HanoiTower<T> API has the following interface:
// - Number of disks in the tower: std::size_t height_of(const std::size_t tower_id) const
// - Size of the disk on the top of the tower: unsigned int head_of(const std::size_t tower_id) const
// - Take top disk of from and move it towards to: void move(const std::size_t dest, const std::size_t from)
// Start your file by #include "hanoi.hpp"

// Algorithm to be tested:
// template <class T> inline void hanoi(HanoiTower<T>& tower)

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

