#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <stack>
#include <tuple>

// HanoiTower objects

struct GAssert
{
  static inline bool expect(bool condition) { EXPECT_TRUE(condition); return condition; };
};
struct RcAssert
{
  static inline bool expect(bool condition) { RC_ASSERT(condition); return condition; };
};

template <class AssertSystem = GAssert>
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
    if (! AssertSystem::expect(tower_id < 3)) return std::size_t();
    return towers[tower_id].size();
  }

  unsigned int head_of(const std::size_t tower_id) const
  {
    EXPECT_TRUE(tower_id < 3);
    return towers[tower_id].top();
  }

  void move(const std::size_t dest, const std::size_t from)
  {
    if (! AssertSystem::expect(dest < 3)) return;
    if (! AssertSystem::expect(from < 3)) return;
    if (! AssertSystem::expect(dest != from)) return;
    if (! AssertSystem::expect(! towers[from].empty())) return;
    if (! AssertSystem::expect(towers[dest].empty() || towers[dest].top() > towers[from].top())) return;

    towers[dest].push(towers[from].top());
    towers[from].pop();
  }

  void assert_done()
  {
    if (! AssertSystem::expect(towers[0].empty())) return;
    if (! AssertSystem::expect(towers[1].empty())) return;
    //by implementation towers[2] contains all the disks (maybe zero if empty hanoi)
  }
};

// Algorithm to be tested
  
template <int from, int other, int to>
struct ApplyMapping
{
  std::pair<std::size_t, std::size_t> operator()(std::pair<std::size_t, std::size_t> const& move)
  {
    static_assert(from != other && other != to && to != from, "Sticks must have different IDs");
    static_assert(from == 0 || other == 0 || to == 0, "Stick #0 not found");
    static_assert(from == 1 || other == 1 || to == 1, "Stick #1 not found");
    static_assert(from == 2 || other == 2 || to == 2, "Stick #2 not found");

    return std::make_pair(move.first == 0 ? from : (move.first == 1 ? other : to), move.second == 0 ? from : (move.second == 1 ? other : to));
  }
};

template <class T>
void hanoi_iterative_no_stack(HanoiTower<T>& tower)
{

  if (tower.height_of(0) == 0)
  {
    return;
  }
  
  const unsigned int height = tower.height_of(0);
  std::vector<std::pair<std::size_t, std::size_t>> moves;
  moves.reserve((2 << height) -1); // Solution contains 2 ^ height -1 moves at the end of the execution
  
  for (unsigned int i = 1 ; i != height+1 ; ++i)
  {
    // At the beginning of this iteration we have:
    // - moves: contains the list of moves necessary to move a HanoiTower of size (i-1)
    //          from 0 to 2 (stick id)

    std::size_t size_previous = moves.size();
    moves.push_back(std::make_pair(0, 2));

    std::copy(moves.begin(), std::next(moves.begin(), size_previous), std::back_inserter(moves));
    std::transform(moves.begin(), std::next(moves.begin(), size_previous), moves.begin(), ApplyMapping<0,2,1>()); // we move a tower of size (i-1) from stick #0 to stick #1
    std::transform(std::next(moves.begin(), size_previous+1), moves.end(), std::next(moves.begin(), size_previous+1), ApplyMapping<1,0,2>()); // we move a tower of size (i-1) from stick #1 to stick #2
  }

  for (auto const& move : moves)
  {
    tower.move(move.second, move.first);
  }
}

template <class T>
void hanoi_iterative(HanoiTower<T>& tower)
{
  if (tower.height_of(0) == 0)
  {
    return;
  }

  std::stack<std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>> helper;
  helper.emplace(0, 1, 2, tower.height_of(0));
  while (! helper.empty())
  {
    auto current = std::move(helper.top());
    helper.pop();
  
    const std::size_t from = std::get<0>(current);
    const std::size_t other = std::get<1>(current);
    const std::size_t to = std::get<2>(current);
    const std::size_t num_to_move = std::get<3>(current);
    
    if (num_to_move == 1)
    {
      tower.move(to, from);
    }
    else
    {
      helper.emplace(other, from, to, num_to_move -1);
      helper.emplace(from, other, to, 1);
      helper.emplace(from, to, other, num_to_move -1);
    }
  }
}

template <class T>
void hanoi_recurse_helper(HanoiTower<T>& tower, std::size_t from, std::size_t other, std::size_t to, std::size_t num_to_move)
{
  if (num_to_move == 0)
  {
    return;
  }
  else
  {
    hanoi_recurse_helper(tower, from, to, other, num_to_move -1);
    tower.move(to, from);
    hanoi_recurse_helper(tower, other, from, to, num_to_move -1);
  }
}

template <class T>
void hanoi_recurse(HanoiTower<T>& tower)
{
  hanoi_recurse_helper(tower, 0, 1, 2, tower.height_of(0));
}

template <class T>
inline void hanoi(HanoiTower<T>& tower)
{
#ifdef ITERATIVE
  #define ALGO HanoiTowers_ITERATIVE
  return hanoi_iterative(tower);
#elif ITERATIVE_NO_STACK
  #define ALGO HanoiTowers_ITERATIVE_NO_STACK
  return hanoi_iterative_no_stack(tower);
#else
  #define ALGO HanoiTowers_DEFAULT
  return hanoi_recurse(tower);
#endif
}

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

