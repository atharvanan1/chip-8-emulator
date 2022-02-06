add_executable(Dummy main.c)
add_subdirectory(bool_lib)

target_link_libraries(Dummy PUBLIC bool_lib)

target_include_directories(Dummy PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/bool-test"
                            )
