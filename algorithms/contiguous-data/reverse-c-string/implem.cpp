#include <algorithm>
#include <memory>
#include <string>

// Algorithm to be tested

// In-place

char* reverse(char* in)
{
  // Reverse a null-terminated string in-place
  
  char* pos = in;
  while (*pos)
  {
    ++pos;
  }
  --pos;
  
  char* direct = in;
  while (direct < pos)
  {
    char tmp = *direct;
    *direct++ = *pos;
    *pos-- = tmp;
  }
  return in;
}

#include "tests.hpp"

