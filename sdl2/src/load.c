#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "hashi_graph.h"

#include "../include/game.h"
#include "../include/node.h"


game load_default_game (const char* path){

   /* chargement des parametres du jeu */
   FILE* Fpointer = fopen(path,"r");

   if(Fpointer == NULL)ERROR("Impossible d'ouvrir le fichier %s \n", path);

   int i,j,k;
   fscanf(Fpointer,"%d %d %d",&i,&j,&k);
   int nb_nodes = i;int nb_max_bridges = j;int nb_dir = k;
   assert(nb_dir == 4 || nb_dir == 8);

   /* load_default_node */
   int ch=0;int nb_lines=1;
   long pointer_old_location = ftell(Fpointer);
   fseek(Fpointer,0,SEEK_SET);

   /* check if nb_node match with the file number lines*/
   while(!feof(Fpointer)){ch = fgetc(Fpointer);
      if(ch == '\n'){ch = fgetc(Fpointer);
         if(isdigit(ch)){nb_lines++;}}}

   fseek(Fpointer,pointer_old_location,SEEK_SET); //On repositionne le pointeur à sa position initiale
   int var = (nb_lines) - nb_nodes;assert( var > 0); //On fait la difference pour savoir le bon nombre de lignes correspond

   /* intialisation du jeu g */
   node nodes[i];
   for (int compt = 0; compt < nb_nodes;compt ++){fscanf(Fpointer,"%d %d %d",&i,&j,&k);
      nodes[compt]=new_node(i,j,k);}

   game g = new_game(nb_nodes,nodes,nb_max_bridges,nb_dir);

   for (int compt = 0; compt < nb_nodes;compt ++)delete_node(nodes[compt]);
   fclose(Fpointer);
   return g;

}

/*
* Description: taille_tab initialise les champs de la structure correspondant avec la plus grande des valeurs prise par les composantes x et y par les différents noeuds du jeu.
* Parameter : deux pointeurs contenant l'adresse des champs x et y de la structure
* Return: void.
*/

void init_taille_tab(game g,int* pt_x, int* pt_y, int nb_nodes)
{
    (*pt_x)=-1;(*pt_y)=-1;
    for(int i= 0; i < nb_nodes; i++){
       if((*pt_x) < get_x(game_node(g,i)))(*pt_x) = get_x(game_node(g,i));
       if((*pt_y) < get_y(game_node(g,i) ))(*pt_y) = get_y(game_node(g,i));}

    (*pt_x)+=1;(*pt_y)+=1;
}
