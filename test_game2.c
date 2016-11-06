#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "test_toolbox.h"



/* Defalult configuration
   2     2     3

   5     1

   3           2
*/

#define EXAMPLE_NB_NODE 7
int vals[EXAMPLE_NB_NODE][3] = {{0,0,3},{0,1,5},{0,2,2},{1,1,1},{1,2,2},{2,0,2},{2,2,3}};

node nodes[EXAMPLE_NB_NODE];


bool test_new_game() {
   for (int i = 0 ; i < EXAMPLE_NB_NODE; i++){
      nodes[i] = new_node(vals[i][0],vals[i][1],vals[i][2]);
   }
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   bool r=false;;
   if (g!=NULL)
      r = true;
   r= r && test_equality_bool(true,r,"pb new game");

   delete_game(g);
   return r;
}

bool test_delete_game() {
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   node test = game_node(g,1);
   bool r=false;;
   delete_game(g); //  BUG DELETE_GAME ??????
   node test2 = game_node(g,1);
   if (g==NULL)
      r = true;
   r= r && test_equality_bool(true,r,"pb new game");

   return r;
}


bool test_copy_game() {}

bool test_game_nb_nodes(){
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   bool r = true;

   r = r && test_equality_int(EXAMPLE_NB_NODE,game_nb_nodes(g),"pb nb_nodes");

   delete_game(g);
   return r;
}

bool test_game_node() {
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   node n;
   bool r = true;

   for (int i=0;i<EXAMPLE_NB_NODE;i++){
      n = game_node(g,i);
      if (n==NULL) // Cas erreur de segmentation non traité !
         return false;
      r = r && test_equality_bool(true,r,"pb game_node");
      r = r && test_equality_int(get_x(n),vals[i][0],"pb game_node");
      r = r && test_equality_int(get_y(n),vals[i][1],"pb game_node");
      r = r && test_equality_int(get_required_degree(n),vals[i][2],"pb game_node");
   }
   return r;
}


int main (int argc, char *argv[])
{
   bool result= true;
   result = result && test_new_game();
   result = result && test_game_nb_nodes();
   result = result && test_game_node();
   //result = result && test_delete_game();
   //result = result && test_copy_game();
   if (result)
      return EXIT_SUCCESS;
   else
      return EXIT_FAILURE;
}
