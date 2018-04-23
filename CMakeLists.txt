cmake_minimum_required(VERSION 3.0.0)
project(qnlp)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
SET(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS " -std=c++11 -fPIC -O3 -Ofast -m64 -march=native -funroll-loops -ffinite-math-only -Wno-unused-result -Wno-deprecated -pthread -g -pg")

MESSAGE( STATUS "CMAKE_CXX_FLAGS:         " ${CMAKE_CXX_FLAGS})
find_package(OpenMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
MESSAGE( STATUS "CMAKE_CXX_FLAGS:         " ${CMAKE_CXX_FLAGS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)



# option(BUILD_SHARED_LIBS "Build shared libraries" ON)
# SET(CMAKE_VERBOSE_MAKEFILE ON)

# set(CMAKE_CXX_FLAGS " -std=c++11 -fPIC -O3 -Ofast -m64 -march=native -funroll-loops -ffinite-math-only -Wno-unused-result -Wno-deprecated -pthread -g -pg")

# set(CMAKE_CXX_STANDARD 11)

find_package(Boost)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(EXT_LIBS ${Boost_LIBRARIES})
else(Boost_FOUND)
    message(SEND_ERROR "Cannot find Boost libraries. Terminating." )
endif(Boost_FOUND)

# Set Release build type by default to get sane performance.
# if(NOT CMAKE_BUILD_TYPE)
#   set(CMAKE_BUILD_TYPE Release)
# endif(NOT CMAKE_BUILD_TYPE)

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# set(INCLUDE_DIRECTORIES
#   ${CMAKE_CURRENT_SOURCE_DIR}/include
#   )

set(SOURCES
  src/bpe.cc  
  src/embeddings.cc  
  src/en_tokenizer.cc  
  src/fr_tokenizer.cc  
  src/tokenizer.cc  
  src/utils.cc
  )
  
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} fasttext )
# target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

add_subdirectory(test)

install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib/
  LIBRARY DESTINATION lib/
  )
install(
  DIRECTORY include/
  DESTINATION include/qnlp
  FILES_MATCHING PATTERN "*.h*"
  )
