#include <SDL_ttf.h>    // required to use TTF fonts

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashi_graph.h"

#include "../include/game.h"
#include "../include/node.h"

/* **************************************************************** */

#define FONT "./sdl2/materials/Arial.ttf"
#define FONTSIZE 30

/* **************************************************************** */

void add_bridge(int nb_nodes, game g, int w, int h, int max_x, int max_y, int mouse_x, int mouse_y, int * bridge){

      for (int i = 0; i<nb_nodes; i++){

         if ((get_x(game_node(g,i))) * (double)(w/max_x) <= mouse_x)
            if( mouse_x <= get_x((game_node(g,i))) * (double)(w/max_x) + 22)
               if ( h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h <= mouse_y)
                  if (mouse_y <= h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h + 35){
                     bridge[i] = 1;
                     for (int x = 0; x <4; x++){
                        if (get_neighbour_dir(g,i,x) != -1)
                           if ( bridge[get_neighbour_dir(g,i,x)] == 1){
                              if (get_degree(g,get_neighbour_dir(g,i,x)) != get_required_degree(game_node(g,get_neighbour_dir(g,i,x))) && can_add_bridge_dir(g,i,x) ) {
                                 add_bridge_dir(g,i,x);
                              }
                              for (int cmpt = 0; cmpt < nb_nodes;cmpt ++)
                                 bridge[cmpt] = 0;}
                     }
                  }
      }
}

void delete_bridge(int nb_nodes, game g, int w, int h, int max_x, int max_y, int mouse_x, int mouse_y, int * bridge){
   for (int i = 0; i< nb_nodes; i++){

      if ((get_x(game_node(g,i))) * (double)(w/max_x) <= mouse_x)
         if (mouse_x <= get_x((game_node(g,i))) * (double)(w/max_x) + 22)
            if (h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h <= mouse_y)
               if (mouse_y <= h - (((1.0+(double)get_y(game_node(g,i)))/max_y))*h + 35) {
                  bridge[i] = 1;
                  for (int x = 0; x <4; x++){
                     if (get_neighbour_dir(g,i,x) != -1)
                        if (bridge[get_neighbour_dir(g,i,x)] == 1){
                           if (get_degree(g,get_neighbour_dir(g,i,x)) != 0 && get_degree(g,i) != 0 ) {
                              del_bridge_dir(g,i,x);
                           }
                           for (int cmpt = 0; cmpt < nb_nodes;cmpt ++)
                              bridge[cmpt] = 0;
                        }
                  }
               }
   }
}

void update_color(SDL_Renderer* ren, SDL_Event * e, game g, SDL_Texture ** texture_node, int nb_nodes){

   if (e->type == SDL_MOUSEBUTTONDOWN){
      if (e->button.button == SDL_BUTTON_LEFT){
         for (int i = 0; i< nb_nodes;i++){
            if (get_required_degree(game_node(g,i)) == get_degree(g,i)  ){

               SDL_Color color = { 186, 85, 211, 0 }; /* purple color in RGBA */
               TTF_Font * font2 = TTF_OpenFont(FONT, FONTSIZE); /* police de caractère */
               if(!font2)ERROR("TTF_OpenFont: %s\n", FONT);
               TTF_SetFontStyle(font2, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
               char  s[1];sprintf(s,"%d",get_required_degree(game_node(g,i)));
               SDL_Surface * surf = TTF_RenderText_Blended(font2, s, color); // blended rendering for ultra nice text
               texture_node[i] = SDL_CreateTextureFromSurface(ren, surf);
               SDL_FreeSurface(surf);TTF_CloseFont(font2);}}
      }
      else
         for (int i = 0; i< nb_nodes;i++){
            if (get_required_degree(game_node(g,i)) != get_degree(g,i)  ){

               SDL_Color color = { 255, 255, 255, 0 }; /* white color in RGBA */
               TTF_Font * font2 = TTF_OpenFont(FONT, FONTSIZE); /* police de caractère */
               if(!font2)ERROR("TTF_OpenFont: %s\n", FONT);
               TTF_SetFontStyle(font2, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
               char  s[1];sprintf(s,"%d",get_required_degree(game_node(g,i)));
               SDL_Surface * surf = TTF_RenderText_Blended(font2, s, color); // blended rendering for ultra nice text
               texture_node[i] = SDL_CreateTextureFromSurface(ren, surf);
               SDL_FreeSurface(surf);TTF_CloseFont(font2);}}
   }
}
