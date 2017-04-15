#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"
#include "../include/node.h"
#include "../include/hashi_solve.h"

int main(int argc, char *argv[]){

   game g = load_default_game_solveur(argv[1]);

   printf("game_required_degree noeud 0 = %d\n",get_required_degree(game_node(g,0)));

   game solved = solveur(g);

   delete_game(g);

   save_game(solved, argv[1]);

   return EXIT_SUCCESS;
}