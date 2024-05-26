# Declare Include Directory Variables
# Each directory path in include folder can be accessed as INCLUDE_PATH_{DIR_NAME}
# For instance, "common" directory path is accessed as INCLUDE_PATH_COMMON variable
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
function(include_path suffix)
  string(TOUPPER ${suffix} suffix_upper)
  set(var_name INCLUDE_PATH_${suffix_upper})
  set(${var_name} ${INCLUDE_PATH}/${suffix} PARENT_SCOPE)
endfunction()

include_path(config)
include_path(connection_pool)

# Executable Linking
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
set(EXECUTABLE_NAME quokkaquery) 
add_executable(${EXECUTABLE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)
target_link_directories(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  ${Boost_LIBRARIES}
  tomlplusplus_tomlplusplus
  nlohmann_json
  qqconf
  qqcp
)
target_include_directories(${EXECUTABLE_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(config)
add_subdirectory(connection_pool)