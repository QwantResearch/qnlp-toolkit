cmake_minimum_required(VERSION 2.6)

PROJECT(qnlp-toolkit)
SET(USERHOME "$ENV{HOME}")
#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_CXX_FLAGS " -Wno-deprecated -Wunused-local-typedefs -Wsign-compare " CACHE STRING "Flags used by the C++ compiler" FORCE )
#add_definitions(-DCMAKE_INSTALL_PREFIX=YOUR INSTALL DIR HERE!!!)
add_definitions(-DIBPP_LINUX -DIBPP_GCC)
# include_directories(YOUR INCLUDE DIR HERE!!!)
# link_directories(YOUR LIB DIR HERE!!!)
#include_directories(/usr/local/include)
#link_directories(/usr/local/lib)
include_directories(./include)
ADD_DEFINITIONS(-Wall -O2 -static -std=c++0x -Wunused-local-typedefs )

#list all source files here
add_subdirectory(test)
# add_subdirectory(src)



