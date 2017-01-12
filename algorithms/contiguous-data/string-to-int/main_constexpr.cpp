#include <iostream>
#include <type_traits>
#include SPECIFIC_HEADER

int main(int /*argc*/, char** /*argv*/)
{
  // check output type
  static_assert(std::is_same<int, decltype(string_to_int(""))>::value, "atoi :: must return int");
  static_assert(std::is_same<long, decltype(string_to_long(""))>::value, "atol :: must return long");
  static_assert(std::is_same<long long, decltype(string_to_longlong(""))>::value, "atoll :: must return long long");
  
  #if ! defined(NO_CONSTEXPR)
    // base 10
    static_assert(string_to_int("1") == 1, "atoi :: 1 digit number <positive>");
    static_assert(string_to_int("15") == 15, "atoi :: 2 digits number <positive>");
    static_assert(string_to_int("-42") == -42, "atoi :: negative number");
    
    // base 16
    static_assert(string_to_int("e", 16) == 14, "atoi(base:16) :: 1 digit number <positive>");
    static_assert(string_to_int("ff", 16) == 255, "atoi(base:16) :: 2 digits number <positive>");
    static_assert(string_to_int("-ffff", 16) == -65535, "atoi(base:16) :: negative number");

    std::cout << "constexpr enabled" << std::endl;
  #else
    std::cout << "constexpr not enabled" << std::endl;
  #endif
  return 0;
}
