#ifndef _GAME_C_
#define _GAME_C_
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.c"


typedef enum dir_e{
   WEST = 1, // Les énumérations permettent de regrouper des valeurs constantes entières
   EAST,
   NORTH,
   SOUTH // == 4
} dir;



struct game_s{
   node* set_of_nodes; // Pointeur de type noeud vers le tableau de noeuds
   int nb_nodes;
   int** bridges_already_build; // Pointeur vers tableau contenant "nb_nodes" tableaux d'entier
};

typedef struct game_s* game;
typedef const struct game_s* cgame;

game new_game(int nb_nodes, node *nodes){
   game g = (game) malloc(sizeof(struct game_s)); // Allocation dynamique
   g -> set_of_nodes = nodes; //Tableau de nodes
   g -> nb_nodes = nb_nodes;

   int** t = malloc(sizeof(int*)*nb_nodes); // On créé le tableau principal qui va contenir l'autre tableau
   if (t==NULL){
      printf("Not enought memory!\n");
      exit(EXIT_FAILURE);
   }

   for (int i=0;i<nb_nodes;i++){
      t[i] = malloc (sizeof(int)); //Puis on alloue chacun des sous-tableaux, t[i][j] stoque les informations sur le degrés de nodes[i]
      if (t[i]==NULL){
         printf("Not enought memory!\n");
         exit(EXIT_FAILURE);
      }
   }
   for (int i = 0; i< nb_nodes;i++){
      for (int j=0; j<4;j++){ //j corespond à une direction (ex: 1 représente le NORD) et 0 <= t[i][j] <= 2
         t[i][j] = 0; // Initialisé à 0
      }
   }

    g->bridges_already_build = t;
   return g;
}

void delete_game (game g){
   if (g!=NULL){

      if (g->bridges_already_build != NULL){
         for (int i = 0;i<g->nb_nodes;i++){
            free(g->bridges_already_build[i]); // Il faut libérer les sous-tableaux avant de pouvoir libérer le tableau principal
         }
      free(g -> bridges_already_build);
   }

   free(g);
   }
   return;
}


game copy_game (cgame g_src){
   game g=(game) malloc(sizeof(g_src));
   if (g != NULL){ // On recopie tous les champs de la structure game !
      g -> set_of_nodes = g_src->set_of_nodes;
      g -> nb_nodes = g_src -> nb_nodes;
      g -> bridges_already_build=g_src->bridges_already_build;
      return g;
   }
   printf("Not enought memory !\n"); // Si le le jeu n'existe pas on annule
   exit(EXIT_FAILURE);
}


int game_nb_nodes (cgame g){
   if (g!=NULL)
      return g -> nb_nodes;
   return EXIT_FAILURE;
}

node game_node(cgame g, int node_num){
   assert(node_num<g->nb_nodes); // On vérifie que node_num est entre 0 et nb_nodes-1
   return g->set_of_nodes[node_num];
}

bool game_over (cgame g){
   if (g!=NULL){
      int somme_bridge =0 ;
      for (int i=0; i<game_nb_nodes(g);i++){
         for (int j=0;j<4; j++){
            somme_bridge = somme_bridge + g->bridges_already_build[i][j];
         }
         if (somme_bridge != g->set_of_nodes[i]->required_degree){// Si la somme des ponts de l'ile n°i négale pas le numéro qu'elle affiche alors c'est perdu
            return 1;
         }
      }
   }
   return EXIT_FAILURE;
}



void del_bridge_dir (game g, int node_num, dir d){
   int entier = d;
   if (g->bridges_already_build[node_num][d]>0)
      g->bridges_already_build[node_num][entier]--;
}

int get_degree_dir (cgame g, int node_num, dir d){
   int entier = d;
   return g->bridges_already_build[node_num][entier];
}


int get_degree (cgame g, int node_num) {
   int cmpt =0;
   for (int i=0; i<4;i++){
      cmpt = cmpt + get_degree_dir(g, node_num, i);
   }
   return cmpt;
}

int get_neighbour_dir (cgame g, int node_num, dir d){
   if (d == EAST){
      for (int i=node_num; i<g->nb_nodes;i++){
         if ((game_node(g,node_num) != game_node(g,i)) && (get_y(game_node(g,i)) == get_y(game_node(g,node_num))))
            return i;
      }
   }
   if (d == WEST){
      for (int i=node_num; i>=0;i--){
         if ((game_node(g,node_num) != game_node(g,i)) && (get_y(game_node(g,i)) == get_y(game_node(g,node_num))))
            return i;
      }
   }
   if (d == NORTH){
      for (int i=node_num; i<g->nb_nodes;i++){
         if ((game_node(g,node_num) != game_node(g,i)) && (get_x(game_node(g,i)) == get_x(game_node(g,node_num))))
            return i;
      }
   }
   if (d == SOUTH){
      for (int i=node_num; i>=0;i--){
         if ((game_node(g,node_num) != game_node(g,i)) && (get_x(game_node(g,i)) == get_x(game_node(g,node_num))))
            return i;
      }
   }
   return -1;
}


int game_get_node_number (cgame g, int x, int y){
   int i=0;
   while (i < g->nb_nodes){
      if (get_x(g -> set_of_nodes[i]) == x && get_y(g->set_of_nodes[i]) == y)
         return i;
      i++;
   }
   return -1;
}

bool can_add_bridge_dir (cgame g, int node_num, dir d){
   int entier = d ;

   if (g->bridges_already_build[node_num][entier]>=2 || get_neighbour_dir(g, node_num, d) == -1)
      return 0;
   return 1;
}

void add_bridge_dir (game g, int node_num, dir d){
   int entier =d ;

   if (can_add_bridge_dir(g, node_num,d)){
      g->bridges_already_build[node_num][entier]++;
      int neighbour_dir = get_neighbour_dir(g,node_num,d);
      g->bridges_already_build[neighbour_dir][(entier+1)]++;
   }
}


#endif
