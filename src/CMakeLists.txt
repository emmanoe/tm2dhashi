add_executable(hashi_text game.c node.c hashi_text.c)

target_link_libraries(hashi_text m hashi)

install(TARGETS hashi_text RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})
