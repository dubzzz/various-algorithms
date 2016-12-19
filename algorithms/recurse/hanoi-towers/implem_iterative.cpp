#include <stack>
#include <tuple>

#include "hanoi.hpp"

// Algorithm to be tested
  
template <class T>
void hanoi(HanoiTower<T>& tower)
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

#include "tests.hpp"

