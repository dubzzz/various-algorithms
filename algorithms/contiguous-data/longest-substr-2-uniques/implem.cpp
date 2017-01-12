#include <deque>
#include <iostream>
#include <string>

#include "aim.hpp"

std::size_t longest_size(std::string const& in)
{
  std::size_t max_length = 0;
  std::deque<std::size_t> switches; // valid char switches
  for (std::size_t i = 0 ; i != in.size() ; ++i)
  {
    // is it a change compared to last entry?
    if (switches.empty() || in[switches.back()] != in[i])
    {
      switches.push_back(i);
    }

    //do we have more than two different chars?
    if (switches.size() >= 2 && in[i] != in[switches[0]] && in[i] != in[switches[1]])
    {
      std::size_t current = i - switches.front();
      if (current > max_length)
      {
        max_length = current;
      }
      switches.erase(switches.begin(), switches.begin() + switches.size() -2);
    }
  }
  
  if (switches.empty())
  {
    return max_length;
  }
  
  std::size_t current = in.size() - switches.front();
  if (current > max_length)
  {
    max_length = current;
  }
  return max_length;
}
