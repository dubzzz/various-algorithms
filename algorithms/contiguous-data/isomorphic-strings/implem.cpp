#include <string>
#include <unordered_map>

#include "aim.hpp"

// Algorithm to be tested

bool isomorphics(std::string const& s1, std::string const& s2)
{
  if (s1.size() != s2.size())
  {
    return false;
  }
  
  std::unordered_map<char, char> matches;
  for (std::size_t i {} ; i != s1.size() ; ++i)
  {
    const char& c1 = s1[i];
    const char& c2 = s2[i];
    auto&& match = matches.find(c1);
    if (match != matches.end())
    {
      if (match->second != c2) { return false; }
    }
    else
    {
      matches[c1] = c2;
    }
  }
  return true;
}
