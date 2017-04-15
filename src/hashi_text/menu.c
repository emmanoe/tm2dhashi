#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "node.h"
#include "hashi_text.h"

                        /////////////////////////// PARTIE MENU /////////////////////

  void menu(int nb_nodes, game g, int game_nb_max_bridges, int nb_dir){

   int choix =0;  // variables nécéssaire lors intéraction avec la machine

      while (1){
         system("clear");

         printf("%5s","- MENU -\n");

         printf("\n");

         printf("1 - Reprendre");

         printf("\n");

         printf("2 - Nouvelle partie");

         printf("\n");

         printf("3 - Sauvegarder instance");

         printf("\n");

         printf("4 - Sauvegarder partie en cours\n");

         printf("5 - Solution\n");

         printf("0 - Quitter\n");

         printf("\n");

         scanf("%d", &choix);



      
      if( choix == 1 ){
         int nb = game_nb_nodes(g);
         int value = 0;
         for (int i= 0; i< nb ; i++){
            if (get_degree(g,i) > 0){value = i;break;}}
         if (get_degree(g,value) >0)break;}

      else if (choix == 2){
         for (int i = 0; i<game_nb_nodes(g);i++){
            for (int d = 0; d<4;d++)
               if (game_get_node_number(g,get_x(game_node(g,i)),get_y(game_node(g,i)) != -1)){
                  int b = get_degree_dir(g,i,d);
                  for (int cmpt = 0 ; cmpt < b ;cmpt ++)
                     del_bridge_dir(g,i,d);
               }
            }
         break;}

      else if (choix == 3){

         FILE *Fpointer;

         Fpointer = fopen("save/game_default.txt","w");

         if(Fpointer == NULL){
            printf("Impossible d'ouvrir le fichier de sauvegarde, \n");
            exit(EXIT_FAILURE);
         }

         else{
            fprintf(Fpointer,"%d %d %d \n",nb_nodes,game_nb_max_bridges,nb_dir);
            int compteur;

            printf("Sauvegarde en cours ..\n");
            system("sleep 1");

            for (compteur = 0; compteur < nb_nodes; compteur++){
               int x = get_x(game_node(g,compteur));
               int y = get_y(game_node(g,compteur));
               fprintf(Fpointer, "%d %d %d \n",x,y,get_required_degree(game_node(g,compteur)));}}

         printf("(100%%) Le jeu a été sauvegardé dans save/game_default\n");
         fclose(Fpointer);
         system("sleep 2");}

      else if (choix == 4){

         FILE *Fpointer;
         Fpointer = fopen("save/sauvegarde.txt","w");

         if(Fpointer == NULL){
            printf("Impossible d'ouvrir le fichier de sauvegarde, \n");
            exit(EXIT_FAILURE);
         }
         
         else{
            fprintf(Fpointer,"%d %d %d \n",nb_nodes,game_nb_max_bridges,nb_dir);
            int compteur;

            printf("Sauvegarde en cours ..\n");
            system("sleep 1");
            
            if (nb_dir == 4){
               for (compteur = 0; compteur < nb_nodes; compteur++){
                  int x = get_x(game_node(g,compteur));
                  int y = get_y(game_node(g,compteur));
                  fprintf(Fpointer,"%d %d %d %d %d %d %d \n",x,y,get_required_degree(game_node(g,compteur)), get_degree_dir(g,compteur,NORTH), get_degree_dir(g,compteur,WEST),get_degree_dir(g,compteur,SOUTH),get_degree_dir(g,compteur,EAST) );
               }
            }
            if (nb_dir == 8){
               for (compteur = 0; compteur < nb_nodes; compteur++){
                  int x = get_x(game_node(g,compteur));
                  int y = get_y(game_node(g,compteur));
                  fprintf(Fpointer, "%d %d %d %d %d %d %d %d %d %d %d \n",x,y,get_required_degree(game_node(g,compteur)), get_degree_dir(g,compteur,NORTH), get_degree_dir(g,compteur,WEST), get_degree_dir(g,compteur,SOUTH), get_degree_dir(g,compteur,EAST), get_degree_dir(g,compteur,NW), get_degree_dir(g,compteur,SW), get_degree_dir(g,compteur,SE), get_degree_dir(g,compteur,NE));
               }
            }
            printf("(100%%) Le jeu a été sauvegardé dans save/sauvegarde.txt\n");
            fclose(Fpointer);
            system("sleep 2");
         }
      }

            
      


      else if (choix == 0)
         return;
      }
         game_print(nb_nodes, g, game_nb_max_bridges, nb_dir);      
      }

      //////////////////////////////FIN MENU /////////////////////////////