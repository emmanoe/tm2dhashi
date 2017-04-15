#ifndef HASHI_SOLVE_H
#define HASHI_SOLVE_H

#include <SDL.h>
#include <stdio.h>
#include "../include/game.h"
#include "../include/node.h"


/* **************************************************************** */

bool good_conf (game g_src, int num_node,int i, int j, int k, int l);

game load_default_game_solveur (const char* path);

game solveur_recursif(game g, int num_node);

bool isolate(game g_src, int num_node);

void save_game(game g, char * path);

game solveur(game g);

/* **************************************************************** */

#endif