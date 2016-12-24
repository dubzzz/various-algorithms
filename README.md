# Various Algorithms

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
 - G++ 5.1 or more (tested using 4.9 with flags removing missing features)
 - Clang 3.4 or more