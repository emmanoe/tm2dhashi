#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "node.h"

                                                //FONCTION DIVERSE//

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

                                         // PARTIE PRINTF INSTANCE DE JEU//
void game_print(int nb_nodes,game g, node nodes[]){ /* Affiche l'instance de jeu créé */ // RAJOUT DE game g !!
   int exit = 0;
   int ivoisini=-1;
   //int numnode;
   int *pc=&exit;
   //int *p_n=&numnode;
   int *p_i=&ivoisini;
   int choix =0;
   int coordx=0; //Ajout de ponts entre 2 nodes
   int coordy=0;

   printf("\n");
   while (exit!=1){
      printf("choix=%d",choix);
      int max = max_x_y(nb_nodes, nodes);
      printf("     -----------------------------------------------------------------  \n");
      printf("                                 HASHIWOKAKERO                          \n");
      printf("\n");
      for (int y = max ; y>=0; y--){ // for moins de test et plus maniable" rajout des nodes vides"
         for (int x = 0; x<=max; x++){
            int i = 0;
            if (game_get_node_number(g,x,y)!=-1){
               i = game_get_node_number(g,x,y);
               printf(" %d ",get_required_degree(nodes[i]));
            }
            else
               printf("   ");


               //PARTIE PONT

            if (game_get_node_number(g,x,y)!=-1){
               if (get_degree(g,game_get_node_number(g,x,y))>= 1){
                  if  (get_degree(g,game_get_node_number(g,x,y)) ==1)
                     if (choix == 2 || choix == 1){{
                        if (game_get_node_number(g,x,y)!=ivoisini){
                           printf("-----"); //si degré >= 1 on dessine le pont
                           *p_i = get_neighbour_dir(g,i,EAST);
                        }
                        else printf("     ");
                        }
                     }
                  if (get_degree(g,game_get_node_number(g,x,y))==2)
                     if (choix ==2 ||choix ==  1){{
                           *p_i = get_neighbour_dir(g,i,EAST);
                           if (game_get_node_number(g,x,y)!=ivoisini){
                              printf("=====");
                           }
                           else printf("    5");
                        }
                     }
               }
               else if (get_degree(g,game_get_node_number(g,x,y))==0)
               printf("     "); //suivi d'espace pour l'esthétique
            }
            else printf("     ");
         }
         *p_i = -1; // on réinitialise ivoisini
         printf("\n");
         printf("\n");
      }
      //printf("\n");

                                                 // PARTIE INTERACTION//

      printf(" Choisissez une action 1:ajouter 2:supprimer 0:quitter\n ");
      scanf("%d",&choix);
      if (choix == 1){
         printf(" veuiller entrer la coordonnée \"x\" de l'île:\n ");
         scanf("%d",&coordx);
         printf(" veuiller entrer la coordonnée \"y\" de l'île:\n ");
         scanf("%d",&coordy);
         printf(" veuiller choisir une direction 1:OUEST 2:EST 3:NORD 4:SUD \n ");
         scanf("%d",&choix);
         int node_num = game_get_node_number(g,coordx,coordy); // A revoir pour la position
         printf("node numero %d\n",node_num);


         if ( can_add_bridge_dir(g,node_num,EAST)){
            add_bridge_dir(g,node_num,EAST);

         }
      }
      if (choix ==0)
         *pc = 1;
      //         dessiner_bridge(g,node_num,droite);
   }
}




   //  printf("degree %d = %d\n",node_num,get_degree(g, node_num));
   //}



/*    int ivoisin= get_neighbour_dir(g,node_num,d); /\*index du noeud voisin **\/ */
/*    int xvoisin = get_y( nodes[ivoisin]); */
/*    int xnode = get_y(nodes[node_num]); */
/*    for (int i=xnode+1;i<xvoisin;i++) */

                                     //MAIN//

int main(void){
   int tnodes [7][3]= {{0,0,3},{0,1,5},{0,2,2},{1,1,1},{1,2,2},{2,0,2},{2,2,3}};

   node nodes[7];
   for (int i=0;i<7;i++)
      nodes[i]= new_node(tnodes[i][0],tnodes[i][1],tnodes[i][2]);
   game g = new_game(7, nodes);
   //game_over(g);
   //game_node(g, 1);
   game_print(7,g, nodes);
   //add_bridge(g,nodes);
   //max_x_y(nb_nodes,nodes);
   //delete_game(g);
   return EXIT_SUCCESS;
}
