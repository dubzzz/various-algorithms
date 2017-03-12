#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

static std::size_t end_of_word(std::string const& in, std::size_t start)
{
  while (start < in.size() && in[start] != ' ') { ++start; }
  return start;
}

std::string reverse_words(std::string const& in_)
{
  // Space: O(1) -- we suppose here that in = in_ is the user input
  // Time : O(n)
  
  if (in_.empty()) { return ""; }
  std::string in = in_;
  
  std::size_t start, end;
  for (start = 0, end = end_of_word(in, start)
      ; start < in.size()
      ; start = end+1, end = end_of_word(in, start))
  {
    std::reverse(in.begin() + start, in.begin() + end);
  }
  std::reverse(in.begin(), in.end());
  return in;
}

