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

# Hint for compiler switch:
# - CLANG:
#   export CC=/usr/bin/clang
#   export CXX=/usr/bin/clang++
# - G++:
#   export CC=/usr/bin/gcc
#   export CXX=/usr/bin/g++

set(CUSTOM_DEFINES "")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CUSTOM_DEFINES "${CUSTOM_DEFINES} -Wno-error=cpp")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
    message(STATUS "g++ <5.1 does not support C++14 constexpr")
    set(CUSTOM_DEFINES "${CUSTOM_DEFINES} -DNO_SUPPORT_CONSTEXPR_CXX14")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CUSTOM_DEFINES "${CUSTOM_DEFINES} -Wno-error=#warnings")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4)
    message(FATAL_ERROR "clang <3.4 does not support C++14 constexpr")
    set(CUSTOM_DEFINES "${CUSTOM_DEFINES} -DNO_SUPPORT_CONSTEXPR_CXX14")
  endif()
endif()

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++1x" COMPILER_SUPPORTS_CXX1X)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
CHECK_CXX_COMPILER_FLAG("/std:c++14" COMPILER_SUPPORTS_CXX14_VS)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
CHECK_CXX_COMPILER_FLAG("/std:c++latest" COMPILER_SUPPORTS_CXX17_VS)
if (COMPILER_SUPPORTS_CXX14)
  set(CXX14 "-std=c++14")
elseif (COMPILER_SUPPORTS_CXX1Y)
  set(CXX14 "-std=c++1y")
elseif (COMPILER_SUPPORTS_CXX14_VS)
  set(CXX14 "/std:c++14")
endif()

set(CMAKE_CXX_FLAGS "${CUSTOM_DEFINES} ${CXX14} -Wall -Wextra -Werror -pthread -ftemplate-depth=10000")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

enable_testing()

include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(SYSTEM ${RAPIDCHECK_INCLUDE_DIRS})

file(GLOB_RECURSE CMAKEFILES **/CMakeLists.txt)
foreach(CMAKEFILE ${CMAKEFILES})
  if(NOT ${CMAKEFILE} MATCHES "^.*/rapidcheck/.*")
    get_filename_component(DIR_PATH ${CMAKEFILE} DIRECTORY)
    add_subdirectory(${DIR_PATH})
  endif()
endforeach()

