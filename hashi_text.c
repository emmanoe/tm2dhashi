#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "node.h"

int max_x_y(int nb_nodes, node nodes[]){ /* fonction qui calcul la position du noeud le + éloigné */
   int max=0;
   for (int i = 0;i<nb_nodes;i++){
      if (get_x(nodes[i])>max)
         max = get_x(nodes[i]);
      if (get_y(nodes[i])>max)
         max = get_y(nodes[i]);
   }
   return max;
}

int get_node_num(game g,node nodes[],int x, int y){ // recuperer le numéro du node de coordoné (x,y)
   for (int i =0;i<game_nb_nodes(g);i++){
      if (get_x(nodes[i])==x && get_y(nodes[i])==y)
         return i;
   }
   printf("Erreur ces coordonnées ne correspondent à aucun noeud !\n");
   exit(0) ;
}


void game_print(int nb_nodes, node nodes[]){ /* Affiche l'instance de jeu créé */
   int max = max_x_y(nb_nodes, nodes);
   for (int x = max ; x>=0; x--){
      printf("%d  ",x); // Ajoute le repère Y
      for (int y = 0; y<=max; y++){
         int i = 0;
         while (((get_x(nodes[i])!=x)||(get_y(nodes[i])!=y))&&(i<nb_nodes)){ // on vérifie si le x et le y des nodes correspondent aux x et y du de la grille
            i++;
         }
         if (i<nb_nodes){printf("%d ", get_required_degree(nodes[i]));// si oui on print le node
         }
         else {printf(". "); // sinon on print les point "."
         }
      }

     printf("\n");
   }
   printf("\n");
   printf("   ");
   for (int i = 0; i<=max; i++){ // Ajoute le repère X
      printf("%d ",i);
   }
   printf("\n");
}


int main(void){
   int nb_nodes = 3;
   node n0 = new_node(0, 0, 2);
   node n1 = new_node(3, 0, 1);
   node n2 = new_node(0, 8, 1);
   node nodes[nb_nodes];
   nodes[0]=n0;
   nodes[1]=n1;
   nodes[2]=n2;
   game g = new_game(nb_nodes, nodes);
   game_over(g);
   game_node(g, 1);
   printf("\n");
   game_print(nb_nodes, nodes);

   int coordx=0; //Ajout de ponts entre 2 nodes
   int coordy=0;
   printf("\n");
   printf("veuiller entrer la coordonnée \"x\" du noeud:\n ");
   scanf("%d",&coordy); // coord x en vrai
   //printf("x=%d\n",coordx);
   printf("veuiller entrer la coordonnée \"y\" du noeud:\n ");
   scanf("%d",&coordx); // coord y en vrai
   printf("ces coordonnées correspondent au nodes numéro : %d \n",get_node_num(g,nodes,coordx,coordy));
   //max_x_y(nb_nodes,nodes);
   delete_game(g);
   return EXIT_SUCCESS;
}
