#include <numeric>
#include <vector>

#include SPECIFIC_HEADER

int main(int /*argc*/, char** /*argv*/)
{
  constexpr unsigned num_entries = 1e7;
  std::vector<int> in(num_entries);
  std::iota(std::begin(in), std::end(in), 0);
  auto out = product_except(in);
  
  bool success = out[1] == 0;
  return !success;
}
