file(GLOB TEST_SRC_FILES *.cpp)

message(STATUS "Scanning: ${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(EXEC_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message(STATUS "Target name: ${EXEC_NAME}")

add_executable(${EXEC_NAME} ${TEST_SRC_FILES})
target_link_libraries(${EXEC_NAME} ${GTEST_BOTH_LIBRARIES} rapidcheck)
add_test(NAME ${EXEC_NAME} COMMAND ${EXEC_NAME})

