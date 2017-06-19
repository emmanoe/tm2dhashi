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
   game g = new_game(EXAMPLE_NB_NODE,nodes,4,4);
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
   game g = new_game(EXAMPLE_NB_NODE,nodes,4,4);
   bool r=true;
   delete_game(g);
   r = test_equality_bool(true,r,"pb new game") && r;
   *p = bilan(r);
   return r;
}



bool test_copy_game() {
   bool r=true;
   game g = new_game(EXAMPLE_NB_NODE,nodes,4,4);
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
   game g = new_game(EXAMPLE_NB_NODE,nodes,4,4);
   bool r = true;

   r = test_equality_int(EXAMPLE_NB_NODE,game_nb_nodes(g),"pb nb_nodes") && r;

   delete_game(g);
   *p = bilan(r);
   return r;
}

bool test_game_nb_dir(){
   game g = new_game(EXAMPLE_NB_NODE,nodes,4,4);
   bool r = true;
   r = test_equality_int(4 ,game_nb_dir(g),"pb nb_dir");
   delete_game(g);
   *p = bilan(r);
   return r;
}

bool test_game_node() {
   game g = new_game(EXAMPLE_NB_NODE,nodes,4,4);
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

bool test_game_over(){
   // Example node fonction game over

   int vals[4][3] = {{0,0,2},{0,1,2},{1,0,1},{1,1,1}};
   node nodes[4];

   bool r = true;

   for (int i = 0 ; i < 4; i++){
      nodes[i] = new_node(vals[i][0],vals[i][1],vals[i][2]);
   }

   game g = new_game(4,nodes,2,4); // (int nb_nodes, node *nodes, int nb_max_bridges, int nb_dir)

   if (can_add_bridge_dir(g, 0, EAST)){

      add_bridge_dir(g, 0, EAST);

   }

   if (can_add_bridge_dir(g, 0, NORTH)){

      add_bridge_dir(g, 0, NORTH);

   }

   if (can_add_bridge_dir(g, 1, EAST)){

      add_bridge_dir(g, 1, EAST);

   }

   r = test_equality_bool(true, game_over(g),"pb game_over") && r;


   *p = bilan(r);
   return r;

  }

bool test_add_bridge(){
   game g = new_game(EXAMPLE_NB_NODE,nodes,9,4);
   bool r = true;
   for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
      int num = game_get_node_number (g, vals[i][0], vals[i][1]);
      if (can_add_bridge_dir(g, num,EAST)){
         add_bridge_dir(g, num, EAST);
      }
      if (can_add_bridge_dir(g, num,NORTH)){
         add_bridge_dir(g, num, NORTH);
      }
      if (can_add_bridge_dir(g, num,NORTH)){
         add_bridge_dir(g, num, NORTH);
      }
   }

      r = test_equality_int(1,get_degree_dir(g, 0, EAST),"Problème add_bridge node num 0 EAST");
      r = test_equality_int(1,get_degree_dir(g, 1, EAST),"Problème add_bridge node num 1 EAST");
      r = test_equality_int(0,get_degree_dir(g, 3, EAST),"Problème add_bridge node num 3 EAST");
      r = test_equality_int(0,get_degree_dir(g, 6, EAST),"Problème add_bridge node num 6 EAST");

      r = test_equality_int(2,get_degree_dir(g, 3, NORTH),"Problème add_bridge node num 3 NORTH");
      r = test_equality_int(2,get_degree_dir(g, 5, NORTH),"Problème add_bridge node num 5 NORTH");
      r = test_equality_int(0,get_degree_dir(g, 4, NORTH),"Problème add_bridge node num 4 NORTH");
      r = test_equality_int(0,get_degree_dir(g, 2, NORTH),"Problème add_bridge node num 2 NORTH");

    delete_game(g);
    *p = bilan(r);
    return r;
}


bool test_del_bridge(){
   game g = new_game(EXAMPLE_NB_NODE,nodes,9,4);
   bool r = true;
   for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
      int num = game_get_node_number (g, vals[i][0], vals[i][1]);
      if (can_add_bridge_dir(g, num,EAST)){
         add_bridge_dir(g, num, EAST);
      }
      if (can_add_bridge_dir(g, num,NORTH)){
         add_bridge_dir(g, num, NORTH);
      }
      if (can_add_bridge_dir(g, num,NORTH)){
         add_bridge_dir(g, num, NORTH);
      }
   }

   del_bridge_dir(g, 0, EAST);
   del_bridge_dir(g, 1, EAST);

   del_bridge_dir(g, 3, NORTH);
   del_bridge_dir(g, 5, NORTH);

   r = test_equality_int(0,get_degree_dir(g, 0, EAST),"Problème del_bridge node num 1 EAST");
   r = test_equality_int(0,get_degree_dir(g, 1, EAST),"Problème add_bridge node num 1 EAST");

   r = test_equality_int(1,get_degree_dir(g, 3, NORTH),"Problème del__bridge node num 3 EAST");
   r = test_equality_int(1,get_degree_dir(g, 5, NORTH),"Problème del_bridge node num 6 EAST");

   del_bridge_dir(g, 3, NORTH);
   del_bridge_dir(g, 5, NORTH);

   r = test_equality_int(0,get_degree_dir(g, 3, NORTH),"Problème del_bridge node num 3 EAST");
   r = test_equality_int(0,get_degree_dir(g, 5, NORTH),"Problème del_bridge node num 6 EAST");

   delete_game(g);
   *p = bilan(r);
    return r;
}

