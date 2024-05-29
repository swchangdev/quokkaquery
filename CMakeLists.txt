# CMake Minimum
cmake_minimum_required(VERSION 3.5.0)

# Set Project
set(PROJECT_NAME "quokkaquery")
PROJECT(${PROJECT_NAME})

# CMake Flags
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)

# Boost
find_package(Boost REQUIRED COMPONENTS
  # Boost Components
)

# External Libraries
include(FetchContent)
# Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
)
# TOML++
FetchContent_Declare(
  tomlplusplus
  GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
  GIT_TAG v3.4.0
)
# JSON Parser
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(tomlplusplus googletest json)

# Config file generation
execute_process(
  COMMAND python3 ${PROJECT_SOURCE_DIR}/script/gen_config.py 
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# Add Source Subdirectory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
