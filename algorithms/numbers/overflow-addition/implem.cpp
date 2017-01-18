#include <limits>

#include "aim.hpp"

// Algorithm to be tested

bool overflow(short const* items, std::size_t N)
{
  if (! N)
  {
    return false;
  }
  
  short const*& plus_item { items };
  short const* minus_item { items };
  short const* end { items +N };
  
  auto advance_plus = [&plus_item, end]()
  {
    ++plus_item;
    for (; plus_item != end && *plus_item < 0 ; ++plus_item) {}
  };
  auto advance_minus = [&minus_item, end]()
  {
    ++minus_item;
    for (; minus_item != end && *minus_item >= 0 ; ++minus_item) {}
  };
  
  if (*items >= 0)
  {
    advance_minus();
  }
  else
  {
    advance_plus();
  }
  
  short sum {};
  while (plus_item != end || minus_item != end)
  {
    //plus_item and minus_item point to the next >=0, <0 item to analyse (respectively)
    if ((sum >= 0 && minus_item != end) || plus_item == end)
    {
      if (std::numeric_limits<short>::min() - *minus_item > sum) { return true; }
      sum += *minus_item;
      advance_minus();
    }
    else
    {
      if (std::numeric_limits<short>::max() - *plus_item < sum) { return true; }
      sum += *plus_item;
      advance_plus();
    }
  }
  return false;
}

