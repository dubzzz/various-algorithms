#include "gtest/gtest.h"

#include <stack>

// HanoiTower objects

class HanoiTower
{
  std::stack<unsigned int> towers[3];

public:
  HanoiTower() = delete;
  HanoiTower(HanoiTower const&) = delete;
  HanoiTower(HanoiTower&&) = delete;
  HanoiTower& operator=(HanoiTower const&) = delete;
  HanoiTower& operator=(HanoiTower&&) = delete;

  HanoiTower(const unsigned short height) : towers()
  {
    for (unsigned short i = 0 ; i != height ; ++i)
    {
      towers[0].push(height -i);
    }
  }

  std::size_t height_of(const std::size_t tower_id) const
  {
    EXPECT_TRUE(tower_id < 3);
    return towers[tower_id].size();
  }

  unsigned int head_of(const std::size_t tower_id) const
  {
    EXPECT_TRUE(tower_id < 3);
    return towers[tower_id].top();
  }

  void move(const std::size_t dest, const std::size_t from)
  {
    ASSERT_TRUE(dest < 3);
    ASSERT_TRUE(from < 3);
    ASSERT_TRUE(dest != from);
    ASSERT_FALSE(towers[from].empty());
    ASSERT_TRUE(towers[dest].empty() || towers[dest].top() > towers[from].top());

    towers[dest].push(towers[from].top());
    towers[from].pop();
  }

  void assert_done()
  {
    ASSERT_TRUE(towers[0].empty());
    ASSERT_TRUE(towers[1].empty());
    ASSERT_FALSE(towers[2].empty()); //by implementation it contains all the disks
  }
};

// Algorithm to be tested

// In-place

void hanoi_recurse(HanoiTower& tower)
{
}

inline void hanoi(HanoiTower& tower)
{
  #define ALGO HanoiTowers_DEFAULT
  return hanoi_recurse(tower);
}

// Running tests

TEST(ALGO, NoTower)
{
  HanoiTower tower(0);
  hanoi(tower);
  tower.assert_done();
}

TEST(ALGO, OneDisk)
{
  HanoiTower tower(1);
  hanoi(tower);
  tower.assert_done();
}

TEST(ALGO, TwoDisks)
{
  HanoiTower tower(2);
  hanoi(tower);
  tower.assert_done();
}

TEST(ALGO, FiveDisks)
{
  HanoiTower tower(5);
  hanoi(tower);
  tower.assert_done();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

