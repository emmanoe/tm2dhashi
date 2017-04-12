add_executable(test1 ${CMAKE_SOURCE_DIR}/src/test/test_game2.c ${CMAKE_SOURCE_DIR}/src/test/test_toolbox.c ${CMAKE_SOURCE_DIR}/src/game.c ${CMAKE_SOURCE_DIR}/src/node.c)


add_test(TestDelar test1)
