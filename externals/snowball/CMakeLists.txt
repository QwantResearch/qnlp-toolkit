cmake_minimum_required(VERSION 3.0.0)
project(qnlp)

# set(CMAKE_CXX_STANDARD 11)

FILE(GLOB SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/libstemmer/libstemmer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/runtime/api.c
  ${CMAKE_CURRENT_SOURCE_DIR}/runtime/utilities.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src_c/*.c
)
  
add_library(snowball SHARED ${SOURCES})

# target_link_libraries(libstemmer fasttext )
# target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

# add_subdirectory(test)

install(
  TARGETS snowball
  ARCHIVE DESTINATION lib/
  LIBRARY DESTINATION lib/
  )
install(
  DIRECTORY include/  
  DESTINATION include/snowball
  FILES_MATCHING PATTERN "*.h*"
  )
