#if defined(NO_SUPPORT_CONSTEXPR_CXX14)
#   define __CONSTEXPR__
#   define NO_CONSTEXPR
#else
#   define __CONSTEXPR__ constexpr
#endif

#include <utility>

// Algorithm to be tested

template <class NumType> constexpr NumType pow2(std::size_t i)
{
  return NumType(1) << i;
}

template <class NumType> constexpr NumType pows2(std::size_t num_ones)
{
  return num_ones == std::size_t()
      ? NumType{}
      : pow2<NumType>(num_ones -1) | pows2<NumType>(num_ones -1);
}

template <unsigned ones, unsigned pad, class NumType>
__CONSTEXPR__ unsigned most_significant_position_helper(NumType num)
{
  if (! ones) return 1 + pad;
  constexpr unsigned midones = ones >> 1;
  constexpr NumType mask = pows2<NumType>(ones+pad);
  return (num & ~mask)
      ? most_significant_position_helper<midones, pad + ones>(num)
      : most_significant_position_helper<midones, pad>(num);
}

__CONSTEXPR__ unsigned most_significant_position(unsigned num)
{
  return num ? most_significant_position_helper<4*sizeof(unsigned), 0>(num) : 0;
}

#if defined(NO_SUPPORT_CONSTEXPR_CXX14)
#   pragma message("warning - constexpr tests have been disabled for this compiler")
#   pragma message("warning - requirement: compiler compatible with C++14's constexpr")
#endif

