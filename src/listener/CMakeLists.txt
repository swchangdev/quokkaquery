# Header File Setting
set(HEADER_FILE_PATH ${PROJECT_SOURCE_DIR}/include)
set(HEADER_FILES
  ${HEADER_FILE_PATH}/common/config.h
  ${HEADER_FILE_PATH}/listener/server.h
)

# Source File Setting
set(SOURCE_FILES
  server.cc
)

set(CONTROL_LIBRARY pllsnr)
add_library(pllsnr ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(pllsnr PRIVATE ${HEADER_FILE_PATH})