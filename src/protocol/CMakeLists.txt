# Header File Setting
set(HEADER_FILES
  ${INCLUDE_PATH_PROTOCOL}/connection_pool.h
  ${INCLUDE_PATH_PROTOCOL}/connection.h
  ${INCLUDE_PATH_PROTOCOL}/server.h
)

# Source File Setting
set (SOURCE_FILES
  connection_pool.cc
  connection.cc
  server.cc
)

set(LIBRARY_NAME qqproto)
add_library(${LIBRARY_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDE_PATH_PROTOCOL})
