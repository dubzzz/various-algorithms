#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

/*
// Exact application of the rules
std::string business_tasks(std::vector<std::string> const& tasks_in, unsigned n)
{
  auto tasks = tasks_in;
  std::size_t current {};
  while (tasks.size() > 1)
  {
    for (unsigned ctn {1} ; ctn != n ; ++ctn)
    {
      ++current;
      if (current >= tasks.size()) { current = 0; }
    }
    
    tasks.erase(tasks.begin() + current);
    if (current >= tasks.size()) { current = 0; } 
  }
  return tasks.back();
}
*/

std::string business_tasks(std::vector<std::string> const& tasks_in, unsigned n)
{
  auto tasks = tasks_in;
  std::size_t current {};
  while (tasks.size() > 1)
  {
    current += n - 1;
    current %= tasks.size();
    tasks.erase(tasks.begin() + current);
  }
  return tasks.back();
}

