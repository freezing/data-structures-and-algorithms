cmake_minimum_required(VERSION 3.22)
project(dsa-dynamic-programming)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_SOURCE_DIR}/cmake/findlib.cmake)
FIND_LIB_GOOGLETEST()

add_gtest(LcsTest lcs/lcs_test.cpp)
add_gtest(TextDiffTest lcs/text_diff_test.cpp)

add_executable(text_diff lcs/text_diff.cpp)
add_executable(print_dp_matrix lcs/print_dp_matrix.cpp)