#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "../include/game.h"
#include "../include/node.h"

game load_default_game (const char* path){

   int i,j,k;

   FILE* Fpointer = fopen(path,"r");

   if(Fpointer == NULL){
      fprintf(stderr,"Impossible d'ouvrir le fichier %s \n", path);
      exit(EXIT_FAILURE);
   }

   fscanf(Fpointer,"%d %d %d",&i,&j,&k);

   int nb_nodes = i;
   /////// load_default_node /////////

   int ch=0;
   int nb_lines=1;
   long pointer_old_location = ftell(Fpointer);
   fseek(Fpointer,0,SEEK_SET);
   while(!feof(Fpointer))
   {
      ch = fgetc(Fpointer);
      if(ch == '\n'){
         ch = fgetc(Fpointer);
         if(isdigit(ch))
         {
            nb_lines++;
         }
      }
   }

   fseek(Fpointer,pointer_old_location,SEEK_SET);

   int var = (nb_lines) - nb_nodes;
   assert( var > 0);

   //////////////////////////////////

   node nodes[i];
   int nb_max_bridges = j;
   int nb_dir = k;
   assert(nb_dir == 4 || nb_dir == 8);

   for (int compt = 0; compt < nb_nodes;compt ++){
      fscanf(Fpointer,"%d %d %d",&i,&j,&k);
      nodes[compt]=new_node(i,j,k);
   }

   game g = new_game(nb_nodes,nodes,nb_max_bridges,nb_dir);

   /////// QUICK SOLVE //////////////
   int acc = 0;
   for (int i=0; i<nb_nodes+1; i++){
      if (game_node(g,i) != NULL)
         acc = acc + get_required_degree(nodes[i]);
   }
   if (acc%2 != 0){
      fprintf(stderr,"Ce problème n'a aucune solution !\n");
      exit(EXIT_SUCCESS);
   }
   //////////////////////////////////

   for (int compt = 0; compt < nb_nodes;compt ++)
      delete_node(nodes[compt]);

   fclose(Fpointer);

   return g;
}

void save_game(game g, char * path){

   FILE *Fpointer;
   strcat(path,".solved");
   Fpointer = fopen(path,"w");

   //////// VARIABLES/////////
   int nb_nodes = game_nb_nodes(g);
   int nb_max_bridges = game_nb_max_bridges(g);
   int nb_dir = game_nb_dir(g);


   /////// ALGORITHME//////////
   if(Fpointer == NULL){
      printf("Impossible d'ouvrir le fichier de sauvegarde, \n");
      exit(EXIT_FAILURE);
   }

   else{
      fprintf(Fpointer,"%d %d %d \n",nb_nodes,nb_max_bridges,nb_dir);

            if (nb_dir == 4){
               for (int compteur = 0; compteur < nb_nodes; compteur++){
                  int x = get_x(game_node(g,compteur));
                  int y = get_y(game_node(g,compteur));
                  fprintf(Fpointer,"%d %d %d %d %d %d %d \n",x,y,get_required_degree(game_node(g,compteur)), get_degree_dir(g,compteur,NORTH), get_degree_dir(g,compteur,WEST),get_degree_dir(g,compteur,SOUTH),get_degree_dir(g,compteur,EAST) );
               }
            }
            if (nb_dir == 8){
               for (int compteur = 0; compteur < nb_nodes; compteur++){
                  int x = get_x(game_node(g,compteur));
                  int y = get_y(game_node(g,compteur));
                  fprintf(Fpointer, "%d %d %d %d %d %d %d %d %d %d %d \n",x,y,get_required_degree(game_node(g,compteur)), get_degree_dir(g,compteur,NORTH), get_degree_dir(g,compteur,WEST), get_degree_dir(g,compteur,SOUTH), get_degree_dir(g,compteur,EAST), get_degree_dir(g,compteur,NW), get_degree_dir(g,compteur,SW), get_degree_dir(g,compteur,SE), get_degree_dir(g,compteur,NE));
               }
            }
            printf("game_solution_to_file %s \n", path);
            fclose(Fpointer);
         }
   delete_game(g);
}



