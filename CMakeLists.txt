cmake_minimum_required(VERSION 3.0.0)
project(qnlp)

# add_subdirectory(vendor/fastText)
add_subdirectory(externals/snowball)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(/usr/include)
include_directories(include)
include_directories(externals/snowball/include)
#include_directories(BEFORE vendor/fastText/src)

link_directories(/usr/lib
                 /usr/local/lib
                 build/vendor/fastText
                 externals/snowball/lib)

#find_package(OpenMP)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

set(SOURCES
  src/bpe.cc
  src/embeddings.cc
  src/en_tokenizer.cc
  src/fr_tokenizer.cc
  src/tokenizer.cc
  src/stemmer.cc
  src/stopwords.cc
  src/utils.cc
  src/stemmer.cc
  src/generalization.cc
)

set(LIBS
  fasttext
  snowball
)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(LIBS ${LIBS} ${Boost_LIBRARIES})
endif(Boost_FOUND)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

add_subdirectory(test)

install(TARGETS ${PROJECT_NAME} DESTINATION lib/)
install(DIRECTORY include/ DESTINATION include/qnlp FILES_MATCHING PATTERN "*.h*")
