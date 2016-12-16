file(GLOB TEST_SRC_FILES *.cpp)

message(STATUS "Scanning: ${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(EXEC_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message(STATUS "Owner name: ${EXEC_NAME}")

foreach(SRC_NAME ${TEST_SRC_FILES})
  if(NOT ${SRC_NAME} MATCHES "main.cpp")
    message(STATUS "Found source: ${SRC_NAME}")
    get_filename_component(SRC_NAME_WE ${SRC_NAME} NAME_WE)
    set(TARGET_NAME "${EXEC_NAME}.${SRC_NAME_WE}")
    message(STATUS "Target name: ${TARGET_NAME}")
    add_executable(${TARGET_NAME} ${SRC_NAME} main.cpp)
    target_link_libraries(${TARGET_NAME} ${GTEST_BOTH_LIBRARIES} rapidcheck)
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
  endif()
endforeach()

