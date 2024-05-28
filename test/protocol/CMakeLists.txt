# Source File Setting
set(SOURCE_FILES
  test_connection_pool.cc
  test_db_connection.cc
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/test/bin)
set(TEST_EXECUTABLE_NAME qqtest_proto)
add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE
  gtest_main
  qqproto
  ${Boost_LIBRARIES}
)
target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE
  ${Boost_INCLUDE_DIRS}
  ${INCLUDE_PATH_PROTOCOL}
)
