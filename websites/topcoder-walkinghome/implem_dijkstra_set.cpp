#include <algorithm>
#include <set>
#include <string>
#include <vector>

#ifdef DEBUG
  #include <iostream>
#endif

// Algorithm to be tested

static std::pair<int,int> find_cell(std::vector<std::string> const& map, char cell_type)
{
  for (std::size_t idx {} ; idx != map.size() ; ++idx)
  {
    auto found = std::find(map[idx].begin(), map[idx].end(), cell_type);
    if (found != map[idx].end())
    {
      return std::make_pair(std::distance(map[idx].begin(), found), idx);
    }
  }
  return std::make_pair(-1, -1);
}

static std::size_t to_index(std::vector<std::string> const& map, std::pair<std::size_t, std::size_t> const& p)
{
  return p.first + p.second * map[0].size();
}
static std::pair<std::size_t, std::size_t> from_index(std::vector<std::string> const& map, std::size_t idx)
{
  return std::make_pair(idx % map[0].size(), idx / map[0].size());
}

static void update_if_allowed(std::vector<std::string> const& map, std::set<std::pair<int, std::size_t>>& tobeanalyzed, std::vector<int>& distances, std::pair<std::size_t, std::size_t> const& prev, std::pair<std::size_t, std::size_t> const& next, char forbidden)
{//prev is not at dist = -1
  if (next.first >= map[0].size() || next.second >= map.size()) { return; }
  
  char prev_val = map[prev.second][prev.first];
  char next_val = map[next.second][next.first];
  
  if (next_val == forbidden) { return; }
  
  auto prev_dist = distances[to_index(map, prev)];
  auto next_idx = to_index(map, next);
  auto& next_dist = distances[next_idx];
  
  auto try_update = [&](auto should_be)
  {
    if (next_dist == -1)
    {
      #ifdef DEBUG
        std::cout << "-> (" << next.first << "," << next.second << ") updated from " << next_dist << " to " << should_be << std::endl;
      #endif
      next_dist = should_be;
      tobeanalyzed.emplace(next_dist, next_idx);
    }
    else if (should_be < next_dist)
    {
      #ifdef DEBUG
        std::cout << "-> (" << next.first << "," << next.second << ") updated from " << next_dist << " to " << should_be << std::endl;
      #endif
      auto it = tobeanalyzed.find(std::make_pair(next_dist, next_idx));
      if (it != tobeanalyzed.end()) { tobeanalyzed.erase(it); }
      next_dist = should_be;
      tobeanalyzed.emplace(next_dist, next_idx);
    }
  };
  
  switch (next_val)
  {
    case '|':
      if (prev_val == '-') { return; }
      try_update(prev_dist);
      break;
    case '-':
      if (prev_val == '|') { return; }
      try_update(prev_dist);
      break;
    case '.':
    case 'H':
      if (prev_val == '|' || prev_val == '-')
      {
        if (prev_val == forbidden) { return; }
        try_update(prev_dist +1);
      }
      else
      {
        try_update(prev_dist);
      }
      break;
  };
}

int fewest_crossings(std::vector<std::string> const& map)
{
  const auto start_pt = find_cell(map, 'S');
  const auto end_pt = find_cell(map, 'H');
  
  const std::size_t num_vertices { map.size() * map[0].size() };
  std::vector<int> distances(num_vertices, -1);
  std::set<std::pair<int, std::size_t>> tobeanalyzed;
  
  const std::size_t start_idx = to_index(map, start_pt);
  distances[start_idx] = 0;
  tobeanalyzed.emplace(0, start_idx);
  while (! tobeanalyzed.empty())
  {
    // find the closest point not analyzed yet
    
    std::size_t idx_min { tobeanalyzed.begin()->second };
    auto pt_min = from_index(map, idx_min);
    #ifdef DEBUG
      std::cout << "Analyzing (" << pt_min.first << ", " << pt_min.second << ") at distance " << tobeanalyzed.begin()->first << std::endl;
    #endif
    
    // treat selected point
    tobeanalyzed.erase(tobeanalyzed.begin());
    update_if_allowed(map, tobeanalyzed, distances, pt_min, std::make_pair(pt_min.first -1,    pt_min.second), '-');
    update_if_allowed(map, tobeanalyzed, distances, pt_min, std::make_pair(pt_min.first +1,    pt_min.second), '-');
    update_if_allowed(map, tobeanalyzed, distances, pt_min, std::make_pair(pt_min.first   , pt_min.second -1), '|');
    update_if_allowed(map, tobeanalyzed, distances, pt_min, std::make_pair(pt_min.first   , pt_min.second +1), '|');
  }
  return distances[to_index(map, end_pt)];
}

