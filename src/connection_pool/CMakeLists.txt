# Header File Setting
set(HEADER_FILES
  ${INCLUDE_PATH_CONNECTION_POOL}/connection_factory.h
  ${INCLUDE_PATH_CONNECTION_POOL}/connection_map.h
  ${INCLUDE_PATH_CONNECTION_POOL}/connection_queue.h
  ${INCLUDE_PATH_CONNECTION_POOL}/database_connection.h
)

# Source File Setting
set (SOURCE_FILES
  connection_factory.cc
  connection_map.cc
  connection_queue.cc
  database_connection.cc
)

set(LIBRARY_NAME qqcp)
add_library(${LIBRARY_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDE_PATH_CONNECTION_POOL})
