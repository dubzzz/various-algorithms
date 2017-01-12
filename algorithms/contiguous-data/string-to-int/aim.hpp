/*
  The aim of this topic is:
    Implements string_to_int, string_to_long, string_to_longlong
    to convert input strings to respectively int, long, long long
    Input strings assumptions:
    - contains only figures valid for the base (0-9 and a-z) or - (only possible for first element)
    - never empty
    - always valid entries (no overflow)
    - null terminated
   
    string_to_* accept an optional parameters for the base (must be defaulted to 10 - maximum value is 36)
   
    Functions must be defined as constexpr for char*
    and normal functions for std::string
*/

#include <string>

// Algorithm to be tested

#define NO_CONSTEXPR
int string_to_int(const char*, unsigned base=10);
int string_to_int(std::string const&, unsigned base=10);
long string_to_long(const char*, unsigned base=10);
long string_to_long(std::string const&, unsigned base=10);
long long string_to_longlong(const char*, unsigned base=10);
long long string_to_longlong(std::string const&, unsigned base=10);
