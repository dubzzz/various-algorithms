/*
  The aim of this topic is:
    Roman numbers are defined as succesives characters among I,V,X,L,C,D,M...
    The aim of this exercise is to write two functions:
    - from_roman_str: taking a roman string and converting it into an integer
    - to_roman_str: taking an integer and converting it into a roman string
    More details on roman numerals can be found on https://en.wikipedia.org/wiki/Roman_numerals

    You may suppose that entries would be correct numbers or roman strings
    0 is equivalent to "0"
    negative numbers equivalent to "-" + to_roman_str(-number)

    If your algorithm does not apply for all the possible characters defined into checks::letters_value (below)
    You can override the number of letters selected by using the macro LIMIT_TO_X_LETTERS
*/

#pragma once
#include <string>

// Algorithm to be tested

int from_roman_str(std::string const&);
std::string to_roman_str(int);

