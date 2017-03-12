#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::string reverse_words(std::string const& in)
{
  // Space: O(n)
  // Time : O(n)
  
  if (in.empty()) { return ""; }
  
  std::vector<std::string> words;
  std::istringstream iss(in);
  std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(words));
  std::ostringstream oss;
  std::copy(words.rbegin(), words.rend(), std::ostream_iterator<std::string>(oss, " "));
  std::string out = oss.str();
  return out.substr(0, out.size() -1);
}

