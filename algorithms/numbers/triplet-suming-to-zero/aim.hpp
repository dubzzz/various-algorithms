/*
  The aim of this topic is:
    Taken from http://www.programcreek.com/2012/12/leetcode-3sum/
    Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
    The solution set must not contain duplicate triplets.

    a+b+c overflows giving 0 are not considered as solutions
*/

#pragma once
#include <tuple>
#include <vector>

// Algorithm to be tested

std::vector<std::tuple<int,int,int>> sum3(std::vector<int> const&);

