#include <algorithm>
#include <iterator>
#include <vector>

#ifdef DEBUG
  #include <bitset>
  #include <iostream>
#endif

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
  std::vector<unsigned> codes(1); //initial vector contains one entry
  // We cannot work directly on std::vector<unsigned>::iterator because they will be invalidated whatever the situation
  // As stated in cppreference:
  // <<
  //   If the new size() is greater than capacity()
  //   then all iterators and references (including the past-the-end iterator) are invalidated.
  // >>
  // One can think of reserving the necessary size in order to falsify the condition size() > capacity()
  // by doing code.reserve(2 * corresponding_pow(num));
  //
  // Unfortunately, in this case the reference states that:
  // <<
  //   Otherwise only the past-the-end iterator is invalidated.
  // >>
  // Meaning that code.end() and code.rend() might be invalidated after a call to code.push_back
  // In order to prevent that we can use indexes (positions) instead of iterators on vectors
  // by pre-reserving the required size in order to prevent changes of pointers
  codes.reserve(2 * corresponding_pow(num));
  
  unsigned more = 1;
  while (more < num)
  {
    std::transform(fixed_rbegin(codes), fixed_rend(codes)
        , std::back_inserter(codes)
        , [more](auto prev) {
            #ifdef DEBUG
              std::cout << std::bitset<8>(prev) << " + " << std::bitset<8>(more) << std::endl;
            #endif
            return prev + more;
        });
    more <<= 1;
    #ifdef DEBUG
      for (auto e : codes)
      {
        std::cout << std::bitset<8>(e) << std::endl;
      }
      std::cout << "Next sugar       : " << more << std::endl;
      std::cout << "Number of entries: " << codes.size() << std::endl;
      std::cout << " --- " << std::endl;
    #endif
  }
  codes.erase(std::next(codes.begin(), num), codes.end());
  return codes;
}

#include "tests.hpp"

