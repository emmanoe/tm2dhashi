#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "node.h"

int main(void){
   int nb_nodes = 3;
   node n0 = new_node(0, 0, 2);
   node n1 = new_node(1, 0, 1);
   node n2 = new_node(0, 2, 1);
   node nodes[nb_nodes];
   nodes[0]=n0;
   nodes[1]=n1;
   nodes[2]=n2;
   game g = new_game(nb_nodes, nodes);
   game_over(g);
   game_node(g, 1);
   /* -------------------- Déterminer position max ---------------------- */
   int max=0;
   for (int i = 0;i<nb_nodes;i++){
      if (get_x(nodes[i])>max)
         max = get_x(nodes[i]);
      if (get_y(nodes[i])>max)
         max = get_y(nodes[i]);
   }
   /* printf("max = %d\n",max); */

   /* ------------------------------------------------------------------- */

   for (int x = max ; x>=0; x--){
     for (int y = 0; y<=max; y++){
        int i = 0;
        while (((get_x(nodes[i])!=x)||(get_y(nodes[i])!=y))&&(i<nb_nodes)){
           i++;
        }
        if (i<nb_nodes){printf("%d ", get_required_degree(nodes[i]));}
        else {printf("- ");}
     }
     printf("\n");
   }
   delete_game(g);
   return EXIT_SUCCESS; //c'est bien
}
