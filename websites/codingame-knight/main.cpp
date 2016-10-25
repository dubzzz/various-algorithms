#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>

// Algorithm to be tested

// Inspired from CodinGame: https://www.codingame.com/training/medium/shadows-of-the-knight-episode-1

// Given an instance of Space<number_dimensions>, space, having dimensions space.dimensions()
// you need to find as quickly as possible the position of an hidden tale
// at each turn you can std::array<Where,number_dimensions> guess(std::array<int,number_dimensions>)

enum class Where { Less, Equal, More };

struct GAssert
{
  static inline ::testing::AssertionResult apply(const char*, const char*, bool condition, std::string const& msg)
  {
    if (condition) { return ::testing::AssertionSuccess(); }
    else { return ::testing::AssertionFailure() << msg; }
  }
  static inline bool expect(bool condition, std::string const& msg) { EXPECT_PRED_FORMAT2(apply, condition, msg.c_str()); return condition; };
};
struct RcAssert
{
  static inline bool expect(bool condition, std::string const& msg) { RC_ASSERT(condition); return condition; };
};
struct too_many_iterations : std::length_error
{
  too_many_iterations(const char* s) : std::length_error(s) {}
  too_many_iterations(std::string const& s) : std::length_error(s) {}
};

template <std::size_t DIM, class AssertSystem = GAssert>
class Space
{
  const std::array<std::size_t, DIM> dimensions_;
  const std::array<std::size_t, DIM> hidden_;
  int num_guess;

public:
  Space(std::array<std::size_t, DIM> const& dimensions, std::array<std::size_t, DIM> const& hidden)
      : dimensions_(dimensions)
      , hidden_(hidden)
      , num_guess()
  {}
  std::array<std::size_t, DIM> const& dimensions() const { return dimensions_; }
  std::array<Where, DIM> guess(std::array<std::size_t, DIM> const& choice)
  {
    std::size_t max_dim = *std::max_element(dimensions_.begin(), dimensions_.end());
    if (! AssertSystem::expect(++num_guess <= std::ceil(std::log(max_dim)/std::log(2)), "Too many iterations to solve this problem")) throw too_many_iterations("Too many iterations to solve this problem");
    
    std::array<Where, DIM> answer;
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      AssertSystem::expect(choice[i] >= 0 && choice[i] < dimensions_[i], "Guess must have values between 0 and dimension (not included)");
      answer[i] = hidden_[i] < choice[i] ? Where::Less : (hidden_[i] > choice[i] ? Where::More : Where::Equal);
    }
    return answer;
  }
  bool is_solution(std::array<std::size_t, DIM> const& choice) const
  {
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      if (hidden_[i] != choice[i])
      {
        return false;
      }
    }
    return true;
  }
};

template <std::size_t DIM, class T> std::array<std::size_t, DIM> locate_in_space(Space<DIM, T>& space)
{
  std::array<std::size_t, DIM> min_ext {};
  std::array<std::size_t, DIM> max_ext = space.dimensions();
  
  while (true)
  {
    // Analyze remaining possibilities (break if unique solution)

    bool min_is_solution { true };
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      if (min_ext[i] +1 != max_ext[i])
      {
        min_is_solution = false;
        break;
      }
    }
    if (min_is_solution)
    {
      break;
    }
    
    // Build a choice/guess
    
    std::array<std::size_t, DIM> choice;
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      choice[i] = min_ext[i] + (max_ext[i] - min_ext[i])/2;
    }

    // Try with the choice
    std::array<Where, DIM> hint = space.guess(choice);
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      switch (hint[i])
      {
        case Where::Equal:
          min_ext[i] = choice[i];
          max_ext[i] = choice[i] +1;
          break;
        case Where::Less:
          max_ext[i] = choice[i];
          break;
        case Where::More:
          min_ext[i] = choice[i] +1;
          break;
      }
    }
  }

  return min_ext;
}

#define ALGO CodinGameKNIGHT

// Running tests

TEST(ALGO, 2DSpaceIsAPoint)
{
  Space<2> space({1, 1}, {0, 0});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

TEST(ALGO, 2DSpaceIsALine)
{
  Space<2> space({10, 1}, {9, 0});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

TEST(ALGO, 2DSpaceIsAColumn)
{
  Space<2> space({1, 10}, {0, 9});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

TEST(ALGO, 2DSpace)
{
  Space<2> space({1000, 1000}, {1, 1});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

RC_GTEST_PROP(ALGO, Random2DSpace, (std::size_t const& w, std::size_t const &h))
{
  RC_PRE(w > static_cast<std::size_t>(0) && h > static_cast<std::size_t>(0));
  std::size_t x = *rc::gen::inRange(std::size_t(), w);
  std::size_t y = *rc::gen::inRange(std::size_t(), h);
    
  Space<2, RcAssert> space({w, h}, {x, y});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

