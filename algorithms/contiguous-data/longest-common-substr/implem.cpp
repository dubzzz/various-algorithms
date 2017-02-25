#include <string>
#include <utility>

#include "aim.hpp"

// Algorithm to be tested

static std::size_t same_start_upto(std::string const& input1, std::string const& input2, std::size_t pos1, std::size_t pos2)
{
  // return is such that it is the highest value: input1[pos1:pos1+answer-1] == input2[pos2:pos2+answer-1]
  std::size_t common {};
  for ( ; pos1 != input1.size() && pos2 != input2.size() && input1[pos1] == input2[pos2] ; ++pos1, ++pos2, ++common) {}
  return common;
}

std::pair<std::size_t, std::pair<std::size_t, std::size_t>> longest_common_substr(std::string const& input1, std::string const& input2)
{
  // space complexity: O(1)
  // time complexity: O(n^3)
  
  auto max_length = std::size_t{};
  auto max_pos = std::pair<std::size_t, std::size_t>{};
  for (std::size_t idx1 {} ; idx1 != input1.size() ; ++idx1)
  {
    for (std::size_t idx2 {} ; idx2 != input2.size() ; ++idx2)
    {
      auto upto = same_start_upto(input1, input2, idx1, idx2);
      if (upto > max_length)
      {
        max_length = upto;
        max_pos = std::make_pair(idx1, idx2);
      }
    }
  }
  return std::make_pair(max_length, max_pos);
}

