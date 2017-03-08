#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::vector<std::string> split(std::string const& in, char delim)
{
  std::size_t pos_lastcut {};
  std::vector<std::string> out;
  while (true)
  {
    auto pos_nextcut = in.find_first_of(delim, pos_lastcut); // can be generalized to multiple delims
    out.emplace_back(in.substr(pos_lastcut, pos_nextcut - pos_lastcut));
    if (pos_nextcut == std::string::npos) return out;
    pos_lastcut = pos_nextcut+1;
  }
  return out;
}

