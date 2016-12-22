#if (defined(__clang__) && (__clang_major__ < 3 || (__clang_major__ == 3 && __clang_minor__ < 4))) || \
    (defined(__GNUC__)  && (__GNUC__        < 5 || (__GNUC__        == 5 && __GNUC_MINOR__  < 1)))
#   define NO_CONSTEXPR
#endif

#if defined(NO_CONSTEXPR)
#   define __CONSTEXPR__
#else
#   define __CONSTEXPR__ constexpr
#endif

#include <utility>

// Algorithm to be tested

template <class NumType>
constexpr NumType pow2(std::size_t i) { return NumType(1) << i; }

template <class NumType, std::size_t... I>
__CONSTEXPR__ NumType pows2(std::index_sequence<I...>)
{
  __CONSTEXPR__ NumType data[] = { pow2<NumType>(I)... };
  NumType agg {};
  for (std::size_t idx {} ; idx != sizeof...(I) ; ++idx)
  {
    agg |= data[idx];
  }
  return agg;
}

template <unsigned ones, unsigned pad, class NumType>
__CONSTEXPR__ unsigned most_significant_position_helper(NumType num)
{
  if (! ones) return 1 + pad;
  constexpr unsigned midones = ones >> 1;
  __CONSTEXPR__ NumType mask = pows2<NumType>(std::make_index_sequence<ones+pad>());
  return (num & ~mask)
      ? most_significant_position_helper<midones, pad + ones>(num)
      : most_significant_position_helper<midones, pad>(num);
}

__CONSTEXPR__ unsigned most_significant_position(unsigned num)
{
  return num ? most_significant_position_helper<4*sizeof(unsigned), 0>(num) : 0;
}

#include "tests.hpp"

#if defined(NO_CONSTEXPR)
#   warning "Constexpr tests have been disabled for this compiler"
#   warning "requirement: compiler compatible with C++14's constexpr"
#endif

