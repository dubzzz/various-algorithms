#include <string>
#include <utility>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::pair<std::size_t, std::pair<std::size_t, std::size_t>> longest_common_substr(std::string const& input1, std::string const& input2)
{
  // N = len(input1)
  // M = len(input2)
  
  // space complexity: O(N x M)
  // time complexity: O(N x M)
  
  std::vector<std::vector<std::size_t>> helper(input1.size(), std::vector<std::size_t>(input2.size()));
  
  auto max_length = std::size_t{};
  auto max_pos = std::pair<std::size_t, std::size_t>{};
  for (std::size_t idx1 {} ; idx1 < input1.size() ; ++idx1)
  {
  // At loop #idx1:
  //   for all i<idx1, for all j<input2.size()
  //   helper[i][j] = number of characters in common between input1[:i+1] and input2[:j+1]
    for (std::size_t idx2 {} ; idx2 < input2.size() ; ++idx2)
    {
    // At loop #idx1, #idx2:
    //   for all i<idx1, for all j<idx2
    //   helper[i][j] = number of characters in common between input1[:i+1] and input2[:j+1]
      if (input1[idx1] == input2[idx2])
      {
        auto length = (idx1>0 && idx2>0) ? helper[idx1-1][idx2-1] +1 : 1;
        helper[idx1][idx2] = length;
        if (length > max_length)
        {
          max_length = length;
          max_pos = std::make_pair(idx1+1 -length, idx2+1 -length);
        }
      }//else: helper[idx1][idx2] is already zero
    }
  }
  return std::make_pair(max_length, max_pos);
}

