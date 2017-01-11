#include <algorithm>
#include <iterator>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

unsigned corresponding_pow(unsigned num)
{
  for ( ; (num & (num -1)) != 0 ; num &= num -1) {}
  return num;
}

std::reverse_iterator<const unsigned*> fixed_rbegin(std::vector<unsigned> const& vs) { return std::reverse_iterator<const unsigned*>{ vs.data() + vs.size() }; }
std::reverse_iterator<const unsigned*> fixed_rend(std::vector<unsigned> const& vs) { return std::reverse_iterator<const unsigned*>{ vs.data() }; }

std::vector<unsigned> build_grays(unsigned num)
{
  if (num == 0)
  {
    return {};
  }
  std::vector<unsigned> codes(1);
  codes.reserve(num);
  // Please refer to implem.cpp for more precise details concerning the use of helpers: fixed_rbegin and fixed_rend
  // In a nutshell: past-the-end iterators might be invalidated by push_back (the use of reserve prevent others to be invalidated)
  
  unsigned corresponding = corresponding_pow(num);
  unsigned more = 1;
  while (codes.size() < corresponding)
  {
    std::transform(fixed_rbegin(codes), fixed_rend(codes)
        , std::back_inserter(codes)
        , [more](auto prev){ return prev + more; });
    more <<= 1;
  }
  std::transform(fixed_rbegin(codes), std::next(fixed_rbegin(codes), num - corresponding)
      , std::back_inserter(codes)
      , [more](auto prev){ return prev + more; });
  return codes;
}

