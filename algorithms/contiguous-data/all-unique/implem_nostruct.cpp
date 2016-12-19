#include <algorithm>
#include <string>

// Algorithm to be tested
// Without ADDITIONAL DATA STRUCTURE

bool all_unique(std::string const& in)
{
  typedef long long HelperType;
  const std::size_t __possible_elements = 1 << (sizeof(char) << 3);
  const std::size_t __elements_per_helper = sizeof(HelperType) << 3;
  static_assert(__possible_elements % __elements_per_helper == 0, "8 x sizeof(HelperType) must divide 8 x sizeof(char)");

  HelperType unicity_checker[__possible_elements / __elements_per_helper] = { 0 }; //should be a ceil
  
  for (auto c : in)
  {
    const unsigned char cc = *reinterpret_cast<unsigned char*>(&c);
    const std::size_t idx = cc / __elements_per_helper;
    const HelperType mask = static_cast<HelperType>(1) << (cc & (__elements_per_helper-1)); // << (cc & __elements_per_helper)
    if (unicity_checker[idx] & mask)
    {
      return false;
    }
    unicity_checker[idx] |= mask;
  }
  return true;
}

#include "tests.hpp"

