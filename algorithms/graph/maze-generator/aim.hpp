/*
  The aim of this topic is:
    Fill an array with a random maze
    Maze has to fullfill several properties decribed in main.cpp (using RapidCheck)

    Point -> maze[y][x]
    x : [0 ;  dim.width[
    y : [0 ; dim.height[
*/

#pragma once
#include "maze.hpp"

// Algorithm to be tested

void generate_maze(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt, unsigned seed);

