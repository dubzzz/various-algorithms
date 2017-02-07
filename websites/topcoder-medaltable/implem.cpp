#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// Algorithm to be tested

std::vector<std::string> medal_table(std::vector<std::string> const& results)
{
  constexpr unsigned idxs[] = {0, 1, 2};
  std::vector<std::pair<std::string, unsigned>> flat_results;
  for (auto const& podium : results)
  {
    std::istringstream iss(podium);
    std::transform(
        std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()
        , std::begin(idxs)
        , std::back_inserter(flat_results)
        , [](auto const& name, auto idx) { return std::make_pair(name, idx); });
  }
  
  std::map<std::string, std::vector<unsigned>> data;
  for (auto const& entry : flat_results)
  {
    auto current = data.find(entry.first);
    if (current == data.end())
    {
      current = data.emplace(entry.first, std::vector<unsigned>{0, 0, 0}).first;
    }
    ++current->second[entry.second];
  }
  
  std::vector<std::pair<std::string, std::vector<unsigned>>> ranking;
  std::copy(std::begin(data), std::end(data), std::back_inserter(ranking));
  std::sort(std::begin(ranking), std::end(ranking)
      , [](auto const& p1, auto const& p2) {
          return !(p1.second < p2.second || (p1.second == p2.second && p1.first > p2.first));
      });
  
  std::vector<std::string> out;
  std::transform(std::begin(ranking), std::end(ranking)
      , std::back_inserter(out)
      , [](auto const& p) {
          std::ostringstream oss;
          oss << p.first << ' ' << p.second[0] << ' ' << p.second[1] << ' ' << p.second[2];
          return oss.str();
      });
  return out;
}

