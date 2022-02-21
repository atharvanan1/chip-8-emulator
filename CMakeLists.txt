cmake_minimum_required(VERSION 3.18)

project(Chip8Emu VERSION 0.1)

configure_file(Config.h.in Config.h)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Set directories
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_DIR ${ROOT_DIR}/src)
set(TEST_DIR ${ROOT_DIR}/tests)
set(FLTK_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
set(FLTK_BUILD_TEST OFF CACHE BOOL " " FORCE)

add_subdirectory(src)
add_subdirectory(lib/cfltk)
target_include_directories(main PRIVATE lib/cfltk/include)
target_link_libraries(main PRIVATE cfltk fltk fltk_images)
# for linux, might be needed in some setups like creating a library
target_link_libraries(main PRIVATE pthread X11 Xext Xinerama Xcursor Xrender Xfixes Xft fontconfig pango-1.0 pangoxft-1.0 gobject-2.0 cairo pangocairo-1.0)


option(BUILD_TEST "Build testing executables" ON)
if(BUILD_TEST)
    add_subdirectory(tests)
endif()
