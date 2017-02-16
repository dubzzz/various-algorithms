/*
  The aim of this topic is:
    TopCoder: https://community.topcoder.com/stat?c=problem_statement&pm=3064&rd=5869
    
  Problem:
    You are in a maze containing revolving doors.
    The doors can be turned 90 degrees by pushing against them in either direction.
    You are to find a route from the start square to the end square that involves revolving as few doors as possible.
    Given a map of the maze, determine the fewest number of door revolutions necessary to get from the start to the end.

    In the map:

       ' ': empty space
       '#': wall
       'O': center of a revolving door (letter "oh", not zero)
       '-': horizontal door (always adjacent to a 'O')
       '|': vertical door (always adjacent to a 'O')
       'S': start square
       'E': end square

    Each revolving door will always be oriented horizontally (with two horizontal segments) or vertically (with two vertical segments):

        |
        O  or  -O-
        |

    Doors can be revolved 90 degrees by moving onto a door segment from any of the 4 squares diagonally adjacent to the door center, i.e., the 'X' characters below:

       X|X     X X
        O  or  -O-
       X|X     X X

    Here is an example map:

            ###
            #E#
           ## #
        ####  ##
        # S -O-#
        # ###  #
        #      #
        ########

    In this example, 2 door revolutions are necessary to get from 'S' to 'E'. The first turn is shown here:

            ###         ###
            #E#         #E#
           ## #        ## #
        ####  ##    #### |##
        # S -O-#    # S  OX#
        # ### X#    # ###| #
        #      #    #      #
        ########    ########

    And the second turn is shown here:

            ###         ###
            #E#         #E#
           ## #        ## #
        ####X|##    #### X##
        # S  O #    # S -O-#
        # ###| #    # ###  #
        #      #    #      #
        ########    ########

    Your method should return an int, the minimum number of door revolutions necessary to get from the start square to the end square. If there is no way to reach the end square, return -1. 

  Constraints:
    map will contain between 3 and 50 elements, inclusive.
    Each element of map will contain between 3 and 50 characters, inclusive.
    Each element of map will contain the same number of characters.
    Each character in map will be one of 'S', 'E', 'O', '-', '|', '#', and ' ' (space).
    There will be exactly one 'S' and one 'E' in map.
    There will be between 1 and 10 doors, inclusive, and they will be formatted in map as described in the problem statement.
    No two doors will be close enough for any part of them to occupy the same square.
    It is not allowed for a door to be blocked and unable to turn. There will not be any walls in any of the 4 squares immediately adjacent to the center of a door, nor will a door be on the edge of the map.
*/

#pragma once
#include <string>
#include <vector>

// Algorithm to be tested

int turns(std::vector<std::string> const& map);

