# Source File Setting
set(SOURCE_FILES
  test_option_parser.cc
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/test/bin)
set(TEST_EXECUTABLE_NAME pltest_control)
add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE
  gtest_main
  plctrl
  ${Boost_LIBRARIES}
)

target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE
  ${INCLUDE_PATH_CONTROL}
  ${INCLUDE_PATH_EXTERNAL}
  ${Boost_INCLUDE_DIRS}
)