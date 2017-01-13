#include "ihanoi.hpp"
#include "aim.hpp"

// Algorithm to be tested
  
void hanoi_recurse_helper(IHanoi& tower, std::size_t from, std::size_t other, std::size_t to, std::size_t num_to_move)
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

void hanoi(IHanoi& tower)
{
  hanoi_recurse_helper(tower, 0, 1, 2, tower.height_of(0));
}

