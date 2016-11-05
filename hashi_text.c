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

dir intostr(int i){ //Fonction qui traduit le choix int en dir str !
   dir d;
   if (i==1)
      d =WEST;
   if (i==2)
      d= EAST;
   if (i==3)
      d= NORTH;
   if (i==4)
      d= SOUTH;
return d;

}

                                         // PARTIE PRINTF INSTANCE DE JEU//
void game_print(int nb_nodes,game g, node nodes[]){ /* Affiche l'instance de jeu créé */ // RAJOUT DE game g !!
   int exit = 0;
   //int numnode;
   int *pc=&exit;
   //int *p_n=&numnode;
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
            else if(x>0 && game_get_node_number(g,x-1,y)!=-1) //Factoriser ce code en fonction car répété à ligne 77 !!!
               if (get_degree_dir(g,game_get_node_number(g,x-1,y),EAST)==0)
                  printf("   ");


               //PARTIE PONT

            if (game_get_node_number(g,x,y)!=-1){ //on teste si le noeud est existant !
               if (get_degree_dir(g,game_get_node_number(g,x,y),EAST)==1)/*choix == 2 || choix == 1*/{
                        // if (game_get_node_number(g,x,y)!=ivoisini){
                              if (x+1<max &&  game_get_node_number(g,x+1,y)==-1 )
                                 printf("-------------"); //si degré >= 1 on dessine le pont
                              else printf("-----");
               }

               if (get_degree_dir(g,game_get_node_number(g,x,y),EAST)==2)
               {{
                     if (x+1<max &&  game_get_node_number(g,x+1,y)==-1 )
                        printf("=============");
                     else
                        printf("=====");
                  }
                     //else printf("    5");
                  }

                  else if (get_degree_dir(g,game_get_node_number(g,x,y),EAST)==0)
               printf("     "); //suivi d'espace pour l'esthétique
            }
            else if (game_get_node_number(g,x,y)==-1){
               if(x>0 && game_get_node_number(g,x-1,y)!=-1)
                  if (get_degree_dir(g,game_get_node_number(g,x-1,y),EAST)==0)
                     printf("     ");
            }
         }
         printf("\n");
         for (int x =0;x<max;x++){
            if (game_get_node_number(g,x,y)!=-1 && game_get_node_number(g,x,y-1)!=-1){
               if (get_degree_dir(g,game_get_node_number(g,x,y),SOUTH)==1 || get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH)==1){
                  printf(" |");
                  printf("      ");
               }
               else if (get_degree_dir(g,game_get_node_number(g,x,y),SOUTH)==2){
                  printf(" H");
                  printf("      ");
               }
               else if (get_degree_dir(g,game_get_node_number(g,x,y),SOUTH)==0){
                  printf("        ");
               }
            }
            else if (game_get_node_number(g,x,y)==-1)
               printf("      ");
         }
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


         if ( can_add_bridge_dir(g,node_num,intostr(choix))){
            add_bridge_dir(g,node_num,intostr(choix));

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
   game_print(7,g, nodes);;
   //add_bridge(g,nodes);
   //max_x_y(nb_nodes,nodes);
   //delete_game(g);
   return EXIT_SUCCESS;
}
