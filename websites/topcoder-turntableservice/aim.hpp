/*
  The aim of this topic is:
    TopCoder: https://community.topcoder.com/stat?c=problem_statement&pm=3117&rd=5865
    
  Problem:
    You are out for Chinese food with a bunch of friends.
    You are all sitting at a round table, and in the center of the table is a turntable onto which all of the entrees are placed.
    There is one entree immediately in front of each of you.

    Each of you likes certain items, given as a String[] favorites, each element of which is a space delimited list of integers.
    Each integer corresponds to an entree, where 0 is the entree initially in front of person 0, etc.
    Element i of favorites contains the indexes of all the entrees that person i likes.

    The turntable rotates in either direction.
    When someone is serving himself, he can only take from the entree that is directly in front of him.
    However, he is not required to take the entree presented to him, even if it is one of his favorites.

    It takes 2 seconds to rotate the turntable by one position.
    But, to rotate it by two positions takes 3 seconds, and in general it takes n+1 seconds to rotate the turntable by n positions.
    It takes 15 seconds for a person to serve himself the entree in front of him.
    If multiple people have favorite entrees in front of them, they can serve themselves simultaneously.
    The turntable cannot be rotated while anyone is serving himself.

    You are to return an int indicating the minimum number of seconds it takes for each person to have served himself one entree.

  Constraints:
    favorites will contain between 1 and 15 elements, inclusive.
    Each element of favorites will be a list of integers, separated by a single space, with no leading or trailing spaces.
    Each element of favorites will contain only digits ('0'-'9') and spaces (' ').
    Each element of favorites will contain between 1 and 50 characters, inclusive.
    Each number in each element of favorites will be between 0 and n - 1, inclusive, where n is the number of elements in favorites. Leading zeros are permitted, and numbers may be repeated.
*/

#pragma once
#include <string>
#include <vector>

// Algorithm to be tested

int calculate_time(std::vector<std::string> const& favorites);

