project(googletest)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(googletest_run test_stack.cpp)

target_link_libraries(googletest_run stack_lib)

target_link_libraries(googletest_run gtest gtest_main)
