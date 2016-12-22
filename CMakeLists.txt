cmake_minimum_required(VERSION 2.8.8)


project(myProject C CXX)
find_package(GTest REQUIRED)
#set(CMAKE_VERBOSE_MAKEFILE ON)

message(STATUS "CMake version   : " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Compiler        : " ${CMAKE_CXX_COMPILER})
message(STATUS "Operating System: " ${CMAKE_SYSTEM})

set(RAPIDCHECK_PATH rapidcheck)
set(RAPIDCHECK_INCLUDE_DIRS ${RAPIDCHECK_PATH}/include ${RAPIDCHECK_PATH}/extras/gtest/include)
add_subdirectory(${RAPIDCHECK_PATH})

option(USE_CLANG "build binaries using clang" OFF)
option(USE_GCC "build binaries using g++" OFF)
if (USE_CLANG)
  set(CMAKE_C_COMPILER "clang" CACHE string "clang compiler" FORCE)
  set(CMAKE_CXX_COMPILER "clang++" CACHE string "clang++ compiler" FORCE)
elseif (USE_GCC)
  set(CMAKE_C_COMPILER "gcc" CACHE string "gcc compiler" FORCE)
  set(CMAKE_CXX_COMPILER "g++" CACHE string "g++ compiler" FORCE)
endif()

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++1x" COMPILER_SUPPORTS_CXX1X)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
if (COMPILER_SUPPORTS_CXX14)
  set(CXX14 "-std=c++14")
elseif (COMPILER_SUPPORTS_CXX1Y)
  set(CXX14 "-std=c++1y")
endif()
set(CMAKE_CXX_FLAGS "${CXX14} -Wall -pthread")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${RAPIDCHECK_INCLUDE_DIRS})

file(GLOB_RECURSE CMAKEFILES **/CMakeLists.txt)
foreach(CMAKEFILE ${CMAKEFILES})
  if(NOT ${CMAKEFILE} MATCHES "^.*/rapidcheck/.*")
    get_filename_component(DIR_PATH ${CMAKEFILE} DIRECTORY)
    add_subdirectory(${DIR_PATH})
  endif()
endforeach()

