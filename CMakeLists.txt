cmake_minimum_required(VERSION 3.22)
project(dsa)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        b796f7d44681514f58a683a3a71ff17c94edb0c1
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

enable_testing()

macro(add_gtest test_name test_file)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} gtest gmock gtest_main)
    add_test(${test_name} ${test_name})
    gtest_discover_tests(${test_name})
endmacro()

include(GoogleTest)

add_gtest(QueueTest queue_test.cpp)
add_gtest(StackTest stack_test.cpp)
add_gtest(ClosedAddressingHashMapTest closed_addressing_hash_map_test.cpp)
add_gtest(OpenAddressingHashMapTest open_addressing_hash_map_test.cpp)