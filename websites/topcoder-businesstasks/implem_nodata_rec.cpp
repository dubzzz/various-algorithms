#include <string>
#include <vector>

#include "aim.hpp"

/*
remains_at_the_end(size=1,n,offset)
 - return 0

//not necessary -- base case with size=1 do the job
remains_at_the_end(size=2,n,offset)
 -n+offset % 2 == 0 -> 0
 -n+offset % 2 == 1 -> 1

remains_at_the_end(size,n,offset)
 - should_remove = (n-1+offset) % size
 - ret = remains_at_the_end(size-1,n-1,(n+offset)%size)
 - return ret < should_remove ? ret : ret+1
*/

static std::size_t remains_at_the_end(std::size_t size, std::size_t n, std::size_t offset)
{
  if (size == 1) { return 0; }
  std::size_t should_remove = (n-1+offset) % size;
  std::size_t ret = remains_at_the_end(size-1,n,should_remove);
  return ret < should_remove ? ret : ret+1;
}

std::string business_tasks(std::vector<std::string> const& tasks, unsigned n)
{
  return tasks[remains_at_the_end(tasks.size(), n, 0)];
}
