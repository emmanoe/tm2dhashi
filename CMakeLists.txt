cmake_minimum_required(VERSION 3.3)

project(hashi)

add_definitions(-std=c99 -Wall)

include_directories(libhashi)

add_subdirectory(libhashi)
add_subdirectory(hashi)
