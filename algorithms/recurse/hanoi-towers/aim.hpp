/*
  The aim of this topic is:
    Rebuild Hanoi tower correctly
    The towers are labeled 0, 1 and 2
    The aim is to move all the disks of 0 towards 2 by following the rules below:
    - one disk can be moved by step
    - a disk cannot be moved onto a smaller one
    HanoiTower<T> API has the following interface:
    - Number of disks in the tower: std::size_t height_of(const std::size_t tower_id) const
    - Size of the disk on the top of the tower: unsigned int head_of(const std::size_t tower_id) const
    - Take top disk of from and move it towards to: void move(const std::size_t dest, const std::size_t from)
    Start your file by #include "hanoi.hpp"
*/

#pragma once
#include "ihanoi.hpp"

// Algorithm to be tested

void hanoi(IHanoi& tower);

