cmake_minimum_required(VERSION 3.0.0)
project(qnlp)

set(CMAKE_BUILD_TYPE Release)
SET(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -fPIC -O3 -march=native -funroll-loops -ffinite-math-only -pthread")

find_package(Boost
             OpenMP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

include_directories(${CMAKE_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/vendor)

link_directories(${CMAKE_SOURCE_DIR}/vendor/snowball
                 ${CMAKE_SOURCE_DIR}/vendor/fasttext
                 ${CMAKE_SOURCE_DIR}/vendor/utfcpp
                 /usr/local/lib)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(EXT_LIBS ${Boost_LIBRARIES})
else(Boost_FOUND)
    message(SEND_ERROR "Cannot find Boost libraries. Terminating." )
endif(Boost_FOUND)

set(SOURCES
  ${CMAKE_SOURCE_DIR}/src/bpe.cc
  ${CMAKE_SOURCE_DIR}/src/embeddings.cc
  ${CMAKE_SOURCE_DIR}/src/en_tokenizer.cc
  ${CMAKE_SOURCE_DIR}/src/fr_tokenizer.cc
  ${CMAKE_SOURCE_DIR}/src/tokenizer.cc
  ${CMAKE_SOURCE_DIR}/src/stemmer.cc
  ${CMAKE_SOURCE_DIR}/src/stopwords.cc
  ${CMAKE_SOURCE_DIR}/src/utils.cc
  ${CMAKE_SOURCE_DIR}/src/stemmer.cc
  ${CMAKE_SOURCE_DIR}/src/generalization.cc
  )

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} fasttext snowball utfcpp)

add_subdirectory(test)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib/
        LIBRARY DESTINATION lib/)

install(IRECTORY include/
        DESTINATION include/qnlp
        FILES_MATCHING PATTERN "*.h*")
