#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct node_s {
   int x;// x-axe from left to right
   int y;// y-axe from bottom to top
   int required_degree;
};

typedef struct node_s* node;

node new_node(int x, int y, int required_degree){
   node new = malloc(sizeof(struct node_s));
   if (new != NULL){
      new -> x = x; // Coordonnée x du noeud
      new -> y = y; // Coordonnée y du noeud
      new -> required_degree = required_degree; // Degré du noeud
      return new;
   }
   printf("Not enought memory\n"); // Si n n'existe pas, on affiche l'erreur
   exit(EXIT_FAILURE);
}

void delete_node (node n){
   if ( n!=NULL)
      free(n);
}

int get_x(node n){
   if (n!=NULL)
      return n -> x;
   printf("Not enought memory\n"); // Si n n'existe pas, on affiche l'erreur
   exit(EXIT_FAILURE);
}

int get_y(node n){
   if (n!=NULL)
      return n -> y;
   printf("Not enought memory\n"); // Si n n'existe pas, on affiche l'erreur
   exit(EXIT_FAILURE);
}

int get_required_degree (node n){
   if (n!=NULL)
      return n -> required_degree;
   printf("Not enought memory\n"); // Si n n'existe pas, on affiche l'erreur
   exit(EXIT_FAILURE);
}
