cmake_minimum_required(VERSION 3.22)
project(chip_8 C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(chip_8_run ${SOURCE_FILES})

include_directories(stack_lib)
add_subdirectory(stack_lib)

add_subdirectory(googletest)

target_link_libraries(chip_8_run stack_lib)
