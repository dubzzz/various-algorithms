#include <algorithm>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

int closest_3sum(int target, std::vector<int> const& _data)
{// data.size() >= 3
  auto eval_distance = [](int a, int b) -> unsigned
  {
      return a > b
          ? unsigned(a - b)
          : unsigned(b - a);
  };
  constexpr unsigned NUM = 3;
  auto data = _data;
  std::sort(std::begin(data), std::end(data));
  
  int answer {};
  unsigned min_diff = std::numeric_limits<unsigned>::max();
  for (std::size_t i {} ; i != data.size()-NUM+1 ; ++i)
  {
    std::size_t j = i+1;
    std::size_t k = data.size() -1;
    while (j < k)
    {
      const unsigned abs_delta = eval_distance(data[i] + data[j] + data[k], target);
      if (min_diff >= abs_delta)
      {
        answer = data[i] + data[j] + data[k];
        min_diff = abs_delta;
      }
      if (data[i] + data[j] + data[k] < target)
      {
        ++j;
      }
      else
      {
        --k;
      }
    }
  }
  return answer;
}

