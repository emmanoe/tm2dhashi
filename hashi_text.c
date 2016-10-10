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
   for (int i = 5 ; i>=0; i--){
     for (int j = 0; j<6; j++){
       if ((get_x(n0)==i) && (get_y(n0)==j)){
     printf("%d ", get_required_degree(n0));
       }
       else if ((get_x(n1)==i) && (get_y(n1)==j)){  /* Deg à revoir au plus vite !! */
     printf("%d ", get_required_degree(n1));
       }
       else if ((get_x(n2)==i) && (get_y(n2)==j)){
     printf("%d ", get_required_degree(n2));
       }
       else {
     printf("- ");
       }
       if (j==5) {
       printf("\n");
       }
     }
   }
   delete_game(g);
   return EXIT_SUCCESS;
}
