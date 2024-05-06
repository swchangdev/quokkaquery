# Source File Setting
set(SOURCE_FILES
  test_config_dashboard.cc
  test_config_user_input.cc
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/test/bin)
set(TEST_EXECUTABLE_NAME pltest_config)
add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE
  gtest_main
  plconf
  ${Boost_LIBRARIES}
)
target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE
  ${INCLUDE_PATH_CONFIG}
  ${Boost_INCLUDE_DIRS}
)