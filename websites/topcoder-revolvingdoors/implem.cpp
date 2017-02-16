#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

using Position = std::pair<std::size_t, std::size_t>;

class State
{
  int num_revolvings_;
  Position pos_;
  std::vector<bool> state_;

public:
  State(int num_revolving, Position const& pos, std::vector<bool> const& state) : num_revolvings_(num_revolving), pos_(pos), state_(state) {}
  State(State&&) = default;
  State(State const&) = default;
  State& operator=(State&&) = default;
  State& operator=(State const&) = default;
  
  bool operator<(State const& other) const { return num_revolvings_ > other.num_revolvings_; }
  auto iters() const { return num_revolvings_; }
  auto const& pos() const { return pos_; }
  auto const& state() const { return state_; }
};

int turns(std::vector<std::string> const& map_)
{
  auto map = map_;
  Position start_pt {};
  Position end_pt {};
  
  // Scan the map for doors and their status
  
  std::vector<bool> initial_state;//true = horizontal
  std::map<Position, std::size_t> state_ids;
  for (std::size_t j {} ; j != map.size() ; ++j)
  {
    for (std::size_t i {} ; i != map[0].size() ; ++i)
    {
      if (map[j][i] != 'O')
      {
        if (map[j][i] == 'S') { start_pt = std::make_pair(i,j); }
        else if (map[j][i] == 'E') { end_pt = std::make_pair(i,j); }
        continue;
      }
      state_ids.emplace(std::make_pair(i,j), initial_state.size());
      initial_state.emplace_back(map[j][i+1] == '-');
    }
  }
  
  // Redraw the map next to doors
  
  map[start_pt.second][start_pt.first] = ' ';
  map[end_pt.second][end_pt.first] = ' ';
  for (auto const& p : state_ids)
  {
    auto const& pos = p.first;
    map[pos.second  ][pos.first-1] = '-';
    map[pos.second  ][pos.first+1] = '-';
    map[pos.second-1][  pos.first] = '|';
    map[pos.second+1][  pos.first] = '|';
  }
  
  // Iterate in the map
  std::set<std::pair<Position, std::vector<bool>>> already_seen;
  
  std::priority_queue<State> nexts;
  nexts.emplace(0, start_pt, std::move(initial_state));
  
  while(! nexts.empty())
  {
    auto st = std::move(nexts.top());
    nexts.pop();
    
    if (st.pos().second >= map.size()) { continue; }
    if (st.pos().first >= map[0].size()) { continue; }
    
    if (st.pos() == end_pt) { return st.iters(); }
    if (! already_seen.insert(std::make_pair(st.pos(), st.state())).second) { continue; }
    
    // move up
    if (st.pos().second >= 1)
    {
      char const& cell = map[st.pos().second -1][st.pos().first];
      switch (cell)
      {
        case '-':
        {
          Position door { st.pos().first >= 1 &&  map[st.pos().second -1][st.pos().first -1] == 'O' ? std::make_pair(st.pos().first -1, st.pos().second -1) : std::make_pair(st.pos().first +1, st.pos().second -1) };
          if (st.state()[state_ids[door]]) //door is closed
          {
            auto state = st.state();
            state[state_ids[door]] = false;
            nexts.emplace(st.iters() +1, std::make_pair(st.pos().first, st.pos().second -1), st.state());
          }
          else
          {
            nexts.emplace(st.iters(), std::make_pair(st.pos().first, st.pos().second -1), st.state());
          }
          break;
        }
        case '|':
        {
          Position door { st.pos().first >= 1 &&  map[st.pos().second -1][st.pos().first -1] == 'O' ? std::make_pair(st.pos().first -1, st.pos().second -1) : std::make_pair(st.pos().first +1, st.pos().second -1) };
          if (st.state()[state_ids[door]]) //door is opened
          {
            nexts.emplace(st.iters(), std::make_pair(st.pos().first, st.pos().second -1), st.state());
          }
          break;
        }
        case ' ':
          nexts.emplace(st.iters(), std::make_pair(st.pos().first, st.pos().second -1), st.state());
          break;
      }
    }
    // move down
    if (st.pos().second +1 < map.size())
    {
      char const& cell = map[st.pos().second +1][st.pos().first];
      switch (cell)
      {
        case '-':
        {
          Position door { st.pos().first >= 1 &&  map[st.pos().second +1][st.pos().first -1] == 'O' ? std::make_pair(st.pos().first -1, st.pos().second +1) : std::make_pair(st.pos().first +1, st.pos().second +1) };
          if (st.state()[state_ids[door]]) //door is closed
          {
            auto state = st.state();
            state[state_ids[door]] = false;
            nexts.emplace(st.iters() +1, std::make_pair(st.pos().first, st.pos().second +1), st.state());
          }
          else
          {
            nexts.emplace(st.iters(), std::make_pair(st.pos().first, st.pos().second +1), st.state());
          }
          break;
        }
        case '|':
        {
          Position door { st.pos().first >= 1 &&  map[st.pos().second +1][st.pos().first -1] == 'O' ? std::make_pair(st.pos().first -1, st.pos().second +1) : std::make_pair(st.pos().first +1, st.pos().second +1) };
          if (st.state()[state_ids[door]]) //door is opened
          {
            nexts.emplace(st.iters(), std::make_pair(st.pos().first, st.pos().second +1), st.state());
          }
          break;
        }
        case ' ':
          nexts.emplace(st.iters(), std::make_pair(st.pos().first, st.pos().second +1), st.state());
          break;
      }
    }
    // move left
    if (st.pos().first >= 1)
    {
      char const& cell = map[st.pos().second][st.pos().first -1];
      switch (cell)
      {
        case '-':
        {
          Position door { st.pos().second >= 1 &&  map[st.pos().second -1][st.pos().first -1] == 'O' ? std::make_pair(st.pos().first -1, st.pos().second -1) : std::make_pair(st.pos().first -1, st.pos().second +1) };
          if (! st.state()[state_ids[door]]) //door is opened
          {
            nexts.emplace(st.iters(), std::make_pair(st.pos().first -1, st.pos().second), st.state());
          }
          break;
        }
        case '|':
        {
          Position door { st.pos().second >= 1 &&  map[st.pos().second -1][st.pos().first -1] == 'O' ? std::make_pair(st.pos().first -1, st.pos().second -1) : std::make_pair(st.pos().first -1, st.pos().second +1) };
          if (! st.state()[state_ids[door]]) //door is closed
          {
            auto state = st.state();
            state[state_ids[door]] = true;
            nexts.emplace(st.iters() +1, std::make_pair(st.pos().first -1, st.pos().second), st.state());
          }
          else
          {
            nexts.emplace(st.iters(), std::make_pair(st.pos().first -1, st.pos().second), st.state());
          }
          break;
        }
        case ' ':
          nexts.emplace(st.iters(), std::make_pair(st.pos().first -1, st.pos().second), st.state());
          break;
      }
    }
    // move right
    if (st.pos().first +1 < map[0].size())
    {
      char const& cell = map[st.pos().second][st.pos().first +1];
      switch (cell)
      {
        case '-':
        {
          Position door { st.pos().second >= 1 &&  map[st.pos().second -1][st.pos().first +1] == 'O' ? std::make_pair(st.pos().first +1, st.pos().second -1) : std::make_pair(st.pos().first +1, st.pos().second +1) };
          if (! st.state()[state_ids[door]]) //door is opened
          {
            nexts.emplace(st.iters(), std::make_pair(st.pos().first +1, st.pos().second), st.state());
          }
          break;
        }
        case '|':
        {
          Position door { st.pos().second >= 1 &&  map[st.pos().second -1][st.pos().first +1] == 'O' ? std::make_pair(st.pos().first +1, st.pos().second -1) : std::make_pair(st.pos().first +1, st.pos().second +1) };
          if (! st.state()[state_ids[door]]) //door is closed
          {
            auto state = st.state();
            state[state_ids[door]] = true;
            nexts.emplace(st.iters() +1, std::make_pair(st.pos().first +1, st.pos().second), st.state());
          }
          else
          {
            nexts.emplace(st.iters(), std::make_pair(st.pos().first +1, st.pos().second), st.state());
          }
          break;
        }
        case ' ':
          nexts.emplace(st.iters(), std::make_pair(st.pos().first +1, st.pos().second), st.state());
          break;
      }
    }
  }
  
  return -1;
}
