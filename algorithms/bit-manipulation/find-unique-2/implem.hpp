#ifdef DEBUG
  #include <bitset>
  #include <iostream>
#endif
#include <iterator>
#include <numeric>

// Algorithm to be tested

template <class It> auto find_unique(It&& beg, It&& end)
{
  using value_type = typename std::iterator_traits<It>::value_type;
  //constexpr unsigned num_bytes = 8 * sizeof(value_type);
  return std::accumulate(
      std::forward<It>(beg)
      , std::forward<It>(end), std::make_pair(value_type(), value_type())
      , [](auto&& acc, auto&& cur)
      {
        #ifdef DEBUG
          std::cout << "Bits equal to 1: " << std::cout.widen('\n');
          std::cout << "    0 mod 3 times: " << std::bitset<num_bytes>(~(acc.first | acc.second)) << std::cout.widen('\n');
          std::cout << "    1 mod 3 times: " << std::bitset<num_bytes>(acc.first) << std::cout.widen('\n');
          std::cout << "    2 mod 3 times: " << std::bitset<num_bytes>(acc.second) << std::cout.widen('\n');
          std::cout << "Input:             " << std::bitset<num_bytes>(cur) << std::cout.widen('\n') << std::endl;
        #endif
        return std::make_pair(~acc.second & (acc.first ^ cur), (acc.second & ~cur) | (acc.first & cur));
      }).first;
}

