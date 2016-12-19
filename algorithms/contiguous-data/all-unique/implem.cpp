#include <algorithm>
#include <string>
#include <unordered_set>

// Algorithm to be tested
// With ADDITIONAL DATA STRUCTURE

bool all_unique(std::string const& in)
{
  std::unordered_set<char> helper;
  for (auto c : in)
  {
    if (helper.find(c) != helper.end())
    {
      return false;
    }
    helper.insert(c);
  }
  return true;
}

#include "tests.hpp"

