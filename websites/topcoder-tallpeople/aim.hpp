/*
  The aim of this topic is:
    TopCoder: https://community.topcoder.com/stat?c=problem_statement&pm=2923&rd=5854
    
  Problem:
    A group of people stand before you arranged in rows and columns. Looking from above, they form an R by C rectangle of people.
    You will be given a String[] people containing the height of each person. Elements of people correspond to rows in the rectangle.
    Each element contains a space-delimited list of integers representing the heights of the people in that row. Your job is to return 2 specific heights in a int[].
    The first is computed by finding the shortest person in each row, and then finding the tallest person among them (the "tallest-of-the-shortest").
    The second is computed by finding the tallest person in each column, and then finding the shortest person among them (the "shortest-of-the-tallest").
  
  Constraints:
    People will contain between 2 and 50 elements inclusive.
    Each element of people will contain between 3 and 50 characters inclusive.
    Each element of people will be a single space-delimited list of positive integers such that: 

    1) Each positive integer is between 1 and 1000 inclusive with no extra leading zeros.

    2) Each element contains the same number of integers.

    3) Each element contains at least 2 positive integers.

    4) Each element does not contain leading or trailing whitespace.*/

#pragma once
#include <string>
#include <utility>
#include <vector>

// Algorithm to be tested

std::pair<int,int> tall_people(std::vector<std::string> const& people);

