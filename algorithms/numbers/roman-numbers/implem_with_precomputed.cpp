#if defined(NO_SUPPORT_CONSTEXPR_CXX14)
#   define __CONSTEXPR__
#   define NO_CONSTEXPR
#else
#   define __CONSTEXPR__ constexpr
#endif

#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <utility>

// Algorithm to be tested

#define LIMIT_TO_X_LETTERS 5
typedef std::pair<int, char> RawLetter;
static constexpr std::pair<int, char> letters_value[] = { {1,'I'}, {5,'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'} };
static constexpr std::size_t num_letters = sizeof(letters_value)/sizeof(RawLetter);
static constexpr std::size_t max_roman = 4 * letters_value[num_letters-1].first -1;
static constexpr std::size_t max_roman_length = (num_letters -1) / 2 + 3 * (num_letters +1) / 2 + 2; //null-terminated and minus

template <std::size_t N> class ccstring
{
  char roman_repr[N];
public:
  __CONSTEXPR__ ccstring() : roman_repr() {}
  __CONSTEXPR__ ccstring(const char (&tab)[N]) : roman_repr()
  {
    for (std::size_t i {} ; i != N ; ++i)
    {
      roman_repr[i] = tab[i];
    }
  }
  __CONSTEXPR__ char const* begin() const { return roman_repr; }
  __CONSTEXPR__ char const* end() const { return roman_repr + N; }
  __CONSTEXPR__ char& operator[](std::size_t idx) { return roman_repr[idx]; }
  __CONSTEXPR__ char const& operator[](std::size_t idx) const { return roman_repr[idx]; }
  __CONSTEXPR__ const char* value() const { return roman_repr; }
  operator std::string() const { return roman_repr; }
};

template <int _value> __CONSTEXPR__ auto build_roman_str_impl()
{
  int value { _value };
  ccstring<max_roman_length> repr;
  std::size_t pos {};
  if (value == 0)
  {
    repr[0] = '0';
    repr[1] = '\0';
    return repr;
  }
  else if (value < 0)
  {
    repr[pos++] = '-';
    value = -value;
  }

  constexpr const std::size_t num_couples = 2 * num_letters -1;
  for (int i = num_couples ; i > 0 ; --i)
  {
    const bool car_composite = !(i & 0x0001);
    const std::size_t idx = i >> 1;
    const std::size_t idx_minus = idx & 0x0001 ? idx-1 : idx-2;
    const int car_value = car_composite
        ? letters_value[idx].first - letters_value[idx_minus].first //IV - IX -...
        : letters_value[idx].first; // direct values from letters_value

    while (value >= car_value)
    {
      value -= car_value;
      if (car_composite)
      {
        repr[pos++] = letters_value[idx_minus].second;
      }
      repr[pos++] = letters_value[idx].second;
    }
  }
  repr[pos++] = '\0';
  return repr;
}

template <int I> __CONSTEXPR__ auto build_roman_str_offset_impl()
{
  return build_roman_str_impl<I-static_cast<int>(max_roman)>();
}

template <int... I> __CONSTEXPR__ ccstring<max_roman_length> to_roman_str_impl(int value, std::integer_sequence<int, I...>)
{
  __CONSTEXPR__ const ccstring<max_roman_length> tab[] = { build_roman_str_offset_impl<I>()... };
  return tab[value + max_roman];
}

__CONSTEXPR__ auto to_roman_str_constexpr(int value)
{
  return to_roman_str_impl(value, std::make_integer_sequence<int, 2 * max_roman +1>());
}

std::string to_roman_str(int value)
{
  return static_cast<std::string>(to_roman_str_constexpr(value));
}

template <std::size_t I> __CONSTEXPR__ int build_one_letter()
{
  char letter = static_cast<char>(I + 'A');
  int val {};
  for (auto const& p : letters_value)
  {
    if (p.second == letter)
    {
      return p.first;
    }
  }
  return val;
}

template <std::size_t... I> __CONSTEXPR__ int from_roman_str_impl(const char* expr, std::index_sequence<I...>)
{
  __CONSTEXPR__ int by_letters[sizeof...(I)] = { build_one_letter<I>()... };
  if (*expr == '0')
  {
    return 0;
  }

  int num {};
  bool positive_sign = true;
  if (*expr == '-')
  {
    ++expr;
    positive_sign = false;
  }
  int current_val = letters_value[num_letters -1].first;
  for ( ; *expr ; ++expr)
  {
    int prev_val = current_val;
    current_val = by_letters[*expr - 'A'];
    if (current_val > prev_val)
    {// eg.: CIX: 100 then 101 then 1? 101(num) - 2*1(prev_val) + 10(current_val)
      num += current_val - 2*prev_val;
    }
    else
    {
      num += current_val;
    }
  }
  return positive_sign ? num : -num;
}

__CONSTEXPR__ int from_roman_str(const char* expr)
{
  return from_roman_str_impl(expr, std::make_index_sequence<26>());
}

int from_roman_str(std::string const& expr)
{
  return from_roman_str(expr.c_str());
}

#include "tests.hpp"

#if defined(NO_SUPPORT_CONSTEXPR_CXX14)
#   warning "Constexpr tests have been disabled for this compiler"
#   warning "requirement: compiler compatible with C++14's constexpr"
#endif

