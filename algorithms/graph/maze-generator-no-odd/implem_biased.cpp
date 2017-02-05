#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

#include "aim.hpp"
#include "maze.hpp"

struct Delta
{
  int x, y;
  Delta() = default;
  Delta(int x, int y) : x(x), y(y) {}
  Delta(Delta&&) = default;
  Delta(Delta const&) = default;
  Delta& operator=(Delta&&) = default;
  Delta& operator=(Delta const&) = default;
  bool operator==(Delta const& other) const { return x == other.x && y == other.y; }
  bool operator!=(Delta const& other) const { return !(*this == other); }
  bool operator<(Delta const& other) const { return x < other.x || (x == other.x && y < other.y); }
};

static unsigned distance(Point const& p1, Point const& p2)
{
  int dx = (int)p1.x - (int)p2.x;
  int dy = (int)p1.y - (int)p2.y;
  return dx*dx + dy*dy;
}

template <class Gen>
static void custom_shuffle(std::vector<Delta>& choices, Point const& start_pt, Point const& end_pt, Point const& pt, bool is_solution, Gen& g)
{
  if (choices.empty())
  {
    return;
  }

  // is_solution: true:
  //  we try to reach the end as quick as possible
  // is_solution: false
  //  the nearest is end_pt, we try to reach start_pt
  //  the nearest is start_pt, we try to reach end_pt
  Point target { is_solution || distance(start_pt, pt) < distance(end_pt, pt) ? end_pt : start_pt };
  std::vector<unsigned> biased;
  std::transform(choices.begin(), choices.end()
      , std::back_inserter(biased)
      , [target, pt](auto d) { return distance(Point{pt.x+d.x, pt.y+d.y}, target); });
  auto best_idx = std::min_element(biased.begin(), biased.end()) - biased.begin();
  auto best_pt = choices[best_idx];
  choices.push_back(best_pt);

  std::shuffle(choices.begin(), choices.end(), g);
  choices.erase(std::find(choices.begin(), choices.end(), best_pt)); //choices is read in reverse order
}

#define OVERRIDE_SHUFFLE
#include "implem_from_solution.cpp"