////////////////////////// FONCTIONS AMELIORATION SOLVEUR RECURSSIF ////////////////////////////////
bool isolate(game g_src, int num_node){
   game g = copy_game(g_src);
   int try = 0;
   int d = 0;
   while (1){
      if (can_add_bridge_dir(g,num_node,d)){
         add_bridge_dir(g,num_node,d);
         try = 0;
         d++;
      }
      else {
         try ++;
         d++;
      }
      if (try == 4)
         break;
   }
   int degre = get_degree(g,num_node);
   delete_game(g);
   return (get_required_degree((game_node(g,num_node)))==degre);
}


bool good_conf (game g_src, int num_node,int i, int j, int k, int l){ // Test si la configuration (i,j,k,l) est bonne pour le node

   game g = copy_game(g_src);

   for (int cmpt = 0; cmpt<i; cmpt++){
      if (can_add_bridge_dir(g,num_node,NORTH) )
         add_bridge_dir(g,num_node,NORTH);
      else{
         delete_game(g);
         return false;
      }

   }

   for (int cmpt = 0; cmpt<j; cmpt++){
      if (can_add_bridge_dir(g,num_node,WEST))
         add_bridge_dir(g,num_node,WEST);
      else{
         delete_game(g);
         return false;
      }
   }

   for (int cmpt = 0; cmpt<k; cmpt++){
      if (can_add_bridge_dir(g,num_node,SOUTH) )
         add_bridge_dir(g,num_node,SOUTH);
      else{
         delete_game(g);
         return false;
      }
   }

   for (int cmpt = 0; cmpt<l; cmpt++){
      if (can_add_bridge_dir(g,num_node,EAST) )
         add_bridge_dir(g,num_node,EAST);
      else{
         delete_game(g);
         return false;
      }
   }
   delete_game(g);
   return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




game solveur_recursif(game g, int num_node){

   if (num_node == game_nb_nodes(g)){
      if (game_over(g))
         return copy_game(g);
      else{
         printf("Solution non trouvée !\n");
         delete_game(g);
         exit(EXIT_FAILURE);
         return NULL;
      }

   }
   int nb_pont_manquant = get_required_degree(game_node(g,num_node)) - get_degree(g,num_node);


   for (int i =0; i<=2; i++){
      for (int j=0; j<=2; j++){
         for(int k=0; k<=2; k++){
            for(int l=0; l<=2;l++){
               if (i+j+k+l == nb_pont_manquant){
                  for(int cmpt =0; cmpt<i;cmpt++){
                     if (can_add_bridge_dir(g,num_node,NORTH))
                        add_bridge_dir(g, num_node, NORTH);
                  }
                  for(int cmpt =0; cmpt<i;cmpt++){
                     if (can_add_bridge_dir(g,num_node,WEST))
                        add_bridge_dir(g, num_node, WEST);
                  }
                  for(int cmpt =0; cmpt<i;cmpt++){
                     if (can_add_bridge_dir(g,num_node,SOUTH))
                        add_bridge_dir(g, num_node, SOUTH);
                  }
                  for(int cmpt =0; cmpt<i;cmpt++)
                  {
                     if (can_add_bridge_dir(g,num_node,EAST))
                        add_bridge_dir(g, num_node, EAST);
                  }
               }
            }
         }
      }
   }

game g2 = g;
game solution = solveur_recursif(g2, num_node+1);

if (solution != NULL){
   return solution;
}


   return NULL; ///////////// g pour le test !!
}

game solveur(game g){
   return solveur_recursif(g,0);
}



int main(int argc, char *argv[]){

   game g = load_default_game(argv[1]);

   game solved = solveur(g);

   delete_game(g);

   save_game(solved, argv[1]);

   return EXIT_SUCCESS;
}
