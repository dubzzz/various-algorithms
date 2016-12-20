#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>

enum class Where { Less, Equal, More };

struct too_many_iterations : std::length_error
{
  too_many_iterations(const char* s) : std::length_error(s) {}
  too_many_iterations(std::string const& s) : std::length_error(s) {}
};

template <std::size_t DIM, class AssertSystem>
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

