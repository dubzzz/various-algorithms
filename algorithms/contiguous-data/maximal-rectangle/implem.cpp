#include <cstddef>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::size_t largest_area(std::vector<std::vector<bool>> const& matrix)
{
  std::size_t max_area = 0;
  std::vector<std::size_t> last_start(matrix[0].size(), 0);
  for (std::size_t idx {} ; idx != matrix.size() ; ++idx)
  {
    // for all i in [|0, matrix[0].size()-1|]
    //   for all j such as last_start[i] <= j < idx
    //     matrix[j][i] is true
    
    // compute bars
    for (std::size_t i {} ; i != last_start.size() ; ++i)
    {
      if (last_start[i] >= idx) { continue; }
      std::size_t starts_at = i;
      std::size_t ends_at = i;
      while (starts_at > 0 && last_start[starts_at-1] <= last_start[i]) { --starts_at; }
      while (ends_at+1 < last_start.size() && last_start[ends_at+1] <= last_start[i]) { ++ends_at; }
      max_area = std::max(max_area, (ends_at-starts_at+1)*(idx-last_start[i]));
    }
    
    // update starts
    for (std::size_t i {} ; i != last_start.size() ; ++i)
    {
      if (! matrix[idx][i]) { last_start[i] = idx +1; }
      else if (last_start[i] >= idx) { last_start[i] = idx; }
    }
  }
  return max_area;
}

