# Header File Setting
set(HEADER_FILES
  ${INCLUDE_PATH_CONNECTION}/connection_factory.h
  ${INCLUDE_PATH_CONNECTION}/map.h
  ${INCLUDE_PATH_CONNECTION}/pool.h
)

# Source File Setting
set (SOURCE_FILES
  connection_factory.cc
  map.cc
  pool.cc
)

set(LIBRARY_NAME qqconn)
add_library(${LIBRARY_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDE_PATH_CONNECTION})
