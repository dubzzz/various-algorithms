#include <string>

#include "aim.hpp"

// Algorithm to be tested

// In-place

static bool is_vowel(char c)
{
  return c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o' || c == 'y'
      || c == 'A' || c == 'E' || c == 'I' || c == 'U' || c == 'O' || c == 'Y';
}

static std::size_t move_left(std::string const& in, std::size_t idx)
{
  while (idx > 0 && ! is_vowel(in[idx])) { --idx; }
  return idx;
}
static std::size_t move_right(std::string const& in, std::size_t idx)
{
  while (idx < in.size() && ! is_vowel(in[idx])) { ++idx; }
  return idx;
}

std::string reverse_vowels(std::string const& in_)
{
  std::string in = in_;
  if (in.empty()) { return in; }
  
  std::size_t start, end;
  for (start = move_right(in, 0), end = move_left(in, in.size() -1)
      ; start < end
      ; start = move_right(in, start+1), end = move_left(in, end-1))
  {
    char t = in[start];
    in[start] = in[end];
    in[end] = t;
  }
  return in;
}

