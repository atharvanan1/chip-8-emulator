cmake_minimum_required(VERSION 3.18)

project(Chip8Emu VERSION 0.1)

configure_file(Config.h.in Config.h)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_DIR ${ROOT_DIR}/src)
set(TEST_DIR ${ROOT_DIR}/tests)

add_subdirectory(src)

option(BUILD_TEST "Build testing executables" ON)
if(BUILD_TEST)
    add_subdirectory(tests)
endif()
