cmake_minimum_required(VERSION 3.3)
project(Pstring)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp pstring.cpp pstring.h pmem.h pmem.cpp)
add_executable(Pstring ${SOURCE_FILES})