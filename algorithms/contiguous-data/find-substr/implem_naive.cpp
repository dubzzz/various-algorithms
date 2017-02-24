#include <string>

#include "aim.hpp"

// Algorithm to be tested
 
static bool starts_with(std::string const& raw, std::string const& pattern, std::size_t offset)
{
  for (std::size_t idx {} ; idx != pattern.size() ; ++idx)
  {
    if (raw[idx + offset] != pattern[idx])
    {
      return false;
    }
  }
  return true;
}

std::size_t find_substr(std::string const& raw, std::string const& pattern)
{
  if (raw.size() < pattern.size())
  {
    return std::string::npos;
  }
  std::size_t max_idx = raw.size() - pattern.size();
  for (std::size_t idx {} ; idx <= max_idx ; ++idx)
  {
    if (starts_with(raw, pattern, idx))
    {
      return idx;
    }
  }
  return std::string::npos;
}
