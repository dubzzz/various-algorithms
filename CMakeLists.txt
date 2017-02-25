cmake_minimum_required(VERSION 2.8.8)
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(various-algorithms C CXX)
find_package(GTest REQUIRED)
#set(CMAKE_VERBOSE_MAKEFILE ON)

message(STATUS "CMake version   : " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Compiler        : " ${CMAKE_CXX_COMPILER})
message(STATUS "Operating System: " ${CMAKE_SYSTEM})

option (ENABLE_EXTENDED "Enable extended tests" OFF)

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

if (ENABLE_EXTENDED)
  if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DENABLE_EXTENDED")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_EXTENDED")
  endif()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=cpp -Wno-error=unknown-pragmas")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
    message(STATUS "g++ <5.1 does not support C++14 constexpr")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_SUPPORT_CONSTEXPR_CXX14")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=#warnings")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4)
    message(STATUS "clang <3.4 does not support C++14 constexpr")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_SUPPORT_CONSTEXPR_CXX14")
  endif()
elseif (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /wd4503 /D _CRT_SECURE_NO_WARNINGS /D _SCL_SECURE_NO_WARNINGS")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 20)
    message(STATUS "visual studio <15 does not support C++14 constexpr")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D NO_SUPPORT_CONSTEXPR_CXX14")
  endif()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pthread -ftemplate-depth=10000")
endif()

if(CMAKE_VERSION VERSION_EQUAL 3.1 OR CMAKE_VERSION VERSION_GREATER 3.1)
  set(CMAKE_CXX_STANDARD 14)
else()
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
  CHECK_CXX_COMPILER_FLAG("-std=c++1x" COMPILER_SUPPORTS_CXX1X)
  CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
  CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
  CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
  CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
  if (COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  elseif (COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
  endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

enable_testing()

include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(SYSTEM ${RAPIDCHECK_INCLUDE_DIRS})

# Helper functions used by sub-CMakeLists.txt

function(escape_name OUTPUT INPUT)
  string(REPLACE "-" "" LOCALVAR ${INPUT})
  string(REPLACE "." "" LOCALVAR ${LOCALVAR})
  string(REPLACE "_" "" LOCALVAR ${LOCALVAR})
  set(${OUTPUT} ${LOCALVAR} PARENT_SCOPE)
endfunction()

function(build_exec_prefix OUTPUT_PREFIX OUTPUT_DIR EXEC_SRC_FILE)
  get_filename_component(EXEC_SRC_FILE_WE ${EXEC_SRC_FILE} NAME_WE)
  if (EXEC_SRC_FILE_WE STREQUAL "main")
    set(EXEC_PREFIX "")
    set(EXEC_OUTPUTDIR "test")
  else()
    string(REPLACE "main_" "" EXEC_PREFIX ${EXEC_SRC_FILE_WE})
    escape_name(EXEC_PREFIX ${EXEC_PREFIX})
    set(EXEC_OUTPUTDIR ${EXEC_PREFIX})
    set(EXEC_PREFIX ${EXEC_PREFIX}.)
  endif()
  set(${OUTPUT_PREFIX} ${EXEC_PREFIX} PARENT_SCOPE)
  set(${OUTPUT_DIR} ${EXEC_OUTPUTDIR} PARENT_SCOPE)
endfunction()

function(build_exec_name OUTPUT_TARGETNAME OUTPUT_TESTNAME EXEC_NAME PREFIX SRC_NAME)
  escape_name(TEST_NAME_START "${EXEC_NAME}")
  get_filename_component(SRC_NAME_WE ${SRC_NAME} NAME_WE)
	if (SRC_NAME_WE STREQUAL "implem")
		set(TARGET_NAME "${PREFIX}${EXEC_NAME}")
		set(CODE_TEST_NAME ${TEST_NAME_START})
	else()
		string(REPLACE "implem_" "" SRC_SUFFIX ${SRC_NAME_WE})
		escape_name(SRC_SUFFIX ${SRC_SUFFIX})
		set(TARGET_NAME "${PREFIX}${EXEC_NAME}.${SRC_SUFFIX}")
		set(CODE_TEST_NAME ${TEST_NAME_START}_${SRC_SUFFIX})
	endif()
  set(${OUTPUT_TARGETNAME} ${TARGET_NAME} PARENT_SCOPE)
  set(${OUTPUT_TESTNAME} ${CODE_TEST_NAME} PARENT_SCOPE)
endfunction()

function(generate_exec_new EXEC_NAME EXEC_SRC_FILE IMPLEM_SRC_FILE)

  # Generate project and test name
  
  build_exec_prefix(EXEC_PREFIX EXEC_OUTPUTDIR "${EXEC_SRC_FILE}")
  build_exec_name(TARGET_NAME CODE_TEST_NAME "${EXEC_NAME}" "${EXEC_PREFIX}" "${IMPLEM_SRC_FILE}")
  message(STATUS "-- Target name: ${TARGET_NAME} (for test: ${CODE_TEST_NAME})")
  
  # Add files into the project
  
  get_filename_component(IMPLEM_EXT ${IMPLEM_SRC_FILE} EXT)
  if (IMPLEM_EXT STREQUAL ".hpp")
    add_executable(${TARGET_NAME} ${IMPLEM_SRC_FILE} ${EXEC_SRC_FILE})
    get_filename_component(SPECIFIC_HEADER ${IMPLEM_SRC_FILE} NAME)
  else()
    add_executable(${TARGET_NAME} ${IMPLEM_SRC_FILE} ${EXEC_SRC_FILE} aim.hpp)
    set(SPECIFIC_HEADER "aim.hpp")
  endif()
  
  # Customize project's properties
  
  set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXEC_OUTPUTDIR})
  if (MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /DTEST_NAME=${CODE_TEST_NAME} /DSPECIFIC_HEADER="${SPECIFIC_HEADER}")
  else()
    target_compile_options(${TARGET_NAME} PRIVATE -DTEST_NAME=${CODE_TEST_NAME} -DSPECIFIC_HEADER="${SPECIFIC_HEADER}")
  endif()
  if (EXEC_OUTPUTDIR STREQUAL "test")
    target_link_libraries(${TARGET_NAME} ${GTEST_BOTH_LIBRARIES} rapidcheck)
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
  endif()

endfunction()

function(generate_compile_only EXEC_NAME EXEC_SRC_FILE)

  # Generate project and test name
  
  build_exec_prefix(EXEC_PREFIX EXEC_OUTPUTDIR "${EXEC_SRC_FILE}")
  build_exec_name(TARGET_NAME CODE_TEST_NAME "${EXEC_NAME}" "${EXEC_PREFIX}" "implem.cpp")
  set(TARGET_NAME "${TARGET_NAME}.compileonly")
  set(CODE_TEST_NAME "${CODE_TEST_NAME}_compileonly")
  message(STATUS "-- Compile-only name: ${TARGET_NAME} (for test: ${CODE_TEST_NAME})")
  
  # Add files into the project
  
  add_library(${TARGET_NAME} OBJECT ${EXEC_SRC_FILE} aim.hpp)
  set(SPECIFIC_HEADER "aim.hpp")
  
  # Customize project's properties
  
  if (MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /DTEST_NAME=${CODE_TEST_NAME} /DSPECIFIC_HEADER="${SPECIFIC_HEADER}")
  else()
    target_compile_options(${TARGET_NAME} PRIVATE -DTEST_NAME=${CODE_TEST_NAME} -DSPECIFIC_HEADER="${SPECIFIC_HEADER}")
  endif()

endfunction()

function(generate_all_execs_new)
  file(GLOB IMPLEM_SRC_FILES implem*.cpp)
  file(GLOB IMPLEM_HDR_FILES implem*.hpp)
  file(GLOB EXEC_SRC_FILES main.cpp main_*.cpp)
  
  message(STATUS "Scanning: ${CMAKE_CURRENT_SOURCE_DIR}")
  get_filename_component(EXEC_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
  #message(STATUS "Owner name: ${EXEC_NAME}")

  foreach(EXEC_SRC_FILE ${EXEC_SRC_FILES})
    generate_compile_only("${EXEC_NAME}" "${EXEC_SRC_FILE}")
    foreach(IMPLEM_SRC_FILE ${IMPLEM_SRC_FILES})
      generate_exec_new("${EXEC_NAME}" "${EXEC_SRC_FILE}" "${IMPLEM_SRC_FILE}")
    endforeach()
    foreach(IMPLEM_SRC_FILE ${IMPLEM_HDR_FILES})
      generate_exec_new("${EXEC_NAME}" "${EXEC_SRC_FILE}" "${IMPLEM_SRC_FILE}")
    endforeach()
  endforeach()
endfunction()

# Declaration of sub-CMakeLists.txt

file(GLOB_RECURSE CMAKEFILES **/CMakeLists.txt)
foreach(CMAKEFILE ${CMAKEFILES})
  if(NOT ${CMAKEFILE} MATCHES "^.*/rapidcheck/.*")
    get_filename_component(DIR_PATH ${CMAKEFILE} DIRECTORY)
    add_subdirectory(${DIR_PATH})
  endif()
endforeach()
