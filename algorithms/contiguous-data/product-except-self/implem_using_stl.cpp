#include <algorithm>
#include <iterator>
#include <vector>

// Algorithm to be tested

std::vector<int> product_except_impl(std::vector<int> data)
{
  // [i] = product data[0..i[
  std::vector<int> prod_upto = {1};
  std::copy(data.begin(), data.end() -1, std::back_inserter(prod_upto));
  std::transform(prod_upto.begin(), prod_upto.end() -1
      , prod_upto.begin() +1
      , prod_upto.begin() +1
      , [](auto prod, auto cur) { return prod * cur; });

  // [size-i-1] = product data]i..size-1]
  std::vector<int> prod_from_rev = {1};
  std::copy(data.rbegin(), data.rend() -1, std::back_inserter(prod_from_rev));
  std::transform(prod_from_rev.begin(), prod_from_rev.end() -1
      , prod_from_rev.begin() +1
      , prod_from_rev.begin() +1
      , [](auto prod, auto cur) { return prod * cur; });

  for (std::size_t i {} ; i != data.size() ; ++i)
  {
    data[i] = prod_upto[i] * prod_from_rev[prod_from_rev.size()-i-1];
  }
  return data;
}

std::vector<int> product_except(std::vector<int> const& data)
{
  return product_except_impl(data);
}

#include "tests.hpp"

