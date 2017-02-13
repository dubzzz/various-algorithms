#include <algorithm>
#include <iterator>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

// Algorithm to be tested

static void push_already_seen_helper(std::unordered_set<std::string>& already_seen, std::vector<std::string> const& pattern, std::string&& current)
{
  if (current.size() == pattern.size())
  {
    already_seen.emplace(std::move(current));
    return;
  }
  
  auto idx = current.size();
  for (char c : pattern[idx])
  {
    push_already_seen_helper(already_seen, pattern, current +c);
  }
}

static void push_already_seen(std::unordered_set<std::string>& already_seen, std::vector<std::string> const& pattern)
{
  push_already_seen_helper(already_seen, pattern, std::string());
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
  std::unordered_set<std::string> already_seen;
  
  for (auto const& raw_f : raw_forbidden)
  {
    std::vector<std::string> f;
    std::istringstream iss(raw_f);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(f));
    push_already_seen(already_seen, f);
  }
  
  if (already_seen.find(end) != already_seen.end()) { return -1; }
  
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
    
    // increase state
    ++num_iters;
    already_seen.emplace(current);
    
    // push nexts
    for (std::size_t idx {} ; idx != current.size() ; ++idx)
    {
      push_nexts(next, num_iters, current, idx);
    }
  }
  
  return -1;
}

