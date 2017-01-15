#include <algorithm>
#include <iterator>
#include <vector>

#include "ihanoi.hpp"
#include "aim.hpp"

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

void hanoi(IHanoi& tower)
{

  if (tower.height_of(0) == 0)
  {
    return;
  }
  
  const unsigned int height = tower.height_of(0);
  std::vector<std::pair<std::size_t, std::size_t>> moves;
  moves.reserve((1 << height) -1); // Solution contains 2 ^ height -1 moves at the end of the execution
  
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

