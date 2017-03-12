#include <algorithm>
#include <istream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

namespace {

struct Splitter : std::string
{//not safe for multi-threading
  static char delim; //crappy just to test with stream iterators
};
char Splitter::delim = ' ';

std::istream& operator>>(std::istream& in, Splitter& sp)
{
  std::getline(in, sp, Splitter::delim);
  return in;
}

}

std::vector<std::string> split(std::string const& in, char delim)
{
  Splitter::delim = delim;
  
  std::vector<std::string> out;
  std::istringstream iss(in);
  std::copy(std::istream_iterator<Splitter>(iss), std::istream_iterator<Splitter>(), std::back_inserter(out));
  for (std::size_t pos {in.size()} ; pos > 1 && in[pos-1] == delim ; --pos) { out.emplace_back(); }
  return out;
}
