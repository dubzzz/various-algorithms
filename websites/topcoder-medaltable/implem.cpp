#include <algorithm>
#include <iterator>
#include <numeric>
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
  std::sort(std::begin(flat_results), std::end(flat_results), [](auto const& i1, auto const& i2) { return i1.first < i2.first; });
  
  auto ranking = std::accumulate(
      std::begin(flat_results), std::end(flat_results)
      , std::vector<std::pair<std::string, std::vector<unsigned>>>{}
      , [](auto&& acc, auto entry) {
          if (acc.empty() || acc.back().first != entry.first)
          {
            acc.emplace_back(entry.first, std::vector<unsigned>{0, 0, 0});
          }
          ++acc.back().second[entry.second];
          return acc;
      });
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

