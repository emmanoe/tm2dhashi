add_library(hashi
        ../src/game.c ../src/node.c)

add_executable(hashi_text game.c node.c ./hashi_text/hashi_text.c)

add_executable(hashi_sdl2 hashi_sdl2/hashi_sdl2 hashi_sdl2/drawline.c hashi_sdl2/load.c hashi_sdl2/main.c hashi_sdl2/manage_bridge.c ${CMAKE_SOURCE_DIR}/src/game.c ${CMAKE_SOURCE_DIR}/src/node.c)
target_link_libraries(hashi_sdl2
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_TTF_LIBRARY})

target_link_libraries(hashi_text m hashi)

install(TARGETS hashi_text RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})

install(TARGETS hashi_sdl2 RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})