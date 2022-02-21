project(chip8bin)
add_executable(main main.c)
add_subdirectory(stack)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR}/.. lib/cfltk/include)
# for linux, might be needed in some setups like creating a library
target_include_directories(main PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${SOURCE_DIR}/stack"
                            )
