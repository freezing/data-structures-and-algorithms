function(FIND_LIB_GOOGLETEST)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        b796f7d44681514f58a683a3a71ff17c94edb0c1
    )
    FetchContent_MakeAvailable(googletest)

    macro(add_gtest test_name test_file)
        add_executable(${test_name} ${test_file})
        target_link_libraries(${test_name} gtest gmock gtest_main)
        add_test(${test_name} ${test_name})
        gtest_discover_tests(${test_name})
    endmacro()

    enable_testing()
    include(GoogleTest)
endfunction()