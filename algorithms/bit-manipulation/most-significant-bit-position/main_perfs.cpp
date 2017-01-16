//#include <iostream>
#include SPECIFIC_HEADER

int main(int /*argc*/, char** /*argv*/)
{
  unsigned out {};
  constexpr unsigned num_runs = 10000000;
  for (unsigned run_id {} ; run_id != num_runs ; ++run_id)
  {
    out += most_significant_position(run_id);
  }
  //std::cout << out;
  bool success = out == unsigned(223222785);
  return !success;
}

