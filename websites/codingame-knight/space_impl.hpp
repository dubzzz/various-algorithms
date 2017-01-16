#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>

#ifdef DEBUG
  #include <iostream>
#endif

#include "ispace.hpp"

struct too_many_iterations : std::length_error
{
  too_many_iterations(const char* s) : std::length_error(s) {}
  too_many_iterations(std::string const& s) : std::length_error(s) {}
};

template <std::size_t DIM, class AssertSystem>
class Space : public ISpace<DIM>
{
  const std::array<std::size_t, DIM> dimensions_;
  const std::array<std::size_t, DIM> hidden_;
  int num_guess;
  int max_guesses;

public:
  Space(std::array<std::size_t, DIM> const& dimensions, std::array<std::size_t, DIM> const& hidden)
      : dimensions_(dimensions)
      , hidden_(hidden)
      , num_guess()
      , max_guesses(std::lround(std::ceil(std::log(*std::max_element(dimensions_.begin(), dimensions_.end()))/std::log(2))))
  {
    #ifdef DEBUG
      std::cout << "--> Space::Space - dimensions<";
      std::copy(std::begin(dimensions), std::end(dimensions), std::ostream_iterator<std::size_t>(std::cout, ","));
      std::cout << ">, hidden<";
      std::copy(std::begin(hidden), std::end(hidden), std::ostream_iterator<std::size_t>(std::cout, ","));
      std::cout << ">" << std::endl;
    #endif
  }
  std::array<std::size_t, DIM> const& dimensions() const override
  {
    #ifdef DEBUG
      std::cout << "--> Space::dimensions - \n<-- dimensions<";
      std::copy(std::begin(dimensions_), std::end(dimensions_), std::ostream_iterator<std::size_t>(std::cout, ","));
      std::cout << ">" << std::endl;
    #endif
    return dimensions_;
  }
  std::array<Where, DIM> guess(std::array<std::size_t, DIM> const& choice) override
  {
    #ifdef DEBUG
      std::cout << "--> Space::guess - choice<";
      std::copy(std::begin(choice), std::end(choice), std::ostream_iterator<std::size_t>(std::cout, ","));
      std::cout << "> - guess #" << (num_guess +1) << "/" << max_guesses << '\n';
    #endif
    if (! AssertSystem::expect(++num_guess <= max_guesses, "Too many iterations to solve this problem")) throw too_many_iterations("Too many iterations to solve this problem");
    
    std::array<Where, DIM> answer;
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      AssertSystem::expect(choice[i] >= 0 && choice[i] < dimensions_[i], "Guess must have values between 0 and dimension (not included)");
      answer[i] = hidden_[i] < choice[i] ? Where::Less : (hidden_[i] > choice[i] ? Where::More : Where::Equal);
    }
    #ifdef DEBUG
      std::cout << "<-- answer<";
      std::copy(std::begin(answer), std::end(answer), std::ostream_iterator<Where>(std::cout, ","));
      std::cout << ">" << std::endl;
    #endif
    return answer;
  }
  bool is_solution(std::array<std::size_t, DIM> const& choice) const override
  {
    #ifdef DEBUG
      std::cout << "--> Space::is_solution - choice<";
      std::copy(std::begin(choice), std::end(choice), std::ostream_iterator<std::size_t>(std::cout, ","));
      std::cout << ">" << std::endl;
    #endif
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

