#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

// Algorithm to be tested

// STL

namespace {
template <char delimiter> struct DelimitedString : std::string {};
template <char delimiter> std::istream& operator>>(std::istream& stream, DelimitedString<delimiter>& s)
{
  return getline(stream, static_cast<std::string&>(s), delimiter);
}
}

static std::string replace_spaces(std::string const& in)
{
  const std::string replace_by = "&nbsp;";
  std::istringstream iss(in);
  std::ostringstream oss;
  std::copy(std::istream_iterator<DelimitedString<' '>>(iss)
      , std::istream_iterator<DelimitedString<' '>>()
      , std::ostream_iterator<std::string>(oss, replace_by.c_str()));
  std::string out = oss.str();
  return out.empty() || in[in.size()-1] == ' ' ? out : out.substr(0, out.size() -replace_by.size());
}

#define ALGO ReplaceSpaces_STL
#include "tests.hpp"

