cmake_minimum_required(VERSION 3.22)
project(dsa-dynamic-programming)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_SOURCE_DIR}/cmake/findlib.cmake)
FIND_LIB_GOOGLETEST()

add_gtest(LcsTest lcs/lcs_test.cpp)