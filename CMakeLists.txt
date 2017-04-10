cmake_minimum_required(VERSION 3.3)

project(hashi)

add_definitions(-std=c99 -Wall -g)

include_directories(include)

enable_testing()


add_subdirectory(tests)
add_subdirectory(include)
add_subdirectory(sdl2)
add_subdirectory(src)
add_subdirectory(solveur)
