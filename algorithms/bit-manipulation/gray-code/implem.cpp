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

std::vector<unsigned> build_grays(unsigned num)
{
  #ifdef _MSC_VER
    // It seems that there is a bug VS 14.0 2015
    // Following code crashes when usin this compiler
    //  std::vector<int> make_it_crash(1);
    //  make_it_crash.reserve(2);
    //  std::copy(std::rbegin(make_it_crash), std::rend(make_it_crash), std::back_inserter(make_it_crash));
    // It seems that push_back invalidate reverse_iterator even if the capacity is right
    std::vector<unsigned> codes(2 * corresponding_pow(num));
  #else
    std::vector<unsigned> codes(1); //initial vector contains one entry
    codes.reserve(2 * corresponding_pow(num));
    // Need to preallocate necessary memory in order to prevent from:
    // If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated. Otherwise only the past-the-end iterator is invalidated.
  #endif
  
  unsigned more = 1;
  while (more < num)
  {
    std::transform(
        #ifdef _MSC_VER
          std::next(codes.rbegin(), codes.size() - more), codes.rend()
          , std::next(codes.begin(), more)
        #else
          codes.rbegin(), codes.rend()
          , std::back_inserter(codes)
        #endif
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

