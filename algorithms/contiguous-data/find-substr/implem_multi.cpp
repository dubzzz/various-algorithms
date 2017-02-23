#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
 
#include "aim.hpp"

// Algorithm to be tested
 
std::size_t find_substr(std::string const& raw, std::string const& pattern)
{
  if (pattern.empty())
  {
    return 0;
  }

  using RawBits = unsigned long long;
  constexpr std::size_t rawbits_length = 8 * sizeof(RawBits);
  RawBits offset_end_bit = RawBits(1) << (pattern.size() % rawbits_length);
  std::size_t num_rawbits = 1 + (pattern.size() -1)/rawbits_length;

  // build automata changes

  std::vector<RawBits> transitions[256];
  std::fill(transitions, transitions +256, std::vector<RawBits>(num_rawbits));
  for (std::size_t idx {} ; idx != pattern.size() ; ++idx)
  {
    std::size_t idx_in_state { idx };
    std::size_t first_idx { idx_in_state / rawbits_length };
    std::size_t second_idx { idx_in_state % rawbits_length };
    transitions[pattern[idx] - CHAR_MIN][first_idx] |= (1 << second_idx);
  }

  // apply automata
  std::vector<RawBits> current_state(num_rawbits);
  current_state[0] = 1;
  for (std::size_t idx {} ; idx != raw.size() ; ++idx)
  {
    auto& transition = transitions[raw[idx] - CHAR_MIN];
    for (std::size_t id {} ; id != current_state.size() ; ++id) { current_state[id] &= transition[id]; }
    std::vector<bool> carry(current_state.size());
    for (std::size_t id {} ; id != current_state.size() ; ++id) { carry[id] = !! (current_state[id] & (RawBits(1) << (rawbits_length -1))); }
    for (std::size_t id {} ; id != current_state.size() ; ++id) { current_state[id] <<= 1; }
    for (std::size_t id {1} ; id < current_state.size() ; ++id) { if (carry[id -1]) { current_state[id] |= 1; } }
    current_state[0] |= 1;
    if (current_state.back() & offset_end_bit) { return idx +1 -pattern.size(); }
  }

  return std::string::npos;
}

