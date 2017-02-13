#include <algorithm>
#include <iterator>
#include <queue>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Algorithm to be tested

class Trie
{// not a real trie implementation, mimic a trie to help the problem
  std::unique_ptr<Trie> sub_tries[26];

private:
  void push_helper(std::string const& entry, std::size_t idx)
  {
    if (idx == entry.size()) { return; }
      
    std::size_t pos { static_cast<std::size_t>(entry[idx] -'a') };
    if (! sub_tries[pos])
    {
      sub_tries[pos] = std::make_unique<Trie>();
    }
    sub_tries[pos]->push_helper(entry, idx +1);
  }
  bool contains_helper(std::string const& entry, std::size_t idx) const
  {
    if (idx == entry.size()) { return true; }
    
    std::size_t pos { static_cast<std::size_t>(entry[idx] -'a') };
    if (! sub_tries[pos]) { return false; }
    return sub_tries[pos]->contains_helper(entry, idx +1);
  }
public:
  Trie() = default;
  Trie(Trie&& other) = delete;
  Trie(Trie const&) = delete;
  Trie& operator=(Trie&& other) = delete;
  Trie& operator=(Trie const&) = delete;
  
  void push(std::string const& entry) { push_helper(entry, 0); }
  bool contains(std::string const& entry) const { return contains_helper(entry, 0); }
};

static void push_already_seen_helper(Trie& already_seen, std::vector<std::string> const& pattern, std::string&& current)
{
  if (current.size() == pattern.size())
  {
    already_seen.push(current);
    return;
  }
  
  auto idx = current.size();
  for (char c : pattern[idx])
  {
    push_already_seen_helper(already_seen, pattern, current +c);
  }
}

static void push_already_seen(Trie& already_seen, std::vector<std::string> const& pattern)
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
  Trie already_seen;
  
  for (auto const& raw_f : raw_forbidden)
  {
    std::vector<std::string> f;
    std::istringstream iss(raw_f);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(f));
    push_already_seen(already_seen, f);
  }
  
  if (already_seen.contains(end)) { return -1; }
  
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
    if (already_seen.contains(current)) { continue; }
    
    // increase state
    ++num_iters;
    already_seen.push(current);
    
    // push nexts
    for (std::size_t idx {} ; idx != current.size() ; ++idx)
    {
      push_nexts(next, num_iters, current, idx);
    }
  }
  
  return -1;
}

