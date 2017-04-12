cmake_minimum_required(VERSION 3.3)

project("hashi" LANGUAGES C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
set (CMAKE_INSTALL_PREFIX .)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/sdl2/CMakeModules)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

include_directories(include)

enable_testing()

add_subdirectory(src)
add_subdirectory(solveur)
add_subdirectory(tests)