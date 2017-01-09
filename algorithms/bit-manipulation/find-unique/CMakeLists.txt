file(GLOB TEST_SRC_FILES implem*.cpp)
file(GLOB MEASURE_SRC_FILES main.cpp main_*.cpp)

message(STATUS "Scanning: ${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(EXEC_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
#message(STATUS "Owner name: ${EXEC_NAME}")

foreach(MEASURE_NAME ${MEASURE_SRC_FILES})
  foreach(SRC_NAME ${TEST_SRC_FILES})
    build_exec("${EXEC_NAME}" "${MEASURE_NAME}" "${SRC_NAME}")
  endforeach()
endforeach()

