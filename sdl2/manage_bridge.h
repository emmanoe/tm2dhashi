// Hashi SDL2 by emmanoe.delar@etu.u-bordeaux.fr

#ifndef MANAGE_BRIDGE_H
#define MANAGE_BRIDGE_H

#include <SDL.h>
#include <stdio.h>
#include "../include/game.h"

/* **************************************************************** */

void add_bridge(int nb_nodes, game g, int w, int h, int max_x, int max_y, int mouse_x, int mouse_y, int * bridge);
void delete_bridge(int nb_nodes, game g, int w, int h, int max_x, int max_y, int mouse_x, int mouse_y, int * bridge);
void update_color(SDL_Renderer* ren, SDL_Event * e, game g, SDL_Texture ** texture_node, int nb_nodes);

/* **************************************************************** */

#endif
