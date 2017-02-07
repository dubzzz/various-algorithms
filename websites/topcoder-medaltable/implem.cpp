#include <algorithm>
#include <array>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

// Algorithm to be tested

namespace {
class Country final
{
  std::string name_;
  std::array<unsigned, 3> medals_;

public:
  explicit Country(std::string const& name) : name_(name), medals_()
  {
    std::fill(std::begin(medals_), std::end(medals_), 0);
  }
  Country(Country&& other) : name_(std::move(other.name_)), medals_()
  {
    std::copy(std::begin(other.medals_), std::end(other.medals_), std::begin(medals_));
  }
  Country(Country const&) = default;
  Country& operator=(Country&& other)
  {
    name_ = std::move(other.name_);
    std::copy(std::begin(other.medals_), std::end(other.medals_), std::begin(medals_));
    return *this;
  }
  Country& operator=(Country const&) = default;
  ~Country() = default;
  bool operator<(Country const& other) const
  {
    auto tie1 = std::tie(medals_[0], medals_[1], medals_[2]);
    auto tie2 = std::tie(other.medals_[0], other.medals_[1], other.medals_[2]);
    return tie1 < tie2 || (tie1 == tie2 && name_ > other.name_);
  }
  std::string to_string() const
  {
    std::ostringstream oss;
    oss << name_ << ' ' << medals_[0] << ' ' << medals_[1] << ' ' << medals_[2];
    return oss.str();
  }
  std::array<unsigned, 3>& medals() { return medals_; }
  std::array<unsigned, 3> const& medals() const { return medals_; }
};
}

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
  
  std::map<std::string, Country> data;
  for (auto const& podium : results_names)
  {
    for (std::size_t idx {} ; idx != 3 ; ++idx)
    {
      auto current = data.find(podium[idx]);
      if (current == data.end())
      {
        current = data.emplace(podium[idx], Country{podium[idx]}).first;
      }
      ++current->second.medals()[idx];
    }
  }
  
  std::vector<Country> ranking;
  std::transform(std::begin(data), std::end(data)
      , std::back_inserter(ranking)
      , [](auto const& p) { return std::move(p.second); });
  std::sort(std::begin(ranking), std::end(ranking), [](auto const& c1, auto const& c2) { return !(c1 < c2); });
  
  std::vector<std::string> out;
  std::transform(std::begin(ranking), std::end(ranking)
      , std::back_inserter(out)
      , [](auto const& country) { return country.to_string(); });
  return out;
}

