// Hashi SDL2 by emmanoe.delar@etu.u-bordeaux.fr

#ifndef LOAD_H
#define LOAD_H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/game.h"

/* **************************************************************** */

game load_default_game (const char* path);

void init_taille_tab(game g,int* pt_x, int* pt_y, int nb_nodes);

/* **************************************************************** */

#endif
