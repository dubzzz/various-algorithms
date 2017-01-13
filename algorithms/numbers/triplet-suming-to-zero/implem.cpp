#include <algorithm>
#include <tuple>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

auto sum3_impl(std::vector<int> data)
{// data.size() >= 3
  constexpr unsigned NUM = 3;
  std::sort(std::begin(data), std::end(data));

  std::vector<std::tuple<int, int, int>> answer;
  for (std::size_t i {} ; i != data.size()-NUM+1 ; ++i)
  {
    if (! answer.empty() && std::get<0>(answer.back()) == data[i])
    {
      continue;
    }
    std::size_t j = i+1;
    std::size_t k = data.size() -1;
    while (j < k)
    {
      const long long delta = static_cast<long long>(data[i]) + static_cast<long long>(data[j]) + static_cast<long long>(data[k]);
      if (delta == 0ll && (answer.empty() || std::get<1>(answer.back()) != data[j] || std::get<2>(answer.back()) != data[k]))
      {
        answer.emplace_back(data[i], data[j], data[k]);
      }
      if (delta < 0ll)
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

std::vector<std::tuple<int,int,int>> sum3(std::vector<int> const& in)
{
  return sum3_impl(in);
}

