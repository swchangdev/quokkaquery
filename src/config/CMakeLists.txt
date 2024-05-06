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

add_library(qqconf ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(qqconf PRIVATE ${INCLUDE_PATH_CONFIG})
target_link_libraries(qqconf PRIVATE nlohmann_json tomlplusplus_tomlplusplus)
target_link_libraries(qqconf PUBLIC tomlplusplus_tomlplusplus)
