#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>

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

struct IterItem
{
  int num_roads;
  std::pair<int, int> position;

  IterItem(int num_roads, std::pair<int,int> const& position) : num_roads(num_roads), position(position) {}
  bool operator<(IterItem const& other) const { return num_roads > other.num_roads; }
};

static char& cell_at(std::vector<std::string>& map, std::pair<int,int> const& pt)
{
  return map[pt.second][pt.first];
}
static bool is_road(std::vector<std::string>& map, std::pair<int,int> const& pt)
{
  char cell = cell_at(map, pt);
  return cell == '|' || cell == '-' || cell == '!' || cell == '~';
}
static bool is_ok(std::vector<std::string>& map, std::pair<int,int> const& pt)
{
  char cell = cell_at(map, pt);
  return cell == '|' || cell == '-' || cell == '.' || cell == 'H';
}
static void nok(std::vector<std::string>& map, std::pair<int,int> const& pt)
{
  char& cell = cell_at(map, pt);
  switch (cell)
  {
    case '|': cell = '!'; break;
    case '-': cell = '~'; break;
    case 'H': break;
    default: cell = '?'; break;
  };
}

static void push_first_time(std::vector<std::string>& map,  std::priority_queue<IterItem>& nexts, int num_roads, std::pair<int,int> const& pt, std::pair<int,int> const& prev, char forbidden)
{
  if (pt.first < 0 || (std::size_t)pt.first >= map[0].size()) { return; }
  if (pt.second < 0 || (std::size_t)pt.second >= map.size()) { return; }
  if (is_ok(map, pt) && cell_at(map, pt) != forbidden)
  {
    if (! is_road(map, pt) && cell_at(map, prev) == (forbidden == '-' ? '~' : '!'))
    {
      return;
    }
    
    if (is_road(map, pt))
    {
      if (is_road(map, prev))
      {
        char prev_road { cell_at(map, prev) == '~' ? '-' : '|' };
        if (prev_road != cell_at(map, pt)) { return; }
      }
      else
      {
        ++num_roads;
      }
    }
    nok(map, pt);
    nexts.emplace(num_roads, pt);
  }
}

int fewest_crossings(std::vector<std::string> const& map_)
{
  auto map = map_;
  auto start_pt = find_cell(map, 'S');
  nok(map, start_pt);
  
  std::priority_queue<IterItem> nexts;
  nexts.emplace(0, start_pt);
  
  while (! nexts.empty())
  {
    auto item = nexts.top();
    auto num_roads = item.num_roads;
    auto const& pt = item.position;
    nexts.pop();
    
    if (cell_at(map, pt) == 'H') { return num_roads; }
    
    push_first_time(map, nexts, num_roads, std::make_pair(pt.first +1, pt.second), pt, '-');
    push_first_time(map, nexts, num_roads, std::make_pair(pt.first -1, pt.second), pt, '-');
    push_first_time(map, nexts, num_roads, std::make_pair(pt.first, pt.second +1), pt, '|');
    push_first_time(map, nexts, num_roads, std::make_pair(pt.first, pt.second -1), pt, '|');
  }
  return -1;
}

