# Header File Setting
set(HEADER_FILES
  ${INCLUDE_PATH_CONTROL}/option_parser.h
)

# Source File Setting
set(SOURCE_FILES
  option_parser.cc
)

set(CONTROL_LIBRARY plctrl)
add_library(plctrl ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(plctrl PRIVATE ${INCLUDE_PATH_CONTROL})