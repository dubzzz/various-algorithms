#include <algorithm>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Algorithm to be tested

std::pair<int,int> tall_people(std::vector<std::string> const& people)
{
  std::vector<std::vector<int>> adapted_data;
  std::transform(std::begin(people), std::end(people)
      , std::back_inserter(adapted_data)
      , [](auto const& desc) {
          std::vector<int> out;
          std::istringstream iss(desc);
          std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), std::back_inserter(out));
          return out;
      });
  
  std::vector<int> shortests;
  std::transform(std::begin(adapted_data), std::end(adapted_data)
      , std::back_inserter(shortests)
      , [](auto const& sizes_row) { return *std::min_element(std::begin(sizes_row), std::end(sizes_row)); });
  int tallest_of_the_shortests = *std::max_element(std::begin(shortests), std::end(shortests));
  
  std::vector<int> tallests = std::accumulate(std::begin(adapted_data), std::end(adapted_data)
      , std::vector<int>(adapted_data.back().size())
      , [](auto&& acc, auto const& row) {
          std::transform(std::begin(acc), std::end(acc)
              , std::begin(row)
              , std::begin(acc)
              , [](auto size_acc, auto size_row) { return std::max(size_acc, size_row); });
          return acc;
      });
  int shortest_of_the_tallests = *std::min_element(std::begin(tallests), std::end(tallests));
  
  return std::make_pair(tallest_of_the_shortests, shortest_of_the_tallests);
}

