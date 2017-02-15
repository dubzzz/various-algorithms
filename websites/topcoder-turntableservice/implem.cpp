#include <algorithm>
#include <cmath>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

class State
{
  int time_;
  int rotation_;
  std::size_t num_served_;
  std::vector<bool> is_served_;
  
  State(int time, int rotation, std::vector<bool>&& is_served)
      : time_(time)
      , rotation_(rotation % is_served.size())
      , num_served_(std::count(is_served.begin(), is_served.end(), true))
      , is_served_(is_served)
  {}

public:
  explicit State(std::size_t num) : time_(), rotation_(), num_served_(), is_served_(num, false) {}
  State(State&&) = default;
  State(State const&) = default;
  State& operator=(State&&) = default;
  State& operator=(State const&) = default;
  
  bool dinner_done() const { return num_served_ == is_served_.size(); }
  bool is_served(std::size_t pos) const { return is_served_[pos]; }
  int plate_at(std::size_t pos) const { return (rotation_ + pos + is_served_.size()) % is_served_.size(); }
  
  State serve(std::vector<std::size_t> poss) const
  {
    auto cloned_is_served = is_served_;
    for (auto pos : poss) { cloned_is_served[pos] = true; }
    return State{time_ +15, rotation_, std::move(cloned_is_served)};
  }
  State rotate(std::size_t num) const
  {
    auto cloned_is_served = is_served_;
    int num_rot = num <= cloned_is_served.size()/2 ? num : (int)num-(int)cloned_is_served.size();
    return State{time_ +1 +std::abs(num_rot), rotation_ +num_rot, std::move(cloned_is_served)};
  }
  
  int getRotation() const { return rotation_; }
  std::vector<bool> const& getServed() const { return is_served_; }
  int time() const { return time_; } 
  bool operator<(State const& other) const { return time_ > other.time_ || (time_ == other.time_ && num_served_ < other.num_served_); }
};

int calculate_time(std::vector<std::string> const& raw_favorites)
{
  std::vector<std::vector<int>> favorites;
  for (auto const& rfav : raw_favorites)
  {
    std::vector<int> fav;
    std::istringstream iss(rfav);
    std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), std::back_inserter(fav));
    favorites.emplace_back(std::move(fav));
  }
  
  std::set<std::pair<int, std::vector<bool>>> already_seen;
  
  std::priority_queue<State> nexts;
  nexts.emplace(favorites.size());
  while (! nexts.empty())
  {
    State current = std::move(nexts.top());
    nexts.pop();
    
    if (current.dinner_done())
    {
      return current.time();
    }
    
    std::vector<std::size_t> can_be_served;
    for (std::size_t idx {} ; idx != favorites.size() ; ++idx)
    {
      if (! current.is_served(idx) && std::find(favorites[idx].begin(), favorites[idx].end(), current.plate_at(idx)) != favorites[idx].end())
      {
        can_be_served.emplace_back(idx);
      }
    }
    if (! can_be_served.empty())
    {
      State toadd = current.serve(can_be_served);
      if (already_seen.insert(std::make_pair(toadd.getRotation(), toadd.getServed())).second)
      {
        nexts.emplace(std::move(toadd));
      }
    }
    
    for (std::size_t idx {1} ; idx != favorites.size() ; ++idx)
    {
      State toadd = current.rotate(idx);
      if (already_seen.insert(std::make_pair(toadd.getRotation(), toadd.getServed())).second)
      {
        nexts.emplace(std::move(toadd));
      }
    }
  }
  return -1;
}

