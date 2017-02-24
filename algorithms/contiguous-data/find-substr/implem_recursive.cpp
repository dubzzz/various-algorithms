#include <string>

#include "aim.hpp"

// Algorithm to be tested
 
static std::size_t find_substr_impl(std::string const& raw, std::string const& pattern, std::size_t pos_raw, std::size_t pos_pattern)
{
  // returns the first position in raw (pos_raw <= answer < raw.size()) such as raw[answer:] == pattern[pos_pattern:]
  // otherwise std::string::npos

  if (pos_pattern == pattern.size())
  {// remaining pattern is empty, it is a match
    return pos_raw;
  }
  if (pos_raw == raw.size())
  {// remaining raw is empty, no match
    return std::string::npos;
  }

  if (raw[pos_raw] == pattern[pos_pattern])
  {// is there a match starting at this position
    std::size_t sub_start = find_substr_impl(raw, pattern, pos_raw +1, pos_pattern +1);
    if (sub_start == pos_raw +1)
    {
      return pos_raw;
    }
  }
  return find_substr_impl(raw, pattern, pos_raw +1, pos_pattern);
}
 
std::size_t find_substr(std::string const& raw, std::string const& pattern)
{
  return find_substr_impl(raw, pattern, 0, 0);
}
