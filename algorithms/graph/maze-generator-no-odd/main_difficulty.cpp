#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <queue>
#include <numeric>
#include <random>
#include <stack>
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

static auto all_paths_analysis(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt)
{
  auto all_paths = std::vector<std::vector<Point>>{};
  auto under_analysis = std::stack<std::vector<Point>>{};
  under_analysis.emplace(std::vector<Point>{start_pt});
  while (! under_analysis.empty())
  {
    auto path = std::move(under_analysis.top());
    under_analysis.pop();

    bool has_child {};
    auto predicate = [&maze, &dim](auto&& pt) { return is_road_extended(maze, dim, pt); };
    auto apply = [&maze, &path, &has_child, &under_analysis](auto&& pt) {
      has_child = true;
      maze[pt.y][pt.x] = to_char(MazeElement::Undefined);
      auto cloned = path;
      cloned.push_back(pt);
      under_analysis.emplace(std::move(cloned));
    };
    
    apply_if(path.back(), Delta{-1, 0}, predicate, apply);
    apply_if(path.back(), Delta{ 1, 0}, predicate, apply);
    apply_if(path.back(), Delta{ 0,-1}, predicate, apply);
    apply_if(path.back(), Delta{ 0, 1}, predicate, apply);

    if (! has_child)
    {
      all_paths.push_back(path);
    }
  }

  reset_visited(maze, dim, start_pt, end_pt);
  return all_paths;
}

template <class Container> static double mean(Container const& ctn)
{
  return std::accumulate(ctn.begin(), ctn.end(), 0., [](auto acc, auto val) { return acc + val; }) / ctn.size();
}
template <class Container> static double variance(Container ctn)
{
  double m = mean(ctn);
  std::transform(ctn.begin(), ctn.end(), ctn.begin(), [m](auto v) { return v - m; });
  std::transform(ctn.begin(), ctn.end(), ctn.begin(), [](auto v) { return v * v; });
  return mean(ctn);
}
template <class Container> static double standard_deviation(Container const& ctn)
{
  return std::sqrt(variance(ctn));
}

static double allpaths_report(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt)
{
  auto all_paths = all_paths_analysis(maze, dim, start_pt, end_pt);
  auto num_paths = all_paths.size();

  auto paths_from_solution = all_paths;
  auto answer_it = std::find_if(paths_from_solution.begin(), paths_from_solution.end(), [end_pt](auto&& v){ return v.back() == end_pt; });
  const auto answer = *answer_it;
  paths_from_solution.erase(answer_it);
  for (auto& path : paths_from_solution)
  {
    auto diff_at = std::mismatch(path.begin(), path.end(), answer.begin(), answer.end());
    path.erase(path.begin(), diff_at.first);
  }

  std::vector<std::size_t> lengths_from_start;
  std::transform(all_paths.begin(), all_paths.end(), std::back_inserter(lengths_from_start), [](auto&& v) { return v.size(); });
  std::vector<std::size_t> lengths_from_solution;
  std::transform(paths_from_solution.begin(), paths_from_solution.end(), std::back_inserter(lengths_from_solution), [](auto&& v) { return v.size(); });
  
  double score = num_paths * mean(lengths_from_solution) / (std::sqrt(dim.width*dim.height) * standard_deviation(lengths_from_solution));
  std::cout << "All paths: [score: " << score << ']' << std::endl;
  std::cout << "- Length of solution: " << answer.size() << std::endl;
  std::cout << "- Number of paths   : " << num_paths << std::endl;
  std::cout << "- From start:" << std::endl;
  std::cout << "  - Length mean              : " << mean(lengths_from_start) << std::endl;
  std::cout << "  - Length standard deviation: " << standard_deviation(lengths_from_start) << std::endl;
  std::cout << "  - Lengths                  : [";
  std::copy(lengths_from_start.begin(), lengths_from_start.end(), std::ostream_iterator<std::size_t>(std::cout, ","));
  std::cout << ']' << std::endl;
  std::cout << "- From solution:" << std::endl;
  std::cout << "  - Length mean              : " << mean(lengths_from_solution) << std::endl;
  std::cout << "  - Length standard deviation: " << standard_deviation(lengths_from_solution) << std::endl;
  std::cout << "  - Lengths                  : [";
  std::copy(lengths_from_solution.begin(), lengths_from_solution.end(), std::ostream_iterator<std::size_t>(std::cout, ","));
  std::cout << ']' << std::endl;
  return score;
}

static bool starts_with(std::string const& to_check, std::string const& pattern)
{
  return to_check.substr(0, pattern.size()) == pattern;
}

int main(int argc, char** argv)
{
  std::random_device rd;
  std::cout << std::setprecision(3);
  
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
    else
    {
      std::cout << "Unknown param: " << current << std::endl;
      std::cout << "Use --help to display help" << std::endl;
      return 1;
    }
  }
  if (dim.height == 1 && dim.width == 1)
  {
    std::cout << "ERROR: One of the maze dimensions must be greater than 1" << std::endl;
    return 1;
  }
  if (dim.height % 2 == 0 || dim.width % 2 == 0)
  {
    std::cout << "ERROR: Maze dimensions must be odd numbers" << std::endl;
    return 1;
  }

  std::array<double, 2> agg_scores;
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
    agg_scores[1] += allpaths_report(array2d.data(), dim, start_pt, end_pt);
  }

  std::cout << std::endl << "---" << std::endl << std::endl;
  std::cout << "Average A* difficulty: " << (agg_scores[0]/num_gens) << std::endl;
  std::cout << "Average all paths    : " << (agg_scores[1]/num_gens) << std::endl;
  
  return 0;
}

