/*
  The aim of this topic is:
    TopCoder: https://community.topcoder.com/stat?c=problem_statement&pm=3935&rd=6532
    
  Problem:
    The toy company "I Can't Believe It Works!" has hired you to help develop educational toys.
    The current project is a word toy that displays four letters at all times. Below each letter are two buttons that cause the letter above to change to the previous or next letter in alphabetical order.
    So, with one click of a button the letter 'c' can be changed to a 'b' or a 'd'. The alphabet is circular, so for example an 'a' can become a 'z' or a 'b' with one click.

    In order to test the toy, you would like to know if a word can be reached from some starting word, given one or more constraints. A constraint defines a set of forbidden words that can never be displayed by the toy.
    Each constraint is formatted like "X X X X", where each X is a string of lowercase letters.
    A word is defined by a constraint if the ith letter of the word is contained in the ith X of the contraint.
    For example, the constraint "lf a tc e" defines the words "late", "fate", "lace" and "face".

    You will be given a String start, a String finish, and a String[] forbid.
    Calculate and return the minimum number of button presses required for the toy to show the word finish if the toy was originally showing the word start.
    Remember, the toy must never show a forbidden word. If it is impossible for the toy to ever show the desired word, return -1.

  Constraints:
    start and finish will contain exactly four characters.
    start and finish will contain only lowercase letters.
    forbid will contain between 0 and 50 elements, inclusive.
    Each element of forbid will contain between 1 and 50 characters.
    Each element of forbid will contain lowercase letters and exactly three spaces.
    Each element of forbid will not contain leading, trailing or double spaces.
    Each letter within a group of letters in each element of forbid will be distinct. Thus "aa a a a" is not allowed.
    start will not be a forbidden word    
*/

#pragma once
#include <string>
#include <vector>

// Algorithm to be tested

int min_presses(std::string const& start, std::string const& end, std::vector<std::string> const& forbidden);

