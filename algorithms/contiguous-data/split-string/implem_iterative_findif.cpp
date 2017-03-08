#include <algorithm>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::vector<std::string> split(std::string const& in, char delim)
{
  auto it_lastcut = in.begin();
  std::vector<std::string> out;
  while (true)
  {
    auto it_nextcut = std::find_if(it_lastcut, in.end(), [delim](char c) { return c == delim; }); //can easily be generalized to multiple delims
    out.emplace_back(it_lastcut, it_nextcut);
    if (it_nextcut == in.end()) { return out; }
    it_lastcut = std::next(it_nextcut);
  }
  return out;
}

