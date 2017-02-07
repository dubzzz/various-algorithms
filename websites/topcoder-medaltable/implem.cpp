#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

// Algorithm to be tested

std::vector<std::string> medal_table(std::vector<std::string> const& results)
{
  std::vector<std::vector<std::string>> results_names;
  std::transform(std::begin(results), std::end(results)
      , std::back_inserter(results_names)
      , [](auto const& names) {
          std::vector<std::string> podium;
          std::istringstream iss(names);
          std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(podium));
          return podium;
      });
  
  std::map<std::string, std::vector<unsigned>> data;
  for (auto const& podium : results_names)
  {
    for (std::size_t idx {} ; idx != 3 ; ++idx)
    {
      auto current = data.find(podium[idx]);
      if (current == data.end())
      {
        current = data.emplace(podium[idx], std::vector<unsigned>{0, 0, 0}).first;
      }
      ++current->second[idx];
    }
  }
  
  std::vector<std::pair<std::string, std::vector<unsigned>>> ranking;
  std::transform(std::begin(data), std::end(data)
      , std::back_inserter(ranking)
      , [](auto const& p) { return p; });
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