bool test_get_degree_dir (){
      game g = new_game(EXAMPLE_NB_NODE,nodes,2,4);
   bool r = true;
   for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
      int num = game_get_node_number (g, vals[i][0], vals[i][1]);
      if (can_add_bridge_dir(g, num,EAST)){
         add_bridge_dir(g, num, EAST);
      }
      if (can_add_bridge_dir(g, num,NORTH)){
         add_bridge_dir(g, num, NORTH);
      }
      if (can_add_bridge_dir(g, num,NORTH)){
         add_bridge_dir(g, num, NORTH);
      }
   }

      r = test_equality_int(1,get_degree_dir(g, 0, EAST),"Problème get_degree_dir node num 0 EAST");
      r = test_equality_int(1,get_degree_dir(g, 1, EAST),"Problème get_degree_dir node num 1 EAST");
      r = test_equality_int(0,get_degree_dir(g, 3, EAST),"Problème get_degree_dir node num 3 EAST");
      r = test_equality_int(0,get_degree_dir(g, 6, EAST),"Problème get_degree_dir node num 6 EAST");

      r = test_equality_int(2,get_degree_dir(g, 3, NORTH),"Problème get_degree_dir node num 3 NORTH");
      r = test_equality_int(2,get_degree_dir(g, 5, NORTH),"Problème get_degree_dir node num 5 NORTH");
      r = test_equality_int(0,get_degree_dir(g, 4, NORTH),"Problème get_degree_dir node num 4 NORTH");
      r = test_equality_int(0,get_degree_dir(g, 2, NORTH),"Problème get_degree_dir node num 2 NORTH");

    delete_game(g);
    *p = bilan(r);
    return r;
}



bool test_get_degree(){

   game g = new_game(EXAMPLE_NB_NODE,nodes,2,4);
   bool r = true;

   for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
      int num = game_get_node_number (g, vals[i][0], vals[i][1]);

      if (can_add_bridge_dir(g, num,EAST)){ // Rajout de pont pour tester le degree
         add_bridge_dir(g, num, EAST);
      }
      if (can_add_bridge_dir(g, num,NORTH)){
         add_bridge_dir(g, num, NORTH);
      }
      if (can_add_bridge_dir(g, num,NORTH)){
         add_bridge_dir(g, num, NORTH);
      }
   }

    r = test_equality_int(3, get_degree(g, 0),"Problème get_degree node num 0 ");


    delete_game(g);
    *p = bilan(r);
    return r;

  }


bool test_get_node_number() {
   game g = new_game(EXAMPLE_NB_NODE,nodes,2,4);
   bool r = true;

   for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
      int num = game_get_node_number (g, vals[i][0], vals[i][1]);
      r = r && test_interval_int(0,EXAMPLE_NB_NODE-1, num, "Pb game_node_number");
      node n = game_node(g, num);
      r = r && test_equality_int(vals[i][2], get_required_degree(n), "Pb with degrees");
    }
    r = r && test_equality_int(-1, game_get_node_number (g, 1, 0), "Pb game_node_number");
    r = r && test_equality_int(-1, game_get_node_number (g, 2, 1), "Pb game_node_number");
    delete_game(g);
    *p = bilan(r);
    return r;
}

bool test_can_add_bridge_dir() {
   game g = new_game(EXAMPLE_NB_NODE,nodes,9,4);
    bool r = true;
    int num = game_get_node_number (g, 0, 0);
    r = r && test_equality_bool(true, can_add_bridge_dir(g, num, NORTH), "can add NORTH");
    r = r && test_equality_bool(true, can_add_bridge_dir(g, num, EAST), "can add EAST");
    r = r && test_equality_bool(false, can_add_bridge_dir(g, num, WEST), "can add WEST");
    r = r && test_equality_bool(false, can_add_bridge_dir(g, num, SOUTH), "can add SOUTH");
    delete_game(g);
    *p = bilan(r);
    return r;
}



bool test_get_neighbour_dir() {
   game g = new_game(EXAMPLE_NB_NODE,nodes,9,4);
    bool r = true;
    r = r && test_equality_int(5, get_neighbour_dir(g,6,SOUTH), "pb neighbour 6 SOUTH");
    r = r && test_equality_int(4, get_neighbour_dir(g,2,EAST), "pb neighbour 2 EAST");
    r = r && test_equality_int(0, get_neighbour_dir(g,1,SOUTH), "pb neighbour 1 SOUTH");
    r = r && test_equality_int(2, get_neighbour_dir(g,1,NORTH), "pb neighbour 1 NORTH");

    delete_game(g);
    *p = bilan(r);
    return r;
}





int main (int argc, char *argv[])
{
   bool result= true;
   result = test_new_game() && result; // EFFECTUE TOUT LES TESTS !
   result = test_game_nb_nodes() && result;
   result = test_game_nb_dir() && result;
   result = test_game_node() && result;
   result = test_game_over() && result;
   result = test_delete_game() && result;
   result = test_copy_game() && result;
   result = test_get_neighbour_dir() && result;
   result = test_add_bridge() && result;
   result = test_get_node_number() && result;
   result = test_del_bridge() && result;
   result = test_get_degree_dir() && result;
   result = test_get_degree() && result;
   result = test_can_add_bridge_dir() && result;
   if (result){
      printf ("Les tests se sont déroulés normalement, bilan %d/14\n",cmpt);
      return EXIT_SUCCESS;
   }
   else{
      printf ("Il y a quelques erreurs dans vos tests, bilan %d/14\n",cmpt);
      return EXIT_FAILURE;
   }
}//////// AJOUTER BILAN TOTAL DES TEST!!
