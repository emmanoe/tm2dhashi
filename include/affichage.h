#ifndef DRAWLINE_H
#define DRAWLINE_H

#include <SDL.h>
#include <stdio.h>
#include "../include/game.h"

/* **************************************************************** */

void draw_bridge(game g, int node_num, char **t, node a, dir d);

char ** draw_map(char ** t, int maxx, int maxy, game g);

/* **************************************************************** */

#endif