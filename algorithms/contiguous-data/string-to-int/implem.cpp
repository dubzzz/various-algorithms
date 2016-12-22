#if (defined(__clang__) && (__clang_major__ < 3 || (__clang_major__ == 3 && __clang_minor__ < 4))) || \
    (defined(__GNUC__)  && (__GNUC__        < 5 || (__GNUC__        == 5 && __GNUC_MINOR__  < 1)))
#   define NO_CONSTEXPR
#endif

#if defined(NO_CONSTEXPR)
#   define __CONSTEXPR__
#else
#   define __CONSTEXPR__ constexpr
#endif

#include <limits>
#include <string>
#include <utility>

#ifdef DEBUG
  #include <iostream>
#endif

// Algorithm to be tested

template <class Type> __CONSTEXPR__ Type to_base(char c, unsigned base)
{
  static_assert('9' > '0', "char('9') must be greater than char('0')");
  static_assert('a' > '9', "char('a') must be greater than char('9')");
  return base <= 10
      ? c - '0'
      : (c > '9' ? static_cast<Type>(c-'a'+10) : static_cast<Type>(c-'0'));
}

__CONSTEXPR__ bool accept_base(char c, unsigned base)
{
  return base <= 10
      ? c >= '0' && c <= static_cast<char>('0' + base)
      : ((c >= '0' && c <= '9') || (c >= 'a' && c <= static_cast<char>('a' + base -11)));
}

template <class OutType> __CONSTEXPR__ auto _atox(const char* expression, unsigned base)
{
  auto value = OutType{};
  auto sign_neg = bool{expression[0] == '-'};
  for (auto c = sign_neg ? ++expression : expression ; *c != '\0' ; ++c)
  {
    #ifdef DEBUG
      if (std::numeric_limits<OutType>::max() / static_cast<OutType>(base) < value) { std::cout << "Overflow encountered when converting input string to integral type" << std::endl; }
    #endif
    value *= base;
    #ifdef DEBUG
      if (! accept_base(*c, base)) { std::cout << "Invalid character encountered when converting input string to integral type" << std::endl; }
    #endif
    auto&& converted_to_base = to_base<OutType>(*c, base);
    #ifdef DEBUG
      if (std::numeric_limits<OutType>::max() -converted_to_base < value) { std::cout << "Overflow encountered when converting input string to integral type" << std::endl; }
    #endif
    value += converted_to_base;
  }
  return sign_neg ? -value : value;
}

__CONSTEXPR__ auto string_to_int(const char* expression, unsigned base=10) { return _atox<int>(expression, base); }
auto string_to_int(std::string const& expression, unsigned base=10) { return string_to_int(expression.c_str(), base); }

__CONSTEXPR__ auto string_to_long(const char* expression, unsigned base=10) { return _atox<long>(expression, base); }
auto string_to_long(std::string const& expression, unsigned base=10) { return string_to_long(expression.c_str(), base); }

__CONSTEXPR__ auto string_to_longlong(const char* expression, unsigned base=10) { return _atox<long long>(expression, base); }
auto string_to_longlong(std::string const& expression, unsigned base=10) { return string_to_longlong(expression.c_str(), base); }

#include "tests.hpp"

#if defined(NO_CONSTEXPR)
#   warning "Constexpr tests have been disabled for this compiler"
#   warning "requirement: compiler compatible with C++14's constexpr"
#endif

