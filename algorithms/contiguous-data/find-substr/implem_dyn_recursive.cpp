#include <algorithm>
#include <string>
#include <vector>

#include "aim.hpp"

// Algorithm to be tested

static std::size_t find_substr_impl(std::string const& raw, std::string const& pattern, std::size_t pos_raw, std::size_t pos_pattern, std::vector<std::vector<std::size_t>>& helper)
{
   // returns the first position in raw (pos_raw <= answer < raw.size()) such as raw[answer:] == pattern[pos_pattern:]
   // otherwise std::string::npos

   if (pos_pattern == pattern.size())
   {// remaining pattern is empty, it is a match
      return pos_raw;
   }
   if (pos_raw == raw.size())
   {// remaining raw is empty, no match
      return std::string::npos;
   }

   if (helper[pos_raw][pos_pattern] != raw.size())
   {
      return helper[pos_raw][pos_pattern];
   }
   if (raw[pos_raw] == pattern[pos_pattern])
   {// is there a match starting at this position
      std::size_t sub_start = find_substr_impl(raw, pattern, pos_raw +1, pos_pattern +1, helper);
      if (sub_start == pos_raw +1)
      {
         helper[pos_raw][pos_pattern] = pos_raw;
         return pos_raw;
      }
   }

   auto answer = find_substr_impl(raw, pattern, pos_raw +1, pos_pattern, helper);
   helper[pos_raw][pos_pattern] = answer;
   return answer;
}

std::size_t find_substr(std::string const& raw, std::string const& pattern)
{
   std::vector<std::vector<std::size_t>> helper(raw.size(), std::vector<std::size_t>(pattern.size(), raw.size()));
   return find_substr_impl(raw, pattern, 0, 0, helper);
}
