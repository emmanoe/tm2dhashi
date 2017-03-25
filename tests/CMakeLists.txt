add_executable(test1 ./src/test_game2.c ./src/test_toolbox.c ../src/game.c ../src/node.c)


add_test(TestDelar test1)
