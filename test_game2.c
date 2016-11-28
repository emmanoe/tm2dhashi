#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "node.h"
#include "test_toolbox.h"
#include <assert.h>


/* Defalult configuration
   2     2     3

   5     1

   3           2
*/


#define EXAMPLE_NB_NODE 7
int vals[EXAMPLE_NB_NODE][3] = {{0,0,3},{0,1,5},{0,2,2},{1,1,1},{1,2,2},{2,0,2},{2,2,3}};

node nodes[EXAMPLE_NB_NODE];
int cmpt = 0;
int *p = &cmpt;

int bilan(bool r){ // // Compte le nombre de tests réussi
   if (r == 1)
      *p = *p +1;
   else
      *p = *p -1;
   return *p;
}


bool test_new_game() {
   for (int i = 0 ; i < EXAMPLE_NB_NODE; i++){
      nodes[i] = new_node(vals[i][0],vals[i][1],vals[i][2]);
   }
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   bool r = true;;

   for (int i=0;i<EXAMPLE_NB_NODE;i++){ // On vérifie si chaque ile correspond au jeu passé en paramètre !!!
      for (int y=0;y<3;y++){
         if (vals[i][0] != get_x(nodes[i])
             || (vals[i][1] != get_y(nodes[i]))
             || (vals[i][2] != get_required_degree(nodes[i]))){
            r = false;
            break;
         }
      }
   }
   r = test_equality_bool(true,r,"pb new game") && r ;

   delete_game(g);
   *p = bilan(r);
   return r;
}

bool test_delete_game() {
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   bool r=true;
   delete_game(g);
   r = test_equality_bool(true,r,"pb new game") && r;
   *p = bilan(r);
   return r;
}



bool test_copy_game() {
   bool r=true;
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   game cpg = copy_game(g);

   for (int i =0;i<EXAMPLE_NB_NODE;i++){
      if ((get_required_degree(game_node(cpg, i)) != get_required_degree(game_node(g, i)))
       || (get_x(game_node(cpg, i)) != get_x(game_node(g, i)))
          || (get_y(game_node(cpg, i)) != get_y(game_node(g, i)))){
      r = false;
      break;
   }
   }
   *p = bilan(r);
   return r;
}


bool test_game_nb_nodes(){
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   bool r = true;

   r = test_equality_int(EXAMPLE_NB_NODE,game_nb_nodes(g),"pb nb_nodes") && r;

   delete_game(g);
   *p = bilan(r);
   return r;
}

bool test_game_node() {
   game g = new_game(EXAMPLE_NB_NODE,nodes);
   node n;
   bool r = true;

   for (int i=0;i<EXAMPLE_NB_NODE;i++){
      n = game_node(g,i);
      if (n==NULL)
         r = false;
      r = test_equality_bool(true,r,"pb game_node") && r;
      r = test_equality_int(get_x(n),vals[i][0],"pb game_node") && r;
      r = test_equality_int(get_y(n),vals[i][1],"pb game_node") && r;
      r = test_equality_int(get_required_degree(n),vals[i][2],"pb game_node") && r;
   }
   *p = bilan(r);
   return r;
}


int main (int argc, char *argv[])
{
   bool result= true;
   result = test_new_game() && result; // EFFECTUE TOUT LES TESTS !
   result = test_game_nb_nodes() && result;
   result = test_game_node() && result;
   result = test_delete_game() && result;
   result = test_copy_game() && result;
   if (result){
      printf ("Les tests se sont déroulés normalement, bilan %d/13\n",cmpt);
      return EXIT_SUCCESS;
   }
   else{
      printf ("Il y a quelques erreurs dans vos tests, bilan %d/13\n",cmpt);
      return EXIT_FAILURE;
   }
}//////// AJOUTER BILAN TOTAL DES TEST!!
