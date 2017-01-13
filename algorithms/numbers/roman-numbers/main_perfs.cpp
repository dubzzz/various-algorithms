#include <string>

#include SPECIFIC_HEADER

namespace perfs {
constexpr int min_roman = -39;
constexpr int max_roman =  39;
}

int main(int /*argc*/, char** /*argv*/)
{
  unsigned out {};
  constexpr unsigned num_runs = 1e6;
  for (unsigned run_id {} ; run_id != num_runs ; ++run_id)
  {
    int num = perfs::min_roman + (run_id % (perfs::max_roman - perfs::min_roman +1));
    out += from_roman_str(to_roman_str(num)) - num;
  }
  bool success = out == unsigned();
  return !success;
}

