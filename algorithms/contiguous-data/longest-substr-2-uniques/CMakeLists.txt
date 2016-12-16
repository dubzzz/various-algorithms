file(GLOB TEST_SRC_FILES *.cpp)

set(EXEC_NAME longest-substr-2-uniques)
add_executable(${EXEC_NAME} ${TEST_SRC_FILES})
target_link_libraries(${EXEC_NAME} ${GTEST_BOTH_LIBRARIES} rapidcheck)
add_test(NAME ${EXEC_NAME} COMMAND ${EXEC_NAME})

