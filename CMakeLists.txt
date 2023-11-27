cmake_minimum_required(VERSION 3.22)
project(dsa)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_SOURCE_DIR}/cmake/findlib.cmake)
FIND_LIB_GOOGLETEST()

add_subdirectory(dynamic_programming)

add_gtest(QueueTest queue_test.cpp)
add_gtest(StackTest stack_test.cpp)
add_gtest(ClosedAddressingHashMapTest closed_addressing_hash_map_test.cpp)
add_gtest(OpenAddressingHashMapTest open_addressing_hash_map_test.cpp)