#include <algorithm>
#include <iterator>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

// Algorithm to be tested

static bool is_allowed(std::string const& current, std::vector<std::vector<std::string>> const& forbidden)
{
  for (auto const& entry : forbidden)
  {
    bool forbidden_for_entry { true };
    for (std::size_t idx {} ; idx != current.size() ; ++idx)
    {
      if (entry[idx].find(current[idx]) == std::string::npos)
      {// current char is allowed, string is not forbidden for this entry
        forbidden_for_entry = false;
        continue;
      }
    }
    if (forbidden_for_entry)
    {
      return false;
    }
  }
  return true;
}

static void push_nexts(std::queue<std::pair<int, std::string>>& next_elts, int iters, std::string const& current, std::size_t idx)
{
  auto prev = current;
  prev[idx] = current[idx] != 'a' ? prev[idx]-1 : 'z';
  next_elts.emplace(iters, std::move(prev));
  
  auto next = current;
  next[idx] = current[idx] != 'z' ? next[idx]+1 : 'a';
  next_elts.emplace(iters, std::move(next));
}

int min_presses(std::string const& start, std::string const& end, std::vector<std::string> const& raw_forbidden)
{
  std::vector<std::vector<std::string>> forbidden;
  for (auto const& raw_f : raw_forbidden)
  {
    std::vector<std::string> f;
    std::istringstream iss(raw_f);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(f));
    forbidden.emplace_back(std::move(f));
  }
  
  if (! is_allowed(end, forbidden)) { return -1; }
  
  std::unordered_set<std::string> already_seen;
  std::queue<std::pair<int, std::string>> next;
  
  next.emplace(0, start);
  
  while (! next.empty())
  {
    auto num_iters = next.front().first;
    auto current = std::move(next.front().second);
    next.pop();
    
    // check if answer
    if (current == end) { return num_iters; }
    
    
    // check if allowed
    if (already_seen.find(current) != already_seen.end()) { continue; }
    already_seen.emplace(current);
    
    if (! is_allowed(current, forbidden)) { continue; }
    
    // increase state
    ++num_iters;
    
    // push nexts
    for (std::size_t idx {} ; idx != current.size() ; ++idx)
    {
      push_nexts(next, num_iters, current, idx);
    }
  }
  
  return -1;
}

