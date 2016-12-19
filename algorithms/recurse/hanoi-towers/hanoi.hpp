#include <stdexcept>
#include <stack>

// HanoiTower objects

struct too_many_iterations : std::length_error
{
  too_many_iterations(const char* s) : std::length_error(s) {}
  too_many_iterations(std::string const& s) : std::length_error(s) {}
};

template <class AssertSystem>
class HanoiTower
{
  std::stack<unsigned int> towers[3];
  unsigned long long remaining_moves_allowed;

public:
  HanoiTower() = delete;
  HanoiTower(HanoiTower const&) = delete;
  HanoiTower(HanoiTower&&) = delete;
  HanoiTower& operator=(HanoiTower const&) = delete;
  HanoiTower& operator=(HanoiTower&&) = delete;

  HanoiTower(const unsigned short height)//max height allowed: 64
      : towers()
      , remaining_moves_allowed((1 << height) -1) // there is a solution having 2^height -1 moves
  {
    for (unsigned short i = 0 ; i != height ; ++i)
    {
      towers[0].push(height -i);
    }
  }

  std::size_t height_of(const std::size_t tower_id) const
  {
    if (! AssertSystem::expect(tower_id < 3, "Tower id must be in the range 0-2")) return std::size_t();
    return towers[tower_id].size();
  }

  unsigned int head_of(const std::size_t tower_id) const
  {
    if (! AssertSystem::expect(tower_id < 2, "Tower id must be in the range 0-2")) return 0;
    return towers[tower_id].top();
  }

  void move(const std::size_t dest, const std::size_t from)
  {
    if (! AssertSystem::expect(dest < 3, "Destination id must be in the range 0-2")) return;
    if (! AssertSystem::expect(from < 3, "Source id must be in the range 0-2")) return;
    if (! AssertSystem::expect(dest != from, "Unable to move to itself, destination must be different from source")) return;
    if (! AssertSystem::expect(! towers[from].empty(), "No disk in the source")) return;
    if (! AssertSystem::expect(towers[dest].empty() || towers[dest].top() > towers[from].top(), "Disk is too large to be inserted on the top of destination")) return;
    if (! AssertSystem::expect(remaining_moves_allowed-- != 0, "Too many iterations to solve this Hanoi Tower problem")) throw too_many_iterations("Too many iterations to solve this Hanoi Tower problem");

    towers[dest].push(towers[from].top());
    towers[from].pop();
  }

  void assert_done()
  {
    if (! AssertSystem::expect(towers[0].empty(), "Problem not solved tower #0 still has disks")) return;
    if (! AssertSystem::expect(towers[1].empty(), "Problem not solved tower #1 still has disks")) return;
    //by implementation towers[2] contains all the disks (maybe zero if empty hanoi)
  }
};

