/*
  The aim of this topic is:
    Find the longest common substring of two input strings
    Return the pair of (longest lenght and pair of longest start position (in 1, in2))
    the start position pair must be such as input1[in1:in1+length-1] == input2[in2:in2+length-1]
*/

#pragma once
#include <cstddef>
#include <string>
#include <utility>

// Algorithm to be tested

std::pair<std::size_t, std::pair<std::size_t, std::size_t>> longest_common_substr(std::string const& input1, std::string const& input2);

