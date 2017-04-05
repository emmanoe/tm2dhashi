// hashi_SDL2 by emmanoe.delar@etu.u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "model.h"
#include "load.h"
#include "drawline.h"
#include "manage_bridge.h"

#include "../include/game.h"
#include "../include/node.h"


/* **************************************************************** */

#define FONT "Arial.ttf"
#define FONTSIZE 30
#define BACKGROUND "green.png"



/* **************************************************************** */


struct Env_t {

   SDL_Texture * background; // Arrière plan
   SDL_Texture ** texture_node; // iles du jeux
   int * bridge;
   int max_x, max_y;
   game g;
};

/* **************************************************************** */


Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{

   PRINT("Cliques gauche : ajout de ponts.\n");
   PRINT("Cliques droit : suppression de ponts.\n");
   PRINT("Press ESC to quit. Enjoy my Hashi SDL2 sample !\n");

   /* Initialisation de l'environnement */

   Env * env = malloc(sizeof(struct Env_t));
   game g = load_default_game(argv[1]);
   int i = game_nb_nodes(g);env->g = g;

   /* intialisation des champs de la structure */
   env->texture_node =  malloc( i * sizeof(SDL_Texture *));
   if(env->texture_node==NULL)exit(EXIT_FAILURE);
   env->bridge = calloc( i, sizeof(int));
   if(env->bridge==NULL)exit(EXIT_FAILURE);
   init_taille_tab(env->g,&env->max_x,&env->max_y,game_nb_nodes(env->g)); 

   /* initialisation du fond d'écran texture de type PNG image */
   env->background = IMG_LoadTexture(ren, BACKGROUND);
   if(!env->background)ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  /* initialisation du node texture utilisant la police Arial font */
  SDL_Color color = { 255, 255, 255, 255 }; /* white color in RGBA */
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE); /* police de caractère */
  if(!font)ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); /* TTF_STYLE_ITALIC | TTF_STYLE_NORMAL*/
  char  s[1]; /* s necéssaire pour convertir le noeuds (int) en  text (* char) pour TTF_RenderText */

  for (int i =0; i< game_nb_nodes(g); i++){ /*Chaque noeud est stocké dans un tableau*/
     sprintf(s,"%d",get_required_degree(game_node(env->g,i)));
     SDL_Surface * surf = TTF_RenderText_Blended(font, s, color); /* Creation rendu pour chaque noeud */
     env->texture_node[i] = SDL_CreateTextureFromSurface(ren, surf);
     SDL_FreeSurface(surf);}

  TTF_CloseFont(font);
  return env;
}

/* **************************************************************** */

void render(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
   int w, h;
   int x, y;
   SDL_GetWindowSize(win, &w, &h);


   /* render background texture */
   SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

   /* render node texture */
   for (int i= 0; i< game_nb_nodes(env->g); i++){
      SDL_Rect rect;
      SDL_QueryTexture(env->texture_node[i], NULL, NULL, &rect.w , &rect.h );
      rect.x =  (get_x(game_node(env->g,i))) * (double)(w/env->max_x)  ;
      rect.y =  h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h ; // formule pour inverser l'affichage
      SDL_RenderCopy(ren, env->texture_node[i], NULL, &rect);
   }

   /* render bridges texture */

   for (int i= 0; i< game_nb_nodes(env->g); i++){
      SDL_QueryTexture(env->texture_node[i], NULL, NULL, &x, &y);
      if (get_degree_dir(env->g,i,0) == 1){render_simple_line_h(ren,env->g,i,x,w,env->max_x,env->max_y,h);}
      if (get_degree_dir(env->g,i,0) ==2){render_double_line_h(ren, env->g, i, x, y, w, env->max_x, env->max_y, h);}
      if (get_degree_dir(env->g,i,3) ==1){render_simple_line_v(ren, env->g, i, x, y, w, env->max_x, env->max_y, h);}
      if (get_degree_dir(env->g,i,3) ==2){render_double_line_v(ren, env->g, i, x, y, w, env->max_x, env->max_y, h);}}}


/* **************************************************************** */


bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{
   if (e->type == SDL_QUIT)
       return true;
   if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE){
      return true;}
   if (game_over(env->g)){
      printf("CONGRATULATION YOU WIN !\n");
      return true;
   }

   int w, h;

   int nb_nodes = game_nb_nodes(env->g);
   SDL_GetWindowSize(win, &w, &h);
   SDL_Point mouse;


   if (e->type == SDL_MOUSEBUTTONDOWN){

      if (e->button.button == SDL_BUTTON_LEFT){
      SDL_GetMouseState(&(mouse.x), &(mouse.y));
      add_bridge(nb_nodes, env->g, w, h, env->max_x, env->max_y, mouse.x, mouse.y, env->bridge);
      update_color(ren, e, env->g, env->texture_node, nb_nodes);}

      if (e->button.button == SDL_BUTTON_RIGHT){
      SDL_GetMouseState(&(mouse.x), &(mouse.y));
      delete_bridge(nb_nodes, env->g, w, h, env->max_x, env->max_y, mouse.x, mouse.y, env->bridge);
      update_color(ren, e, env->g, env->texture_node, nb_nodes);}
   }
   return false;}



/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
   for (int i = 0; i<game_nb_nodes(env->g); i++){SDL_DestroyTexture(env->texture_node[i]);}
   SDL_DestroyTexture(env->background);
   free(env->texture_node);
   free(env->bridge);
   delete_game(env->g);
   free(env);}

/* **************************************************************** */


