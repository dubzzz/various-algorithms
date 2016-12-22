#include <limits>
#include <string>
#include <utility>

// Algorithm to be tested

template <class Type> constexpr Type to_base(char c, unsigned base)
{
  return base <= 10
      ? c - '0'
      : (c > '9' ? static_cast<Type>(c-'a'+10) : static_cast<Type>(c-'0'));
}

template <class OutType> constexpr OutType _atox(const char* expression, unsigned base, OutType prev = OutType())
{
  return *expression == '\0'
      ? prev
      : (*expression == '-'
        ? -_atox(expression +1, base, prev)
        : _atox(expression +1, base, prev * base + to_base<OutType>(*expression, base)));
}

constexpr auto string_to_int(const char* expression, unsigned base=10) { return _atox<int>(expression, base); }
auto string_to_int(std::string const& expression, unsigned base=10) { return string_to_int(expression.c_str(), base); }

constexpr auto string_to_long(const char* expression, unsigned base=10) { return _atox<long>(expression, base); }
auto string_to_long(std::string const& expression, unsigned base=10) { return string_to_long(expression.c_str(), base); }

constexpr auto string_to_longlong(const char* expression, unsigned base=10) { return _atox<long long>(expression, base); }
auto string_to_longlong(std::string const& expression, unsigned base=10) { return string_to_longlong(expression.c_str(), base); }

#include "tests.hpp"

