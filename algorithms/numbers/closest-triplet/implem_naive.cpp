#include <algorithm>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

int closest_3sum(int target, std::vector<int> const& data)
{// data.size() >= 3
  auto eval_distance = [](int a, int b) -> unsigned
  {
      return a > b
          ? unsigned(a - b)
          : unsigned(b - a);
  };
  int answer(data[0] + data[1] + data[2]);
  unsigned distance = eval_distance(answer, target);
  
  for (std::size_t i {} ; i < data.size() ; ++i) {
    for (std::size_t j {i+1} ; j < data.size() ; ++j) {
      for (std::size_t k {j+1} ; k < data.size() ; ++k) {
        unsigned current_dist = eval_distance(data[i] + data[j] + data[k], target);
        if (distance > current_dist)
        {
          distance = current_dist;
          answer = data[i] + data[j] + data[k];
        }
      }
    }
  }
  return answer;
}

