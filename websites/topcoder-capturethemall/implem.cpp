#include <algorithm>
#include <queue>
#include <set>
#include <string>
#include <utility>

// Algorithm to be tested

using Position = std::pair<int,int>;
unsigned num_moves(Position const& start, Position const& end)
{
  bool visited[8][8];
  std::for_each(visited, visited+8, [](auto line) { std::fill(line, line+8, false); });
  
  std::queue<std::pair<int, Position>> nexts;
  nexts.emplace(0, start);
  while (! nexts.empty())
  {
    auto num_moves = nexts.front().first;
    auto current = nexts.front().second;
    nexts.pop();
    
    if (current == end) { return num_moves; }
    if (current.first < 0 || current.first >= 8) { continue; }
    if (current.second < 0 || current.second >= 8) { continue; }
    if (visited[current.second][current.first]) { continue; }
    
    visited[current.second][current.first] = true;
    ++num_moves;
    
    nexts.emplace(num_moves, std::make_pair(current.first -1, current.second -2));
    nexts.emplace(num_moves, std::make_pair(current.first -1, current.second +2));
    nexts.emplace(num_moves, std::make_pair(current.first +1, current.second -2));
    nexts.emplace(num_moves, std::make_pair(current.first +1, current.second +2));
    nexts.emplace(num_moves, std::make_pair(current.first -2, current.second -1));
    nexts.emplace(num_moves, std::make_pair(current.first -2, current.second +1));
    nexts.emplace(num_moves, std::make_pair(current.first +2, current.second -1));
    nexts.emplace(num_moves, std::make_pair(current.first +2, current.second +1));
  }
  return 0;
}

auto make_pos(std::string const& pos_str) { return std::make_pair((int)(pos_str[0] -'a'), (int)(pos_str[1] -'1')); }

unsigned fast_knight(std::string const& knight, std::string const& rook, std::string const& queen)
{
  auto knight_p = make_pos(knight);
  auto rook_p = make_pos(rook);
  auto queen_p = make_pos(queen);
  
  int rook_first = num_moves(knight_p, rook_p) + num_moves(rook_p, queen_p);
  int queen_first = num_moves(knight_p, queen_p) + num_moves(queen_p, rook_p);
  return rook_first < queen_first ? rook_first : queen_first;
}

