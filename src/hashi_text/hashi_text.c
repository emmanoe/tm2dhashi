#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "node.h"
#include "hashi_solve.h"
#include "fun.h"
#include "menu.h"
#include "load.h"
#include "affichage.h"
#include "ressources.h"
                                     
/* **************************************************************** */


void game_print(int nb_nodes,game g, int game_nb_max_bridges, int nb_dir){ /* Affiche l'instance de jeu créé */

   char **t; 
   t = malloc(nb_nodes * sizeof(char *));//allocation dynamique d'un tableau a deux dimensions
   int maxx = max_x(nb_nodes, g);
   int maxy = max_y(nb_nodes, g);
   int max = max2(maxx,maxy);

   for(int i = 0; i <= maxx*2; i++){
   	t[i] = malloc(maxy*2 * sizeof(char));
      for(int j = 0; j <= maxy*2; j++){
         t[i][j] = ' ';}}
        

      ////////////////////////NOUVELLE PARTIE //////////////////////////

  debut: //étiquette début pour éviter de quitter le jeu à chaque fois !!


   while (1){
      system("clear");
      

      char texte[12] = "";

      printf("- Configuration du jeu -\n");

      printf("\n");

      printf("Nombre de ponts maximum entre 2 îles : %d\n",game_nb_max_bridges);

      printf("\n");

      printf("Nombre de directions autorisées : %d \n", game_nb_dir(g));

      printf("\n");

      for (int s = 0 ; s< (max/3); s ++)
      	printf(" %5s","");

      printf("     -----------------------------------------------------------------  \n");

      for (int s = 0 ; s< (max/3); s ++)
      	printf(" %5s","");

      printf("                                 HASHIWOKAKERO                          \n");

      printf("\n");

      for (int y = maxy ; y>=0; y--){
         for (int x = 0; x<=maxx; x++){ 
               if (game_get_node_number(g,x,y) != -1){
                     sprintf(texte,"%d", get_required_degree(game_node(g,game_get_node_number(g,x,y)))); 
                     t[x*2][y*2]=texte[0];
                     }}}
      
      for (int y = maxy*2 ; y>=0; y--){ 
         for (int x = 0; x<=maxx*2; x++){
            printf(" %c ",t[x][y]);
            }
         printf("\n");
      }



               //PARTIE PONT HORIZENTAL

               
               

                                                 // PARTIE INTERACTION//


      printf(" %s\n",msg); // Print le message d'erreur
      sprintf(msg," \n"); // Vide le tableau de message d'erreur

      printf(" Choisissez une action 1:ajouter 2:supprimer 0:menu\n ");

      scanf("%d",&choix);

      if (choix == 0){
         menu(game_nb_nodes(g), g, game_nb_max_bridges, game_nb_dir(g));
         break;
      }

      if (choix == 1){
         printf("\n");
         printf(" veuillez entrer la coordonnée \"x\" de l'île:\n ");
         scanf("%d",&coordx);

         printf("\n");
         printf(" veuillez entrer la coordonnée \"y\" de l'île:\n ");
         scanf("%d",&coordy);

         if (game_get_node_number(g,coordx,coordy)==-1){
            //printf("\n");
            sprintf(msg,"impossible d'ajouter de pont à cet endroit !\n");
            goto debut;
         }

         printf("\n");
         printf(" veuillez choisir une direction 1:OUEST 2:EST 3:NORD 4:SUD 5:NW 6:SW 7:SE 8:NE \n ");
         scanf("%d",&choix2);


         //AJOUTER BRIDGES
         node_num = game_get_node_number(g,coordx,coordy); // A revoir pour la position

         if ( can_add_bridge_dir(g,node_num,intostr(choix2)) && get_degree_dir(g,node_num,intostr(choix2)) < game_nb_max_bridges && choix2 < nb_dir ){ // On vérifie les condition nécéssaire
            add_bridge_dir(g,node_num,intostr(choix2));
            draw_bridge(g,node_num,t,game_node(g,node_num), intostr(choix2));

         }
         else if (!(can_add_bridge_dir(g,node_num,choix2)) || choix2 > nb_dir) {

            sprintf(msg,"Vous ne pouvez pas ajouter de pont vers cette direction.\n");

         }

         else if ( get_degree_dir(g,node_num,intostr(choix2)) >= game_nb_max_bridges ){



            sprintf(msg,"Vous ne pouvez pas ajouter de pont vers cette direction car le nombre de ponts autorisé a été atteint .\n");

         }

      }
                                                 // SOUS MENU INTERACTION //


      // SUPPRIMER BRIDGES !
      if (choix == 2){
        sup: // étiquette pour revenir à l'option supprimer sans préciser à nouveau que l'on veut supprimer un pont

         printf("\n");

         printf("Quelles sont les coordonnées 1:précédent 2:autres\n");

         scanf("%d",&choix);

         if (choix==1 && get_degree_dir(g,node_num,intostr(choix2))>0){
            del_bridge_dir(g,node_num,intostr(choix2));
         }

         else if (choix == 1 && get_degree(g,node_num)==0){

            sprintf(msg,"Il n'y a rien à supprimer");

         }

         if (choix== 2 && get_degree(g,node_num)>0){
            printf("\n");

            printf(" veuiller entrer la coordonnée \"x\" de l'île:\n ");

            scanf("%d",&coordx);

            printf("\n");

            printf(" veuiller entrer la coordonnée \"y\" de l'île:\n ");
            scanf("%d",&coordy);

            printf("\n");

            printf(" veuiller choisir une direction 1:OUEST 2:EST 3:NORD 4:SUD 5:NW 6:SW 7:SE 8:NE \n ");
            scanf("%d",&choix2);

            node_num = game_get_node_number(g,coordx,coordy);

            if (game_get_node_number(g,coordx,coordy)==-1 || get_degree_dir(g,node_num,intostr(choix2)) <= 0){

               sprintf(msg,"impossible de supprimer de pont à cet endroit !\n");

               goto debut;
            }

            else if(game_get_node_number(g,coordx,coordy)!=-1 && get_degree_dir(g,node_num,intostr(choix2))!=0){
               del_bridge_dir(g,node_num,intostr(choix2));

            }

         }

         else if (choix == 2 && get_degree(g,node_num)==0){

            sprintf(msg,"Il n'y a rien à supprimer");

         }
         else goto sup;
      }
      if(game_over(g)){
      printf("\n");
      printf("\n");
      printf("Félicitation vous avez gagné               \n");
      system("sleep 2");
      break;
   }
   }
}








                                     //MAIN//

int main(void){
   system("clear");  // execute a shel built-in cmd !!

   game g = load_default_game("map/game_medium.txt");
   menu(game_nb_nodes(g), g, game_nb_max_bridges(g), game_nb_dir(g));   

   if(!game_over(g)){
      printf("\n");
      printf("YOU LOSE !\n");
   }

   delete_game(g);
   return EXIT_SUCCESS;
}