#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <utility>
#include <vector>

#include "array2d.hpp"
#include "maze.hpp"
#include SPECIFIC_HEADER

namespace {
struct Delta
{
  int x, y;
  Delta(int x, int y) : x(x), y(y) {}
};
}

static bool is_road_extended(char** maze, Dimension const& dim, Point const& pt)
{
  return pt.x < dim.width && pt.y < dim.height
      && (maze[pt.y][pt.x] == to_char(MazeElement::Start) || maze[pt.y][pt.x] == to_char(MazeElement::End) || maze[pt.y][pt.x] == to_char(MazeElement::Road));
}

static void reset_visited(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt)
{
  const char visited { to_char(MazeElement::Undefined) };
  const char road { to_char(MazeElement::Road) };
  for (std::size_t j {} ; j != dim.height ; ++j)
  {
    for (std::size_t i {} ; i != dim.width ; ++i)
    {
      if (maze[j][i] == visited) { maze[j][i] = road; }
    }
  }
  maze[start_pt.y][start_pt.x] = to_char(MazeElement::Start);
  maze[end_pt.y][end_pt.x] = to_char(MazeElement::End);
}

template <class Pred, class Apply>
void apply_if(Point const& pt, Delta const& d, Pred&& predicate, Apply&& apply)
{
  auto inter_pt = Point{pt.x + d.x, pt.y + d.y};
  auto end_pt = Point{pt.x + d.x, pt.y + d.y};
  if (predicate(inter_pt) && predicate(end_pt)) {
    apply(end_pt);
  }
}

static auto astar_analysis(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt)
{
  const char end = to_char(MazeElement::End);
  auto num_tries = std::size_t{};

  using item_type = std::pair<Point, std::size_t>;
  auto comparator = [end_pt](item_type const& i1, item_type const& i2)
  {
      double d1 = i1.second + sqrt((i1.first.x - end_pt.x)*(i1.first.x - end_pt.x) + (i1.first.y - end_pt.y)*(i1.first.y - end_pt.y));
      double d2 = i2.second + sqrt((i2.first.x - end_pt.x)*(i2.first.x - end_pt.x) + (i2.first.y - end_pt.y)*(i2.first.y - end_pt.y));
    return d1 > d2;
  };
  std::priority_queue<item_type, std::vector<item_type>, decltype(comparator)> next_choices { comparator };
  next_choices.emplace(start_pt, 0);
  while (next_choices.top().first != end_pt)
  {
    auto item = next_choices.top();
    next_choices.pop();

    auto predicate = [&maze, &dim](auto&& pt) { return is_road_extended(maze, dim, pt); };
    auto apply = [&maze, &next_choices, iters=item.second+1](auto&& pt) {
      maze[pt.y][pt.x] = to_char(MazeElement::Undefined);
      next_choices.emplace(pt, iters);
    };
    
    apply_if(item.first, Delta{-1, 0}, predicate, apply);
    apply_if(item.first, Delta{ 1, 0}, predicate, apply);
    apply_if(item.first, Delta{ 0,-1}, predicate, apply);
    apply_if(item.first, Delta{ 0, 1}, predicate, apply);

    ++num_tries;
  }

  reset_visited(maze, dim, start_pt, end_pt);
  return std::make_pair(num_tries, next_choices.top().second);
}

static double astar_report(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt)
{
  auto norm_astar_out = astar_analysis(maze, dim, start_pt, end_pt);
  auto rev_astar_out = astar_analysis(maze, dim, end_pt, start_pt);
  double norm_astar_contrib = (double)norm_astar_out.first / (double)norm_astar_out.second - 1.;
  double rev_astar_contrib = (double)rev_astar_out.first / (double)rev_astar_out.second - 1.;
  double astar_score = norm_astar_contrib + rev_astar_contrib;
  std::cout << "A* difficulty: [score: " << astar_score << ']' << std::endl;
  std::cout << "- Start to end: [contrib: " << norm_astar_contrib << ']' << std::endl;
  std::cout << "  - Number of roads visited: " << norm_astar_out.first << std::endl;
  std::cout << "  - Path length            : " << norm_astar_out.second << std::endl;
  std::cout << "- End to start: [contrib: " << rev_astar_contrib << ']' << std::endl;
  std::cout << "  - Number of roads visited: " << rev_astar_out.first << std::endl;
  std::cout << "  - Path length            : " << rev_astar_out.second << std::endl;
  return astar_score;
}

static bool starts_with(std::string const& to_check, std::string const& pattern)
{
  return to_check.substr(0, pattern.size()) == pattern;
}

int main(int argc, char** argv)
{
  std::random_device rd;
  std::cout << std::setprecision(2);
  
  auto dim = Dimension{35,15};
  auto num_gens = unsigned{1};

  for (int idx {1} ; idx != argc ; ++idx)
  {
    auto current = std::string{argv[idx]};
    if (current == "--help")
    {
      std::cout << "------ HELP ------" << std::endl;
      std::cout << std::endl;
      std::cout << "Syntax:" << std::endl;
      std::cout << "--num=<number=1>     : number of mazes" << std::endl;
      std::cout << "--width=<number=35>  : width of the generated maze" << std::endl;
      std::cout << "--height=<number=15> : height of the generated maze" << std::endl;
      return 0;
    }
    else if (starts_with(current, "--height=")) { dim.height = std::stoi(current.substr(9)); }
    else if (starts_with(current, "--width="))  { dim.width = std::stoi(current.substr(8)); }
    else if (starts_with(current, "--num="))    { num_gens = std::stoi(current.substr(6)); }
  }
  if (dim.height == 1 && dim.width == 1)
  {
    std::cout << "ERROR: One of the maze dimensions must be greater than 1" << std::endl;
    return 1;
  }
  if (dim.height % 2 == 0 && dim.width % 2 == 0)
  {
    std::cout << "ERROR: Maze dimensions must be odd numbers" << std::endl;
    return 1;
  }

  std::array<double, 1> agg_scores;
  std::fill(agg_scores.begin(), agg_scores.end(), 0.);

  for (unsigned num{} ; num != num_gens ; ++num)
  {
    if (num)
    {
      std::cout << std::endl << "---" << std::endl << std::endl;
    }
    auto start_pt = Point{0,0};
    auto end_pt = Point{dim.width -1,dim.height -1};

    Array2D array2d(dim);
    generate_maze(array2d.data(), dim, start_pt, end_pt, rd());
    std::cout << "Maze #" << (num+1) << ':' << std::endl;
    array2d.print(std::cout);
    std::cout << std::endl;

    agg_scores[0] += astar_report(array2d.data(), dim, start_pt, end_pt);
  }

  std::cout << std::endl << "---" << std::endl << std::endl;
  std::cout << "Average A* difficulty: " << (agg_scores[0]/num_gens) << std::endl;
  
  return 0;
}

