/*
  The aim of this topic is:
    Given an array of short int elements, check if the sum can be computed with no overflow
    if short goes from -32768 to 32767, the array [-32768, 5000, 32767] does not overflow
    
    Return true in case of overflow
*/

#pragma once
#include <cstddef>

// Algorithm to be tested

bool overflow(short const* items, std::size_t N);

