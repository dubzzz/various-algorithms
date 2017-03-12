#include <algorithm>
#include <climits>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

std::size_t longest_no_repeat(std::string const& in)
{
  std::vector<std::size_t> last_seen(256, 0);
  std::size_t longest_length = 0;
  std::size_t begin = 0;
  for (std::size_t cur = 0 ; cur != in.size() ; ++cur)
  {
    if (last_seen[in[cur] - CHAR_MIN] > 0 && last_seen[in[cur] - CHAR_MIN] -1 >= begin)
    {
      longest_length = std::max(longest_length, cur-begin);
      begin = last_seen[in[cur] - CHAR_MIN];
    }
    last_seen[in[cur] - CHAR_MIN] = cur+1;
  }
  return std::max(longest_length, in.size()-begin);
}

