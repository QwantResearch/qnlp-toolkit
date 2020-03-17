cmake_minimum_required(VERSION 3.0.0)
project(qnlp)

add_subdirectory(externals/snowball)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_CXX_FLAGS " -O3 ")
set(CMAKE_C_FLAGS " -O3 ")

include_directories(/usr/include)
include_directories(include)
include_directories(externals/snowball/include)

link_directories(/usr/lib
                 /usr/local/lib
                 build/vendor/fastText
                 externals/snowball/lib)

set(SOURCES
  src/bpe.cpp
  src/embeddings.cpp
  src/en_tokenizer.cpp
  src/fr_tokenizer.cpp
  src/car_tokenizer.cpp
  src/tokenizer.cpp
  src/stemmer.cpp
  src/stopwords.cpp
  src/utils.cpp
  src/stemmer.cpp
  src/generalization.cpp
  src/spm.cpp
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
install(DIRECTORY include/ DESTINATION include/ FILES_MATCHING PATTERN "*.h*")
