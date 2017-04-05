// Hashi SDL2 by emmanoe.delar@etu.u-bordeaux.fr

#ifndef DRAWLINE_H
#define DRAWLINE_H

#include <SDL.h>
#include <stdio.h>
#include "../include/game.h"

/* **************************************************************** */

void render_simple_line_h(SDL_Renderer* ren, game g, int i, int x, int w, int max_x, int max_y, int h);

void render_double_line_h(SDL_Renderer* ren, game g, int i, int x, int y, int w, int max_x,int max_y,int h);

void render_simple_line_v(SDL_Renderer* ren, game g, int i,int x, int y, int w, int max_x,int max_y,int h);

void render_double_line_v(SDL_Renderer* ren, game g, int i, int x, int y, int w, int max_x,int max_y,int h);

/* **************************************************************** */

#endif
