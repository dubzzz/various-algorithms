#include <algorithm>
#include <iterator>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

bool has_non_filled(bool** map, std::pair<int,int>& pt)
{
  for (std::size_t j {} ; j != ROW ; ++j)
  {
    for (std::size_t i {} ; i != COL ; ++i)
    {
      if (! map[j][i])
      {
        pt = std::make_pair((int)i, (int)j);
        return true;
      }
    }
  }
  return false;
}

std::vector<int> sorted_areas(std::vector<std::string> const& rectangles)
{
  std::vector<int> out;
  
  bool** map = new bool*[ROW];
  std::generate(map, map+ROW, []() { return new bool[COL]; });
  std::for_each(map, map+ROW, [](auto line) { std::fill(line, line+COL, false); });
  
  for (auto const& rect : rectangles)
  {
    std::vector<int> dims;
    std::istringstream iss(rect);
    std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), std::back_inserter(dims));
    std::for_each(map+dims[0], map+dims[2]+1, [&dims](auto line) { std::fill(line+dims[1], line+dims[3]+1, true); });
  }
  
  std::pair<int,int> pt {};
  while (has_non_filled(map, pt))
  {
    int nums {};
    std::queue<std::pair<int,int>> nexts;
    nexts.emplace(pt);
    while (! nexts.empty())
    {
      auto current = nexts.front();
      nexts.pop();
      
      if (current.first < 0 || (std::size_t)current.first >= COL) { continue; }
      if (current.second < 0 || (std::size_t)current.second >= ROW) { continue; }
      if (map[current.second][current.first]) { continue; }
      
      ++nums;
      map[current.second][current.first] = true;
      nexts.emplace(current.first +1,    current.second);
      nexts.emplace(current.first -1,    current.second);
      nexts.emplace(current.first   , current.second +1);
      nexts.emplace(current.first   , current.second -1);
    }
    out.push_back(nums);
  }
  
  std::for_each(map, map+ROW, [](auto line) { delete[] line; });
  delete[] map;
  
  std::sort(out.begin(), out.end());
  return out;
}

