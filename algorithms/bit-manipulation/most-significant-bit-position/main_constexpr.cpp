#include <iostream>
#include SPECIFIC_HEADER

int main(int /*argc*/, char** /*argv*/)
{
  #if ! defined(NO_CONSTEXPR)
    static_assert(most_significant_position(0) == 0, "most_significant_position(0) is 0");
    static_assert(most_significant_position(8) == 4, "most_significant_position(8) is 4");
    std::cout << "constexpr enabled" << std::endl;
  #else
    std::cout << "constexpr not enabled" << std::endl;
  #endif
  return 0;
}

