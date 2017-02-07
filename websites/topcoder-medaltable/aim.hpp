/*
  The aim of this topic is:
    TopCoder: https://community.topcoder.com/stat?c=problem_statement&pm=2922&rd=5855
    
  Problem:
    The Olympic Games in Athens end tomorrow. Given the results of the olympic disciplines, generate and return the medal table.
    
    The results of the disciplines are given as a String[] results, where each element is in the format "GGG SSS BBB". GGG, SSS and BBB
    are the 3-letter country codes (three capital letters from 'A' to 'Z') of the countries winning the gold, silver and bronze medal, respectively.
    
    The medal table is a String[] with an element for each country appearing in results.
    Each element has to be in the format "CCO G S B" (quotes for clarity), where G, S and B are the number of gold, silver and bronze medals won by country CCO, e.g. "AUT 1 4 1".
    The numbers should not have any extra leading zeros.
    
    Sort the elements by the number of gold medals won in decreasing order.
    If several countries are tied, sort the tied countries by the number of silver medals won in decreasing order.
    If some countries are still tied, sort the tied countries by the number of bronze medals won in decreasing order.
    If a tie still remains, sort the tied countries by their 3-letter code in ascending.

  Constraints:
    Results contains between 1 and 50 elements, inclusive.
    Each element of results is formatted as described in the problem statement.
    No more than 50 different countries appear in results.
*/

#pragma once
#include <string>
#include <vector>

// Algorithm to be tested

std::vector<std::string> medal_table(std::vector<std::string> const& results);

