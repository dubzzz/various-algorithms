#include "hanoi.hpp"

// Algorithm to be tested
  
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
void hanoi(HanoiTower<T>& tower)
{
  hanoi_recurse_helper(tower, 0, 1, 2, tower.height_of(0));
}

#include "tests.hpp"

