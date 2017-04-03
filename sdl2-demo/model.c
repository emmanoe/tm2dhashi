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
   int bridge[500]; // a corriger 
   int max_x, max_y;
   int nb_nodes;
   game g;
};

/* **************************************************************** */

/*Initialise les champs de la structure correspondant avec la plus grande des valeurs prise par les composantes x et y */

int taille_tab(Env* env,int* pt_x, int* pt_y, int nb_nodes)
{
    (*pt_x)=-1;
    (*pt_y)=-1;
    for(int i= 0; i < nb_nodes; i++)
    {
       if((*pt_x) < get_x(game_node(env->g,i)))
            (*pt_x) = get_x(game_node(env->g,i));
       if((*pt_y) < get_y(game_node(env->g,i) ))
            (*pt_y) = get_y(game_node(env->g,i));
    }
    (*pt_x)+=1;
    (*pt_y)+=1;

    if (env->max_x> env->max_y)
       return env->max_x;
    return env->max_y;
}



Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{
   /* Initialisation de l'environnement */
   Env * env = malloc(sizeof(struct Env_t));

   /* chargement des parametres du jeu */
   int i,j,k;
   char *path = argv[1];
   FILE* Fpointer = fopen(path,"r");
   if(Fpointer == NULL) ERROR("Impossible d'ouvrir le fichier %s \n", path);
   fscanf(Fpointer,"%d %d %d",&i,&j,&k);
   int nb_max_bridges = j;
   printf("j=%d\n",nb_max_bridges);
   int nb_dir = k;assert(nb_dir == 4 || nb_dir == 8);

   /* intialisation des champs de la structure */
   env->nb_nodes = i; // "i" lu à partir du fichier
   env->texture_node =  malloc( (i+1) * sizeof(SDL_Texture *));

   /* load_default_node */
   int ch=0;
   int nb_lines=1;
   long pointer_old_location = ftell(Fpointer);
   fseek(Fpointer,0,SEEK_SET);

   /* check if nb_node match with the file number lines*/
   while(!feof(Fpointer)){
      ch = fgetc(Fpointer);
      if(ch == '\n'){ch = fgetc(Fpointer);
         if(isdigit(ch)){nb_lines++;}}}

   fseek(Fpointer,pointer_old_location,SEEK_SET); // On repositionne le pointeur à sa position initiale
   int var = (nb_lines) - env->nb_nodes; // On fait la difference pour savoir si c'est le bon nombre de lignes.
   assert( var > 0);

   /* intialisation du jeu g */
   node nodes[i];
   for (int compt = 0; compt < env->nb_nodes;compt ++){fscanf(Fpointer,"%d %d %d",&i,&j,&k);
      nodes[compt]=new_node(i,j,k);}
   game g = new_game(env->nb_nodes,nodes,nb_max_bridges,nb_dir);env->g = g;

   /* **************************************************************** */

   PRINT("TEST1\n");
   PRINT("TEST2\n");

   /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);

  if(!env->background)
     ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  /* init node texture using Arial font */
  SDL_Color color = { 255, 255, 255, 255 }; /* white color in RGBA */

  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE); /* police de caractère */

  if(!font)
     ERROR("TTF_OpenFont: %s\n", FONT);

  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL

  char  s[1]; // s necéssaire pour convertir le noeuds (int) en  text (* char) pour TTF_RenderText


  for (int i =0; i< env->nb_nodes; i++){
     sprintf(s,"%d",get_required_degree(game_node(env->g,i)));
     SDL_Surface * surf = TTF_RenderText_Blended(font, s, color); // blended rendering for ultra nice text
     env->texture_node[i] = SDL_CreateTextureFromSurface(ren, surf);
     SDL_FreeSurface(surf);
  }

  TTF_CloseFont(font);
  fclose(Fpointer);
  for (int a = 0; a < env->nb_nodes;a ++)
      delete_node(nodes[a]);

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
   int w, h;

   SDL_GetWindowSize(win, &w, &h);
   SDL_Point mouse;


   if (e->type == SDL_MOUSEBUTTONDOWN){
      if (e->button.button == SDL_BUTTON_LEFT){
      SDL_GetMouseState(&(mouse.x), &(mouse.y));
      printf("mouse.x=%d, mouse.y=%d\n",mouse.x,mouse.y);

      for (int i = 0; i<env->nb_nodes; i++){

         if ((get_x(game_node(env->g,i))) * (double)(w/env->max_x) <= mouse.x && mouse.x <= get_x((game_node(env->g,i))) * (double)(w/env->max_x) + 22 && h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h <= mouse.y && mouse.y <= h - (((1.0+(double)get_y(game_node(env->g,i)))/env->max_y))*h + 35) {

            env->bridge[i] = 1;
            for (int x = 0; x <4; x++){
               if (env->bridge[get_neighbour_dir(env->g,i,x)] == 1){
                  if (get_degree(env->g,get_neighbour_dir(env->g,i,x)) != get_required_degree(game_node(env->g,get_neighbour_dir(env->g,i,x))) && can_add_bridge_dir(env->g,i,x) ) {
                     add_bridge_dir(env->g,i,x);
                     printf("i = %d and get_degree_0 = %d\n",i,get_degree(env->g,get_neighbour_dir(env->g,i,x)));;
                  }
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

            SDL_Color color = { 255, 255, 255, 0 }; /* purple color in RGBA */
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
   if (game_over(env->g))
   {
      SDL_Color color = { 0, 0, 255, 255 }; /* blue color in RGBA */
      TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
      if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
      TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
      SDL_Surface * surf = TTF_RenderText_Blended(font, "FELICITATION VOUS AVEZ GAGNEZ!", color); // blended rendering for ultra nice text

      env->texture_node[env->nb_nodes] = SDL_CreateTextureFromSurface(ren, surf);
      SDL_FreeSurface(surf);
      TTF_CloseFont(font);

      /* render you win texture */

      SDL_Rect rect;

      /* get current window size */
      int w, h;
      SDL_GetWindowSize(win, &w, &h);

      /* render text texture */
      SDL_QueryTexture(env->texture_node[env->nb_nodes], NULL, NULL, &rect.w, &rect.h);
      rect.x = w/2 - rect.w/2; rect.y = h/2 - rect.h/2; 
      SDL_RenderCopy(ren, env->texture_node[env->nb_nodes], NULL, &rect);

      printf("YOU WIN\n");
      return true;
   }
   //printf("i already went there\n");
   if (e->type == SDL_MOUSEBUTTONDOWN)
      printf("coucou\n");





   if (e->type == SDL_QUIT) {
      return true;
   }

   /* PUT YOUR CODE HERE TO PROCESS EVENTS */
   return false; 
}



/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */
   SDL_DestroyTexture(env->background);

   for (int i = 0; i<=env->nb_nodes; i++)
      SDL_DestroyTexture(env->texture_node[i]);
   free(env->texture_node);

   delete_game(env->g);

   free(env);
}

/* **************************************************************** */


