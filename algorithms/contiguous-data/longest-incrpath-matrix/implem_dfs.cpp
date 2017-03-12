#include <algorithm>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

static std::size_t longest_incr_helper(std::vector<std::vector<int>> const& matrix
    , std::size_t i, std::size_t j
    , std::vector<std::vector<std::size_t>>& mem)
{
  if (mem[j][i]) { return mem[j][i]; }
  
  std::size_t longest = 1; //itself alone measure 1
  if (i > 0 && matrix[j][i] < matrix[j][i-1]) longest = std::max(longest, 1+longest_incr_helper(matrix, i-1, j, mem));
  if (i+1 < matrix[0].size() && matrix[j][i] < matrix[j][i+1]) longest = std::max(longest, 1+longest_incr_helper(matrix, i+1, j, mem));
  if (j > 0 && matrix[j][i] < matrix[j-1][i]) longest = std::max(longest, 1+longest_incr_helper(matrix, i, j-1, mem));
  if (j+1 < matrix.size() && matrix[j][i] < matrix[j+1][i]) longest = std::max(longest, 1+longest_incr_helper(matrix, i, j+1, mem));
  
  mem[j][i] = longest;
  return longest;
}

std::size_t longest_incr(std::vector<std::vector<int>> const& matrix)
{
  std::vector<std::vector<std::size_t>> mem(matrix.size(), std::vector<std::size_t>(matrix[0].size()));
  std::size_t longest = 0;
  for (std::size_t j {} ; j != matrix.size() ; ++j)
    for (std::size_t i {} ; i != matrix[0].size() ; ++i)
      longest = std::max(longest, longest_incr_helper(matrix, i, j, mem));
  return longest;
}

