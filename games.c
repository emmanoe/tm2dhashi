#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

typedef enum dir_e{
   NORTH,
   WEST,
   SOUTH,
   EAST
} dir;

typedef struct bridge_s{
   node debut; // node_num
   dir d;
   int type; //simple ou double
}bridge;

struct game_s{
   node* set_of_nodes; // Pointeur de type noeud vers le tableau de noeuds
   int nb_nodes;
   bridge* bridges_already_build; // Tableau de bridges déja construit (debut,dir,type)
};

typedef struct game_s* game;
typedef const struct game_s* cgame;

game new_game(int nb_nodes, node *nodes){
   game g = (game) malloc(nb_nodes*sizeof(struct game_s));
   g -> set_of_nodes = nodes; //Tableau de nodes
   g -> nb_nodes = nb_nodes;
   return g;
}

void delete_game (game g){
   if (g!=NULL){
      free(g -> set_of_nodes); // On libère chaque objet initialisé à l'aide de malloc
      free(g -> bridges_already_build);
      free(g);
   }
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
}

bool can_add_bridge_dir (cgame g, int node_num, dir d){}

void add_bridge_dir (game g, int node_num, dir d){}

void del_bridge_dir (game g, int node_num, dir d){}

int get_degree_dir (cgame g, int node_num, dir d){}

int get_degree (cgame g, int node_num) {}

int get_neighbour_dir (cgame g, int node_num, dir d){}

int game_get_node_number (cgame, int x, int y){}



int main (void){
   node n=(new_node(0,0,3));
   node n1=(new_node(0,0,3));
   node nodes[2];
   nodes[0]=n;
   nodes[1]=n1;
   game g=new_game(2,nodes);
   return (EXIT_SUCCESS);
}
