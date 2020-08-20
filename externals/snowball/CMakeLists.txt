cmake_minimum_required(VERSION 3.0.0)
project(snowball)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
SET(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS " -std=c++11 -fPIC -O3 -Ofast -m64 -march=native -funroll-loops -ffinite-math-only -Wno-unused-result -Wno-deprecated -pthread -g -pg -fpermissive")
# set(CMAKE_CXX_FLAGS " -O2 -std=c++11 -lpthread -fpermissive ")

# MESSAGE( STATUS "CMAKE_CXX_FLAGS:         " ${CMAKE_CXX_FLAGS})
find_package(OpenMP)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# MESSAGE( STATUS "CMAKE_CXX_FLAGS:         " ${CMAKE_CXX_FLAGS})
# # set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

FILE(GLOB SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/libstemmer/libstemmer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/runtime/api.c
  ${CMAKE_CURRENT_SOURCE_DIR}/runtime/utilities.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src_c/*.c
)
  
add_library(snowball SHARED ${SOURCES})
ADD_LIBRARY(snowball-static STATIC ${SOURCES})

SET_TARGET_PROPERTIES(snowball-static PROPERTIES OUTPUT_NAME snowball)

install(TARGETS snowball snowball-static DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/libstemmer.h DESTINATION include)

# target_link_libraries(libstemmer fasttext )
# target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

# add_subdirectory(test)
# 
# install(
#   TARGETS snowball
#   ARCHIVE DESTINATION lib/
#   LIBRARY DESTINATION lib/
#   )
# install(
#   DIRECTORY include/  
#   DESTINATION include/snowball
#   FILES_MATCHING PATTERN "*.h*"
#   )
