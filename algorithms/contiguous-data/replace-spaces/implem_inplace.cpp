#include <algorithm>
#include <string>

// Algorithm to be tested

// In-place

void replace_spaces_inplace(std::string& in)
{
  // Replace all spaces of std::string <in> using only <in>
  // and being able to resize it if required

  const std::string replace_by = "&nbsp;";
  
  std::size_t previous_size { in.size() };
  std::size_t expected_size { in.size() + (replace_by.size() -1) * std::count(in.begin(), in.end(), ' ') };
  in.resize(expected_size);

  for (std::size_t pos = previous_size, current = expected_size ; pos > 0 ; --pos)
  {
    if (in[pos-1] == ' ')
    {
      for (auto rit = replace_by.rbegin() ; rit != replace_by.rend() ; ++rit)
      {
        in[--current] = *rit;
      }
    }
    else
    {
      in[--current] = in[pos-1];
    }
  }
}

std::string replace_spaces(std::string const& in)
{
  std::string copy { in };
  replace_spaces_inplace(copy);
  return copy;
}

#include "tests.hpp"

