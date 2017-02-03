/*
  The aim of this topic is:
    Fill an array with a random maze
    Maze has to fullfill several properties decribed in main.cpp (using RapidCheck)
    
    Paths are only allowed on even positions
    eg.: we cannot have roads on postions such as there is an (i,j) / (2*i+1, 2*j+1) = position

    Point -> maze[y][x]
    x : [0 ;  dim.width[
    y : [0 ; dim.height[
*/

#pragma once
#include "maze.hpp"

// Algorithm to be tested

void generate_maze(char** maze, Dimension const& dim, Point const& start_pt, Point const& end_pt, unsigned seed);

