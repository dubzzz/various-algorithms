#include <vector>

// Algorithm to be tested

std::vector<int> product_except(std::vector<int> const& data)
{
  std::vector<int> out;

  // After thid step: out[i] = product data[0..i[
  int acc = 1;
  for (auto d : data)
  {
    out.push_back(acc);
    acc *= d;
  }

  // After this step: out is the answer
  acc = 1;
  for (std::size_t i {} ; i != data.size() ; ++i)
  {
    out[data.size()-i-1] *= acc;
    acc *= data[data.size()-i-1];
  }

  return out;
}

#include "tests.hpp"

