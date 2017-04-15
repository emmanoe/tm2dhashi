cmake_minimum_required(VERSION 3.3)

project(hashi_solve)

set (CMAKE_INSTALL_PREFIX .)

option(ENABLE_DEBUG "debug options" ON)
if(ENABLE_DEBUG)
	set(CMAKE_C_FLAGS "-std=c99 -g -fprofile-arcs -ftest-coverage -Wall")
	set(CMAKE_LD_FLAGS "-fprofile-arcs -ftest-coverage")
	INCLUDE(Dart)
else()
	set(CMAKE_C_FLAGS "-std=c99 -O3 -Wall")
endif()


include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/src/solveur)
include_directories(${CMAKE_SOURCE_DIR}/src)


add_executable(hashi_solve 
	${CMAKE_SOURCE_DIR}/src/solveur/hashi_solve.c ${CMAKE_SOURCE_DIR}/src/game.c ${CMAKE_SOURCE_DIR}/src/node.c ${CMAKE_SOURCE_DIR}/src/solveur/main.c)

target_link_libraries(hashi_solve m hashi)

install(TARGETS hashi_solve RUNTIME DESTINATION ${hashi_solve_SOURCE_DIR})
