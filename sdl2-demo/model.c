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
   int nb_nodes;
   game g;
};

/* **************************************************************** */

/*
* Description: taille_tab initialise les champs de la structure correspondant avec la plus grande des valeurs prise par les composantes x et y par les différents noeuds du jeu.
* Parameter : deux pointeurs qui pointent les champs de la structure
* Return: cette fonction permet aussi de retourner la plus grande valeur des deux.
*/

int taille_tab(Env* env,int* pt_x, int* pt_y, int nb_nodes)
{
    (*pt_x)=-1;(*pt_y)=-1;
    for(int i= 0; i < nb_nodes; i++){
       if((*pt_x) < get_x(game_node(env->g,i)))(*pt_x) = get_x(game_node(env->g,i));
       if((*pt_y) < get_y(game_node(env->g,i) ))(*pt_y) = get_y(game_node(env->g,i));}

    (*pt_x)+=1;(*pt_y)+=1;
    if (env->max_x> env->max_y)return env->max_x;return env->max_y;}



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
   env->nb_nodes = game_nb_nodes(g);

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
     SDL_Surface * surf = TTF_RenderText_Blended(font, s, color); /* Cre&tion rendu pour chaque noeud */
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


   taille_tab(env,&env->max_x,&env->max_y,game_nb_nodes(env->g)); // initialisation de max_x et max_y dans la structure
   SDL_GetWindowSize(win, &w, &h);


   /* render background texture */
   SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

   /* render node texture */
   for (int i= 0; i< env->nb_nodes; i++){
      SDL_Rect rect;
      SDL_QueryTexture(env->texture_node[i], NULL, NULL, &rect.w , &rect.h );
      rect.x =  (get_x(game_node(env->g,i))) * (double)(w/env->max_x)  ;
      rect.y =  h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h ; // formule pour inverser l'affichage
      SDL_RenderCopy(ren, env->texture_node[i], NULL, &rect);
   }

   /* render bridges texture */

   for (int i= 0; i< env->nb_nodes; i++){
      SDL_QueryTexture(env->texture_node[i], NULL, NULL, &x, &y);

      if (get_degree_dir(env->g,i,0) == 1){

         SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);

         SDL_RenderDrawLine(ren, (x/2) +(get_x(game_node(env->g,i))) * (double)(w/env->max_x),h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h , (x/2) + (get_x(game_node(env->g,i+1))) * (double)(w/env->max_x), 35 + h - (((1.0+(double)get_y(game_node(env->g,i+1)))/env->max_y))*h);}

      if (get_degree_dir(env->g,i,0) ==2){

         SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);

         SDL_RenderDrawLine(ren, (double)x/3 +(get_x(game_node(env->g,i))) * (double)(w/env->max_x),h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h , (double)x/3+ (get_x(game_node(env->g,i+1))) * (double)(w/env->max_x), 35 + h - (((1.0+(double)get_y(game_node(env->g,i+1)))/env->max_y))*h);

         SDL_RenderDrawLine(ren, (double)(2*x)/3 +(get_x(game_node(env->g,i))) * (double)(w/env->max_x),h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h , (double)(2*x)/3 + (get_x(game_node(env->g,i+1))) * (double)(w/env->max_x), y + h - (((1.0+(double)get_y(game_node(env->g,i+1)))/env->max_y))*h);}

       if (get_degree_dir(env->g,i,3) ==1){ 

         SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
         SDL_RenderDrawLine(ren, (x) +(get_x(game_node(env->g,i))) * (double)(w/env->max_x),h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h + (y/2) ,0 + (get_x(game_node(env->g,get_neighbour_dir(env->g,i,3)))) * (double)(w/env->max_x), (y/2) + h - (((1.0+(double)get_y(game_node(env->g,get_neighbour_dir(env->g,i,3))))/env->max_y))*h);

      }

              if (get_degree_dir(env->g,i,3) ==2){ 

         SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
         SDL_RenderDrawLine(ren, (x) +(get_x(game_node(env->g,i))) * (double)(w/env->max_x),h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h + (double)(y/3) ,0 + (get_x(game_node(env->g,get_neighbour_dir(env->g,i,3)))) * (double)(w/env->max_x),  (double)(y/3) + h - (((1.0+(double)get_y(game_node(env->g,get_neighbour_dir(env->g,i,3))))/env->max_y))*h);

         SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
         SDL_RenderDrawLine(ren, (x) +(get_x(game_node(env->g,i))) * (double)(w/env->max_x),h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h + (double)(2*y/3) ,0 + (get_x(game_node(env->g,get_neighbour_dir(env->g,i,3)))) * (double)(w/env->max_x),  (double)(2*y/3) + h - (((1.0+(double)get_y(game_node(env->g,get_neighbour_dir(env->g,i,3))))/env->max_y))*h);



      }

         }
}


/* **************************************************************** */


bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{
   if (e->type == SDL_QUIT)
       return true;
   if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
         return true;
   if (game_over(env->g)){
      printf("CONGRATULATION YOU WIN !\n");
      return true;
   }

   int w, h;

   SDL_GetWindowSize(win, &w, &h);
   SDL_Point mouse;


   if (e->type == SDL_MOUSEBUTTONDOWN){
      if (e->button.button == SDL_BUTTON_LEFT){
      SDL_GetMouseState(&(mouse.x), &(mouse.y));

      for (int i = 0; i<env->nb_nodes; i++){

         if ((get_x(game_node(env->g,i))) * (double)(w/env->max_x) <= mouse.x && mouse.x <= get_x((game_node(env->g,i))) * (double)(w/env->max_x) + 22 && h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h <= mouse.y && mouse.y <= h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h + 35) {

            env->bridge[i] = 1;
            for (int x = 0; x <4; x++){
               if (get_neighbour_dir(env->g,i,x) != -1)
                  if ( env->bridge[get_neighbour_dir(env->g,i,x)] == 1){
                     if (get_degree(env->g,get_neighbour_dir(env->g,i,x)) != get_required_degree(game_node(env->g,get_neighbour_dir(env->g,i,x))) && can_add_bridge_dir(env->g,i,x) ) {
                        add_bridge_dir(env->g,i,x);}
                     for (int cmpt = 0; cmpt < env->nb_nodes;cmpt ++)
                        env->bridge[cmpt] = 0;
                  }
            }
         }
         for (int i = 0; i< env->nb_nodes;i++){
         if (get_required_degree(game_node(env->g,i)) == get_degree(env->g,i)  ){

            SDL_Color color = { 186, 85, 211, 0 }; /* purple color in RGBA */
            TTF_Font * font2 = TTF_OpenFont(FONT, FONTSIZE); /* police de caractère */
            if(!font2)
               ERROR("TTF_OpenFont: %s\n", FONT);
            TTF_SetFontStyle(font2, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
            char  s[1];
            sprintf(s,"%d",get_required_degree(game_node(env->g,i)));
            SDL_Surface * surf = TTF_RenderText_Blended(font2, s, color); // blended rendering for ultra nice text
            env->texture_node[i] = SDL_CreateTextureFromSurface(ren, surf);
            SDL_FreeSurface(surf);
            TTF_CloseFont(font2);

         }
         }
         
      }
      }
      if (e->button.button == SDL_BUTTON_RIGHT){
      SDL_GetMouseState(&(mouse.x), &(mouse.y));
      printf("mouse.x=%d, mouse.y=%d\n",mouse.x,mouse.y);

      for (int i = 0; i<env->nb_nodes; i++){

         if ((get_x(game_node(env->g,i))) * (double)(w/env->max_x) <= mouse.x && mouse.x <= get_x((game_node(env->g,i))) * (double)(w/env->max_x) + 22 && h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h <= mouse.y && mouse.y <= h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h + 35) {

            env->bridge[i] = 1;
            for (int x = 0; x <4; x++){
               if (env->bridge[get_neighbour_dir(env->g,i,x)] == 1){
                  if (get_degree(env->g,get_neighbour_dir(env->g,i,x)) != 0 && get_degree(env->g,i) != 0 ) {
                     del_bridge_dir(env->g,i,x);
                     printf("i = %d and get_degree_0 = %d\n",i,get_degree(env->g,get_neighbour_dir(env->g,i,x)));;
                  }
                  for (int cmpt = 0; cmpt < env->nb_nodes;cmpt ++)
                     env->bridge[cmpt] = 0;
               }
            }
         }
      }
      for (int i = 0; i< env->nb_nodes;i++){
         if (get_required_degree(game_node(env->g,i)) != get_degree(env->g,i)  ){

            SDL_Color color = { 255, 255, 255, 0 }; /* white color in RGBA */
            TTF_Font * font2 = TTF_OpenFont(FONT, FONTSIZE); /* police de caractère */
            if(!font2)
               ERROR("TTF_OpenFont: %s\n", FONT);
            TTF_SetFontStyle(font2, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
            char  s[1];
            sprintf(s,"%d",get_required_degree(game_node(env->g,i)));
            SDL_Surface * surf = TTF_RenderText_Blended(font2, s, color); // blended rendering for ultra nice text
            env->texture_node[i] = SDL_CreateTextureFromSurface(ren, surf);
            SDL_FreeSurface(surf);
            TTF_CloseFont(font2);

         }
         }
      }

   }
   
   return false;
}



/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
   for (int i = 0; i<env->nb_nodes; i++){SDL_DestroyTexture(env->texture_node[i]);}
   SDL_DestroyTexture(env->background);
   free(env->texture_node);
   free(env->bridge);
   delete_game(env->g);
   free(env);}

/* **************************************************************** */


