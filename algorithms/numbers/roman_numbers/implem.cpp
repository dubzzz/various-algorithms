#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <utility>

// Algorithm to be tested

typedef std::pair<int, char> RawLetter;
static constexpr RawLetter letters_value[] = { {1,'I'}, {5,'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'} };
static constexpr std::size_t num_letters = sizeof(letters_value)/sizeof(RawLetter);
static constexpr std::size_t max_roman = 4 * letters_value[num_letters-1].first -1;

std::string to_roman_str(int value)
{
  if (value == 0)
  {
    return "0";
  }
  else if (value < -static_cast<int>(max_roman) || value > static_cast<int>(max_roman))
  {
    return std::string();
  }

  std::string repr;
  if (value < 0)
  {
    repr += '-';
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
        repr += letters_value[idx_minus].second;
      }
      repr += letters_value[idx].second;
    }
  }
  return repr;
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

