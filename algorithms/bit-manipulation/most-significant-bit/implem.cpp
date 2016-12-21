// Algorithm to be tested

unsigned most_significant(unsigned num)
{
  for ( ; (num & (num -1)) != 0 ; num &= num -1) {}
  return num;
}

#include "tests.hpp"

