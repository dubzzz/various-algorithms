/*
  The aim of this topic is:
    TopCoder: https://community.topcoder.com/stat?c=problem_statement&pm=1585&rd=6535
    
  Problem:
    A busy businessman has a number of equally important tasks which he must accomplish. To decide which of the tasks to perform first, he performs the following operation.

    He writes down all his tasks in the form of a circular list, so the first task is adjacent to the last task.
    He then thinks of a positive number. This number is the random seed, which he calls n.
    Starting with the first task, he moves clockwise (from element 1 in the list to element 2 in the list and so on), counting from 1 to n.
    When his count reaches n, he removes that task from the list and starts counting from the next available task. He repeats this procedure until one task remains. It is this last task that he chooses to execute.

    Given a String[] list representing the tasks and an int n, return the task which the businessman chooses to execute.
  
  Constraints:
    List will contain between 2 and 50 elements inclusive.
    Each element in list will contain between 1 and 50 characters inclusive.
    Each element in list will contain only characters 'a'-'z'.
    n will be between 1 and 10000000 inclusive.
*/

#pragma once
#include <string>
#include <vector>

// Algorithm to be tested

std::string business_tasks(std::vector<std::string> const& tasks, unsigned n);

