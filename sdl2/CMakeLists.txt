cmake_minimum_required(VERSION 2.6)

project ("hashi_sdl2" LANGUAGES C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
set (CMAKE_INSTALL_PREFIX .)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

include_directories(include)

include_directories(src)

add_executable(hashi_graph ./src/main.c ./src/hashi_graph.c ./src/game.c ./src/node.c ./src/load.c ./src/drawline.c ./src/manage_bridge.c)
target_link_libraries(hashi_graph
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_TTF_LIBRARY})


install(TARGETS hashi_graph RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})