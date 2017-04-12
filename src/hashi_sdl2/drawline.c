#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashi_graph.h"

#include "../include/game.h"
#include "../include/node.h"

/* **************************************************************** */

void render_simple_line_h(SDL_Renderer* ren, game g, int i,int x, int w, int max_x,int max_y,int h){
   SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
   SDL_RenderDrawLine(ren, (x/2) +(get_x(game_node(g,i))) * (double)(w/max_x),h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h , (x/2) + (get_x(game_node(g,i+1))) * (double)(w/max_x), 35 + h - (((1.0+(double)get_y(game_node(g,i+1)))/max_y))*h);}

void render_double_line_h(SDL_Renderer* ren, game g, int i, int x, int y, int w, int max_x,int max_y,int h){
   SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
   SDL_RenderDrawLine(ren, (double)x/3 +(get_x(game_node(g,i))) * (double)(w/max_x),h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h , (double)x/3+ (get_x(game_node(g,i+1))) * (double)(w/max_x), 35 + h - (((1.0+(double)get_y(game_node(g,i+1)))/max_y))*h);

   SDL_RenderDrawLine(ren, (double)(2*x)/3 +(get_x(game_node(g,i))) * (double)(w/max_x),h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h , (double)(2*x)/3 + (get_x(game_node(g,i+1))) * (double)(w/max_x), y + h - (((1.0+(double)get_y(game_node(g,i+1)))/max_y))*h);}

void render_simple_line_v(SDL_Renderer* ren, game g, int i,int x, int y, int w, int max_x,int max_y,int h){
   SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
   SDL_RenderDrawLine(ren, (x) +(get_x(game_node(g,i))) * (double)(w/max_x),h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h + (y/2) ,0 + (get_x(game_node(g,get_neighbour_dir(g,i,3)))) * (double)(w/max_x), (y/2) + h - (((1.0+(double)get_y(game_node(g,get_neighbour_dir(g,i,3))))/max_y))*h);}

void render_double_line_v(SDL_Renderer* ren, game g, int i, int x, int y, int w, int max_x,int max_y,int h){
   SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
         SDL_RenderDrawLine(ren, (x) +(get_x(game_node(g,i))) * (double)(w/max_x),h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h + (double)(y/3) ,0 + (get_x(game_node(g,get_neighbour_dir(g,i,3)))) * (double)(w/max_x),  (double)(y/3) + h - (((1.0+(double)get_y(game_node(g,get_neighbour_dir(g,i,3))))/max_y))*h);

         SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
         SDL_RenderDrawLine(ren, (x) +(get_x(game_node(g,i))) * (double)(w/max_x),h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h + (double)(2*y/3) ,0 + (get_x(game_node(g,get_neighbour_dir(g,i,3)))) * (double)(w/max_x),  (double)(2*y/3) + h - (((1.0+(double)get_y(game_node(g,get_neighbour_dir(g,i,3))))/max_y))*h);}


/* **************************************************************** */
