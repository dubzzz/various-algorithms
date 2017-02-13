/*
  The aim of this topic is:
    TopCoder: https://community.topcoder.com/stat?c=problem_statement&pm=2915&rd=5853
    
  Problem:
    Harry is playing magical chess. In this version of the game, all pieces move the same way as in regular chess, but players can cast some magical spells.
    Unfortunately, Harry's opponent, Joe, has captured all of Harry's pieces except one knight; Joe, on the other hand, still has a queen and a rook.
    The only chance Harry has to win this game is to cast a spell, "Haste", that will allow Harry's knight to make several moves in a row.
    You should determine the minimal number of moves the knight needs to capture both the rook and the queen, assuming neither of them moves.
    You may capture them in either order - rook first or queen first.
    
    You will be given a String, knight, containing information about the knight.
    You will also be given a String, queen, and a String, rook, giving you information about Joe's pieces.
    knight, rook and queen will be formatted as "cr", where c is a character between 'a' and 'h', inclusive, determining the column on the board ('a' is the first column, 'h' is the last), and r is a digit between '1' and '8', inclusive, determining the row (1 is the lowest, 8 is the highest).

  Constraints:
    knight, rook and queen will all be distinct.
    knight, rook and queen will be formatted as "cr", where c is a lowercase character between 'a' and 'h', inclusive, and r is a digit between '1' and '8', inclusive
*/

#pragma once
#include <string>

// Algorithm to be tested

unsigned fast_knight(std::string const& knight, std::string const& root, std::string const& queen);

