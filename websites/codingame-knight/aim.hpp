/*
  The aim of this topic is:
    Inspired from CodinGame: https://www.codingame.com/training/medium/shadows-of-the-knight-episode-1

    Given an instance of Space<number_dimensions>, space, having dimensions space.dimensions()
    you need to find as quickly as possible the position of an hidden tale
    at each turn you can std::array<Where,number_dimensions> guess(std::array<int,number_dimensions>)
*/

#pragma once
#include "ispace.hpp"

// Algorithm to be tested

template <std::size_t DIM> std::array<std::size_t, DIM> locate_in_space(ISpace<DIM>& space);

