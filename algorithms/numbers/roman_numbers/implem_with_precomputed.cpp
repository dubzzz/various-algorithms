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
  constexpr ccstring() : roman_repr() {}
  constexpr ccstring(const char (&tab)[N]) : roman_repr()
  {
    for (std::size_t i {} ; i != N ; ++i)
    {
      roman_repr[i] = tab[i];
    }
  }
  constexpr char const* begin() const { return roman_repr; }
  constexpr char const* end() const { return roman_repr + N; }
  constexpr char& operator[](std::size_t idx)
  {
    return roman_repr[idx];
  }
  constexpr const char* value() const
  {
    return roman_repr;
  }
  operator std::string() const
  {
    return roman_repr;
  }
};

template <int _value> constexpr auto build_roman_str_impl()
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

template <int I> constexpr auto build_roman_str_offset_impl()
{
  return build_roman_str_impl<I-static_cast<int>(max_roman)>();
}

template <int... I> constexpr auto to_roman_str_impl(int value, std::integer_sequence<int, I...>)
{
  constexpr const ccstring<max_roman_length> tab[] = { build_roman_str_offset_impl<I>()... };
  return tab[value + max_roman];
}

constexpr auto to_roman_str(int value)
{
  return to_roman_str_impl(value, std::make_integer_sequence<int, 2 * max_roman +1>());
}

std::map<char, int> build_by_letters()
{
  std::map<char, int> reversed;
  std::transform(std::begin(letters_value), std::end(letters_value)
      , std::inserter(reversed, std::begin(reversed))
      , [](auto const& p) { return std::make_pair(p.second, p.first); });
  return reversed;
}

int from_roman_str(std::string const& expr)
{
  static std::map<char, int> by_letters = build_by_letters();
  
  if (expr[0] == '0')
  {
    return 0;
  }

  int num {};
  bool positive_sign = expr[0] != '-';
  int current_val = letters_value[num_letters -1].first;
  for (std::size_t pos = { positive_sign ? std::size_t() : std::size_t(1) } ; pos != expr.size() ; ++pos)
  {
    int prev_val = std::exchange(current_val, by_letters[expr[pos]]);
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

#include "tests.hpp"

