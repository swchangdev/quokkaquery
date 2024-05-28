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
include_path(protocol)

add_subdirectory(config)
add_subdirectory(protocol)