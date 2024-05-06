# CMake Minimum
cmake_minimum_required(VERSION 3.5.0)

# Set Project
set(PROJECT_NAME "quokkaquery")
file(READ "VERSION.txt" PROJECT_VERSION)
PROJECT(${PROJECT_NAME} VERSION ${PROJECT_VERSION})
add_compile_definitions("CURRENT_VERSION=\"${PROJECT_VERSION}\"")

# CMake Flags
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)

# Boost
find_package(Boost REQUIRED COMPONENTS
  # Boost Components
  program_options
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

# Declare Include Directory Variables
# Each directory path in include folder can be accessed as INCLUDE_PATH_{DIR_NAME}
# For instance, "common" directory path is accessed as INCLUDE_PATH_COMMON variable
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
function(include_path suffix)
  string(TOUPPER ${suffix} suffix_upper)
  set(var_name INCLUDE_PATH_${suffix_upper})
  set(${var_name} ${INCLUDE_PATH}/${suffix} PARENT_SCOPE)
endfunction()

include_path(common)
include_path(config)
include_path(control)

# Config file generation
execute_process(
  COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/script/gen_config.py 
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Executable Linking
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/lib)
set(EXECUTABLE_NAME quokkaquery) 
add_executable(${EXECUTABLE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
target_link_directories(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  ${Boost_LIBRARIES}
  tomlplusplus_tomlplusplus
  nlohmann_json
  qqctrl
  qqconf
)
target_include_directories(${EXECUTABLE_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIRS}
)

# Add Source Subdirectory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
