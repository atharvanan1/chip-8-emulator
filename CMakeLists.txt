cmake_minimum_required(VERSION 3.18)

project(Dummy VERSION 0.1)
add_subdirectory(src)

configure_file(Config.h.in Config.h)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

option(BUILD_TEST "Build testing executables" ON)
if(BUILD_TEST)
    # Testing framework
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(
        bool_test
        tests/test_bool_test.cpp
    )

    target_include_directories(
        bool_test PUBLIC
        "${PROJECT_SOURCE_DIR}/src/bool_lib"
    )

    target_link_libraries(
        bool_test
        gtest_main
        bool_lib
    )

    include(GoogleTest)
    gtest_discover_tests(bool_test)
endif()