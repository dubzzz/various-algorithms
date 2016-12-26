# Various Algorithms [![Build Status](https://travis-ci.org/dubzzz/various-algorithms.svg?branch=master)](https://travis-ci.org/dubzzz/various-algorithms)[![Build status](https://ci.appveyor.com/api/projects/status/3d7tvn2vgrkhpfrv?svg=true)](https://ci.appveyor.com/project/dubzzz/various-algorithms)


## Aim of this repository

The aim of this repository is to test and make use of the new possibilities offered by new releases of C++.
These capabilities are evaluated accross various classical implementations and algorithms.

It also wants to make use of:
- modern test frameworks (GTest, property-based testing using RapidCheck)
- continuous integration
- static analysis
- memory profiling
- leaks detection

## Minimum requirements

- CMake 2.8.8
- Compiler compatible with C++14 (partial support might be enough)
 - G++ 5.1 or later (tested using 4.9 with flags removing missing features)
 - Clang 3.4 or later
 - Visual Studio 14.0 2015 or later
