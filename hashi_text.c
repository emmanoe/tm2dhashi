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

void game_print(int nb_nodes,game g, node nodes[]){ /* Affiche l'instance de jeu créé */ // RAJOUT DE game g !!
   int exit = 0;
   int degre=0;
   int numnode;
   int *pc=&exit;
   int *p_n=&numnode;
   int *p_d=&degre;
   int choix =0;
   int coordx=0; //Ajout de ponts entre 2 nodes
   int coordy=0;

   printf("\n");
   while (exit!=1){
      int max = max_x_y(nb_nodes, nodes);
      printf("     -----------------------------------------------------------------  \n");
      printf("                                 HASHIWOKAKERO                            ");
      printf("\n");
      printf("\n");

      for (int y = max ; y>=0; y--){
         for (int x = 0; x<=max; x++){
            int i = 0;


            while (((get_x(nodes[i])!=x)||(get_y(nodes[i])!=y))&&(i<nb_nodes)){ // on vérifie si le x et le y des nodes correspondent aux x et y du de la grille
               i++;
            }

            if (i<nb_nodes){printf(" %d ", get_required_degree(nodes[i]));// si oui on print le node
               if ((degre >= 1 && y == 0 && i ==0 )){ //Parti pont

                  if (degre == 1)
                        printf("-------------"); //si degré >= 1 on dessine le pont

                  if (degre==2)
                     printf("=============");

               }
               else printf("     "); //suivi d'espace pour l'esthétique
            }
            else if (degre ==0)
               printf("        ");  // sinon on print " "
         }
         printf("\n");
         printf("\n");
      }
      printf("\n");



      printf(" Choisissez une action 1:ajouter 2:supprimer 0:quitter\n ");
      scanf("%d",&choix);
      if (choix == 1){
         printf(" veuiller entrer la coordonnée \"x\" de l'île:\n ");
         scanf("%d",&coordx);
         printf(" veuiller entrer la coordonnée \"y\" de l'île:\n ");
         scanf("%d",&coordy);
         printf(" veuiller choisir une direction 1:WEST 2:EAST 3:NORTH 4:SOUTH \n ");
         scanf("%d",&choix);
         int node_num = game_get_node_number(g,coordx,coordy); // A revoir pour la position
         printf("node numero %d\n",node_num);

         if ( can_add_bridge_dir(g,node_num,EAST)){
            add_bridge_dir(g,node_num,NORTH);
            *p_d = get_degree(g,node_num);
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
