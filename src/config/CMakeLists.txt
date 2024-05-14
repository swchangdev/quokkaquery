# Header File Setting
set(HEADER_FILES
  ${INCLUDE_PATH_CONFIG}/dashboard.h
  ${INCLUDE_PATH_CONFIG}/parameter.h
  ${INCLUDE_PATH_CONFIG}/parameter_desc.h
  ${INCLUDE_PATH_CONFIG}/user_input.h
)

# Source File Setting
set (SOURCE_FILES
  dashboard.cc
  dashboard_autogen.cc
  parameter.cc
  user_input.cc
)

set(LIBRARY_NAME qqconf)
add_library(${LIBRARY_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDE_PATH_CONFIG})
target_link_libraries(${LIBRARY_NAME} PRIVATE nlohmann_json)
target_link_libraries(${LIBRARY_NAME} PUBLIC tomlplusplus_tomlplusplus)
