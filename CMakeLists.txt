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

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=cpp")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
    message(STATUS "g++ <5.1 does not support C++14 constexpr")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_SUPPORT_CONSTEXPR_CXX14")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=#warnings")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4)
    message(FATAL_ERROR "clang <3.4 does not support C++14 constexpr")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_SUPPORT_CONSTEXPR_CXX14")
  endif()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pthread -ftemplate-depth=10000")
elseif (MSVC)
  set(CompilerFlags
      CMAKE_CXX_FLAGS
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_C_FLAGS
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_RELEASE)
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MT")
endif()

set(CMAKE_CXX_STANDARD 14)
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
