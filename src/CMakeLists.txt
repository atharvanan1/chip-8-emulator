add_executable(${CMAKE_PROJECT_NAME} main.c)
add_subdirectory(stack)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC stack)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${SOURCE_DIR}/stack"
                            )
