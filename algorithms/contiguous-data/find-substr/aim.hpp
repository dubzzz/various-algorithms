/*
  The aim of this topic is:
    Find the first start position of a pattern in an input string
    Returns std::string::npos if the pattern is not a substring of the input

    You can suppose that both input and pattern contain only characters between A and Z inclusives
*/

#pragma once
#include <cstddef>
#include <string>

// Algorithm to be tested

std::size_t find_substr(std::string const& input, std::string const& pattern);

