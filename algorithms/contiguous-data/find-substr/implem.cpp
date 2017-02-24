#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested
 
using TransitionTable = std::vector<std::array<std::size_t, 26>>;
 
static bool reversed_equals(std::string const& pattern, std::string const& try_sub, std::size_t length)
{
  for (std::size_t idx {} ; idx != length ; ++idx)
  {
    if (try_sub[try_sub.size() -length +idx] != pattern[idx]) { return false; }
  }
  return true;
}
 
static TransitionTable make_transition_table(std::string const& pattern)
{
  TransitionTable transition_table;
  for (std::size_t idx {} ; idx != pattern.size() ; ++idx)
  {
    transition_table.emplace_back();
    auto& transitions = transition_table.back();
    for (char c = 'A' ; c <= 'Z' ; ++c)
    {
      auto& current = transitions[c-'A'];
      if (pattern[idx] == c)
      {// ok to go to next state
        current = idx +1;
        continue;
      }

      // not ok, need to go back in the pattern
      // - find the longest still matching with the new entry
      // - it can have a maximum of idx chars

      current = 0; // in case there is nothing better
      if (idx == 0) { continue; }

      std::string try_submatch = pattern.substr(0, idx);
      try_submatch += c;
      for (std::size_t length {try_submatch.size()} ; length > 0 ; --length)
      {
        if (reversed_equals(pattern, try_submatch, length))
        {
          current = length;
          break;
        }
      }
    }
  }
  // no real need to fill last line correctly for our current use
  transition_table.emplace_back();
  std::fill(transition_table.back().begin(), transition_table.back().end(), pattern.size());

  return transition_table;
}

#ifdef DEBUG
template <class OutputStream>
static void draw_transition_table(OutputStream& os, TransitionTable const& transition_table)
{
  os << "  |";
  for (char c = 'A' ; c <= 'Z' ; ++c) { os << ' ' << c << '|'; }
  os << '\n';

  os << "--+";
  std::fill_n(std::ostream_iterator<std::string>(os, "+"), 26, "--");
  os << '\n';

  for (std::size_t idx {} ; idx != transition_table.size() ; ++idx)
  {
    os << std::setw(2) << idx << '|';
    for (auto transition : transition_table[idx]) { os << std::setw(2) << transition << '|'; }
    os << '\n';
  }
}
#endif

std::size_t find_substr(std::string const& raw, std::string const& pattern)
{
  if (! pattern.size())
  {
    return 0;
  }
  auto transition_table = make_transition_table(pattern);
  #ifdef DEBUG
    draw_transition_table(std::cout, transition_table);
  #endif
  std::size_t state {};
  for (std::size_t idx {} ; idx != raw.size() ; ++idx)
  {
    state = transition_table[state][raw[idx]-'A'];
    #ifdef DEBUG
      std::cout << "--" << raw[idx] << "--> " << state << '\n';
    #endif
    if (state == pattern.size())
    {
      return idx - pattern.size() +1;
    }
  }
  return std::string::npos;
}

