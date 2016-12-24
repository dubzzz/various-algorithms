#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <string>
#include <type_traits>

// Roman numbers are defined as succesives characters among I,V,X,L,C,D,M...
// The aim of this exercise is to write two functions:
// - from_roman_str: taking a roman string and converting it into an integer
// - to_roman_str: taking an integer and converting it into a roman string
// More details on roman numerals can be found on https://en.wikipedia.org/wiki/Roman_numerals

// You may suppose that entries would be correct numbers or roman strings
// 0 is equivalent to "0"
// negative numbers equivalent to "-" + to_roman_str(-number)

// Algorithm to be tested
// int from_roman_str(std::string const&°
// std::string to_roman_str(int)

// If your algorithm does not apply for all the possible characters defined into checks::letters_value (below)
// You can override the number of letters selected by using the macro LIMIT_TO_X_LETTERS

namespace checks {

static constexpr std::pair<int, char> letters_value[] = { {1,'I'}, {5,'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'} };
#if defined(LIMIT_TO_X_LETTERS)
# warning "Number of roman characters have been limited"
  static constexpr std::size_t num_letters = LIMIT_TO_X_LETTERS;
#else
  static constexpr std::size_t num_letters = sizeof(letters_value)/sizeof(std::pair<int, char>);
#endif

constexpr bool check_roman_definition(std::size_t pos = 1)
{
  return pos != num_letters
      ? ((letters_value[pos].first == (pos%2 ? 5 : 2) * letters_value[pos-1].first) && check_roman_definition(pos+1))
      : true;
}

static_assert(num_letters >= 3, "At least 3 characters must be defined");
static_assert(num_letters % 2 == 1, "Roman must have an odd number of mapping pairs");
static_assert(letters_value[0].first == 1, "First Roman mapping pair is always 1");
static_assert(check_roman_definition(), "Latin mapping pairs must follow: pair(i) = i%2 ? 5*pair(i-1) : 2*pair(i-1)");

static constexpr std::size_t max_roman = 4 * letters_value[num_letters-1].first -1;
static constexpr std::size_t max_roman_length = (num_letters -1) / 2 + 3 * (num_letters +1) / 2 + 2; //null-terminated and minus

// Running tests

TEST(TEST_NAME, FromRoman_Zero)
{
  ASSERT_EQ(0, from_roman_str("0"));
}

TEST(TEST_NAME, FromRoman_PositiveNumber)
{
  ASSERT_EQ(14, from_roman_str("XIV"));
}

TEST(TEST_NAME, FromRoman_NegativeNumber)
{
  ASSERT_EQ(-9, from_roman_str("-IX"));
}

TEST(TEST_NAME, FromRoman_MultiplePositiveNumbers)
{
  if (num_letters >= 3)
  {
    ASSERT_EQ(1, from_roman_str("I"));
    ASSERT_EQ(36, from_roman_str("XXXVI"));
    ASSERT_EQ(39, from_roman_str("XXXIX"));
  }
  if (num_letters >= 5)
  {
    ASSERT_EQ(51, from_roman_str("LI"));
    ASSERT_EQ(42, from_roman_str("XLII"));
    ASSERT_EQ(191, from_roman_str("CXCI"));
    ASSERT_EQ(399, from_roman_str("CCCXCIX"));
  }
  if (num_letters >= 7)
  {
    ASSERT_EQ(499, from_roman_str("CDXCIX"));
    ASSERT_EQ(557, from_roman_str("DLVII"));
    ASSERT_EQ(3999, from_roman_str("MMMCMXCIX"));
  }
}

TEST(TEST_NAME, ToRoman_Zero)
{
  ASSERT_EQ("0", to_roman_str(0));
}

TEST(TEST_NAME, ToRoman_PositiveNumber)
{
  ASSERT_EQ("XIV", to_roman_str(14));
}

TEST(TEST_NAME, ToRoman_NegativeNumber)
{
  ASSERT_EQ("-IX", to_roman_str(-9));
}

TEST(TEST_NAME, ToRoman_MultiplePositiveNumbers)
{
  if (num_letters >= 3)
  {
    ASSERT_EQ("I", to_roman_str(1));
    ASSERT_EQ("XXXVI", to_roman_str(36));
    ASSERT_EQ("XXXIX", to_roman_str(39));
  }
  if (num_letters >= 5)
  {
    ASSERT_EQ("LI", to_roman_str(51));
    ASSERT_EQ("XLII", to_roman_str(42));
    ASSERT_EQ("CXCI", to_roman_str(191));
    ASSERT_EQ("CCCXCIX", to_roman_str(399));
  }
  if (num_letters >= 7)
  {
    ASSERT_EQ("CDXCIX", to_roman_str(499));
    ASSERT_EQ("DLVII", to_roman_str(557));
    ASSERT_EQ("MMMCMXCIX", to_roman_str(3999));
  }
}

RC_GTEST_PROP(TEST_NAME, Property_ToThenFrom_IsIdentity, ())
{
  auto generator = rc::gen::inRange(-static_cast<int>(max_roman), static_cast<int>(max_roman));
  int N = *generator;
  RC_ASSERT(from_roman_str(to_roman_str(N)) == N);
}

RC_GTEST_PROP(TEST_NAME, Property_ToRoman_ReturnNotEmpty, ())
{
  auto generator = rc::gen::inRange(-static_cast<int>(max_roman), static_cast<int>(max_roman));
  int N = *generator;
  RC_ASSERT(to_roman_str(N).size() > std::size_t());
}

RC_GTEST_PROP(TEST_NAME, Property_ToRoman_IsSurjective, ())
{
  auto generator = rc::gen::inRange(-static_cast<int>(max_roman), static_cast<int>(max_roman));
  int a = *generator;
  int b = *generator;
  RC_PRE(a != b);
  RC_ASSERT(to_roman_str(a) != to_roman_str(b));
}

RC_GTEST_PROP(TEST_NAME, Property_ToRoman_NegativeStartByMinus, ())
{
  auto generator = rc::gen::inRange(-static_cast<int>(max_roman), -1);
  int N = *generator;
  RC_ASSERT(to_roman_str(N)[0] == '-');
}

RC_GTEST_PROP(TEST_NAME, Property_ToRoman_ProducesOnlyAllowedCharacters, ())
{
  auto generator = rc::gen::inRange(1, static_cast<int>(max_roman));
  int N = *generator;
  
  std::set<char> allowed_chars;
  std::transform(std::begin(letters_value), std::next(std::begin(letters_value), num_letters)
      , std::inserter(allowed_chars, std::begin(allowed_chars))
      , [](auto const& p) { return p.second; });
  
  auto out = std::string{ to_roman_str(N) };
  RC_ASSERT(std::find_if(std::begin(out), std::end(out)
      , [allowed_chars](auto c) { return allowed_chars.find(c) == allowed_chars.end(); }) == std::end(out));
}

RC_GTEST_PROP(TEST_NAME, Property_ToRoman_NegativeIsPositiveWithMinus, ())
{
  auto generator = rc::gen::inRange(1, static_cast<int>(max_roman));
  int N = *generator;
  RC_ASSERT(to_roman_str(-N) == "-" + to_roman_str(N));
}

RC_GTEST_PROP(TEST_NAME, Property_ToRoman_GoodOrdering, ())
{
  auto generator = rc::gen::inRange(1, static_cast<int>(max_roman));
  int N = *generator;
  
  std::map<char, std::set<char>> can_be_preceded_bys;
  for (std::size_t idx {} ; idx != num_letters ; ++idx)
  {
    std::set<char> can_precede_it;
    std::transform(std::next(std::begin(letters_value), idx), std::end(letters_value)
        , std::inserter(can_precede_it, std::begin(can_precede_it))
        , [](auto const& p) { return p.second; });
    if (idx)
    {
      can_precede_it.insert(letters_value[idx % 2 ? idx-1 : idx-2].second);
    }
    can_be_preceded_bys[letters_value[idx].second] = can_precede_it;
  }
  
  auto out = std::string{ to_roman_str(N) };
  RC_PRE(out.size() > std::size_t(1));
  
  std::vector<bool> wrong_ordering;
  std::transform(std::begin(out), std::prev(std::end(out))
      , std::next(std::begin(out))
      , std::back_inserter(wrong_ordering)
      , [&can_be_preceded_bys](auto first, auto second) {
          auto const& allowed = can_be_preceded_bys.at(second);
          return allowed.find(first) == allowed.end();
      });
  RC_ASSERT(std::none_of(std::begin(wrong_ordering), std::end(wrong_ordering), [](auto b){ return b; }));
}

RC_GTEST_PROP(TEST_NAME, Property_ToRoman_NotTooManyTimesTheSameCharacter, ())
{
  auto generator = rc::gen::inRange(1, static_cast<int>(max_roman));
  int N = *generator;
  
  auto out = std::string{ to_roman_str(N) };
  for (std::size_t idx {} ; idx != num_letters ; ++idx)
  {
    RC_ASSERT(std::count(std::begin(out), std::end(out), letters_value[idx].second) <= (idx%2
        ? 1 // 5 * 10^N appear at most 1 time
        : 4 // 10^N appear at most 4 times
    ));
  }
}

RC_GTEST_PROP(TEST_NAME, Property_ToRoman_SizeIsNotTooLong, ())
{
  auto generator = rc::gen::inRange(-static_cast<int>(max_roman), static_cast<int>(max_roman));
  int N = *generator;
  RC_ASSERT(to_roman_str(N).size() < max_roman_length);
}

RC_GTEST_PROP(TEST_NAME, Property_FromRoman_TestOnSimpleRomanStrings, ())
{
  auto choices = *rc::gen::container<std::vector<int>>(num_letters, rc::gen::inRange(0, 3));
  if (! std::all_of(std::begin(choices), std::end(choices), [](auto n) { return n == 0; }))
  {
    choices[0] = 1;
  }
  
  std::string roman_repr;
  int expected {};
  for (std::size_t ridx {} ; ridx != num_letters ; ++ridx)
  {
    std::size_t idx { num_letters - ridx -1 };
    std::size_t nums = (idx % 2 && choices[idx] > 1) ? std::size_t(1) : std::size_t(choices[idx]);
    std::fill_n(std::back_inserter(roman_repr), nums, letters_value[idx].second);
    expected += nums * letters_value[idx].first;
  }
  RC_ASSERT(from_roman_str(roman_repr) == expected);
}

}//checks

