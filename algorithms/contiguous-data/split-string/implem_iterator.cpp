#include <algorithm>
#include <istream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

namespace {

struct Splitter
{//not safe for multi-threading
  static char delim; //crappy just to test with stream iterators
  std::string m_s;
  Splitter() : m_s() {}
};
char Splitter::delim = ' ';

std::istream& operator>>(std::istream& in, Splitter& sp)
{
  std::getline(in, sp.m_s, Splitter::delim);
  return in;
}

}

std::vector<std::string> split(std::string const& in, char delim)
{
  Splitter::delim = delim;
  
  std::vector<Splitter> tmp;
  std::istringstream iss(in);
  std::copy(std::istream_iterator<Splitter>(iss), std::istream_iterator<Splitter>(), std::back_inserter(tmp));
  for (std::size_t pos {in.size()} ; pos > 0 && in[pos-1] == delim ; --pos) { tmp.emplace_back(); }
  
  std::vector<std::string> out(tmp.size());
  std::transform(tmp.begin(), tmp.end(), out.begin(), [](auto& v) { return std::move(v.m_s); });
  return out;
}

