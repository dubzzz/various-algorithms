#include <algorithm>
#include <utility>

#include "aim.hpp"

// Algorithm to be tested

template <std::size_t I> constexpr unsigned pow_of_2()
{
  return unsigned(1) << I;
}

template <std::size_t... I> unsigned most_significant_position_helper(unsigned num, std::index_sequence<I...>)
{
  constexpr unsigned values[] = { pow_of_2<I>()... };
  for (std::size_t idx {} ; idx != sizeof...(I) ; ++idx)
  {
    if ((num ^ values[idx]) < values[idx])
    {
      return idx +1;
    }
  }
  return 0;
}

unsigned most_significant_position(unsigned num)
{
  using defining_sequence = std::make_index_sequence<8 * sizeof(unsigned)>;
  return most_significant_position_helper(num, defining_sequence());
}

