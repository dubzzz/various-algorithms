#include "aim.hpp"

// Algorithm to be tested

unsigned most_significant(unsigned num)
{
  for ( ; (num & (num -1)) != 0 ; num &= num -1) {}
  return num;
}

unsigned less_significant(unsigned num)
{
  return num == 0 ? 0 : most_significant(num ^ (num -1));
}

