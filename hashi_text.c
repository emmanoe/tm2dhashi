#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "node.h"



                                                //FONCTION DIVERSE//

/*
 * Description: system est une fonction qui execute une "shell built-in command" commande intégrée dans le shell
 * Idéal pour faire effacer effacer les données sur l'interpréteur de commande avant de l'ancer notre programme.
 * Parameter :
 * char *command la commande en question.
 * Return: Un entier qui interprète l'état de l'execution de la commande.
 */

int system(const char *command); //  Execute a sell built-in cmd !




/*
 * Description : max_x_y est une fonction qui mémorise la valeur de la coordonnée x ou y la plus grande parmi tous les noeuds du tableau de noeud nodes[].
 * Ça sert de point d'arrêt pour la boucle qui dessine l'instance de jeu.
 * Parameters:
 * -nb_nodes le nombre de noeuds dans le jeu
 * -nodes[] le tableau de noeuds du jeu
 * Return: la coordonnée la plus grande parmi toute les autres
 */
int max_x_y(int nb_nodes, node nodes[]){
   int max=0;
   for (int i = 0;i<nb_nodes;i++){
      if (get_x(nodes[i])>max)
         max = get_x(nodes[i]);
      if (get_y(nodes[i])>max)
         max = get_y(nodes[i]);
   }
   return max;
}






/*
 * Description: intostr est une fonction qui converti un int choisi entre 1 et 4 et le transforme en un des 4 points cardinaux
 * Quand l'utilisateur intéragi avec le jeu il entre des entiers pour représenter ces choix cela vont alors être convertis
 * Return: Une des 4 points cardinaux
 */
dir intostr(int i){ //Fonction qui converti le choix format int en une direction format str !
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






/*
 * Description: printspace affiche les espace dans l'instance du jeu afin de représenter les trous laissé par les noeuds inexistant aux coordonnées x,y
 */
void printspace(game g,int x,int y){ // Print de l'espace pour représenter les pont inexistant !
   if (get_degree_dir(g,game_get_node_number(g,x-1,y),EAST)==0)
      printf("    ");
}


                                         // PARTIE PRINTF INSTANCE DE JEU//
/*
 * Description: game_print afiche le jeu créé sur le l'interpréteur de commande
 * Parameters:
 * -nb_nodes le nombre de noeuds dans le jeu
 * -g le jeu à afficher
 * -nodes[] le tableau de noeuds
 */
void game_print(int nb_nodes,game g, node nodes[]){ /* Affiche l'instance de jeu créé */
   int choix =0; //Choix variables nécéssaire lors intéraction avec la machine
   int choix2=0;
   int coordx=0;  //Stock des valeurs de coordonnées lors de l'intéraction
   int coordy=0;
   int node_num=0;



   printf("\n");
  debut: //étiquette début pour éviter de quitter le jeu soudainement !!
   while (1){
      int max = max_x_y(nb_nodes, nodes);
      printf("     -----------------------------------------------------------------  \n");
      printf("                                 HASHIWOKAKERO                          \n");
      printf("\n");
      for (int y = max ; y>=0; y--){ // boucle for car moins de test par rapport au while et plus maniable "ex:rajout des nodes vides"
         for (int x = 0; x<=max; x++){
            int i = 0;
            if (game_get_node_number(g,x,y)!=-1){ // Si le noeud existe
               i = game_get_node_number(g,x,y);
               printf(" %d ",get_required_degree(nodes[i]));
            }
            else if(x>0 && game_get_node_number(g,x-1,y)!=-1) // Si le noeud n'existe pas pour (x,y) on affiche un espace
               printspace(g,x,y);



               //PARTIE PONT

            if (game_get_node_number(g,x,y)!=-1){ //on teste si le noeud est existant !
               if (get_degree_dir(g,game_get_node_number(g,x,y),EAST)==1){ // Si il y a un pont à ce noeud
                  if (x+1<max &&  game_get_node_number(g,x+1,y)==-1 ) // mais si jamais on tombe sur un trou (-1)
                     printf("-------------"); // On affiche un plus long pont
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
                  printspace(g,x,y);
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


                                                 // PARTIE INTERACTION//

      printf(" Choisissez une action 1:ajouter 2:supprimer 0:quitter\n ");
      scanf("%d",&choix);

      if (choix ==0)
         break;

      if (choix == 1){
         printf(" veuiller entrer la coordonnée \"x\" de l'île:\n ");
         scanf("%d",&coordx);

         printf(" veuiller entrer la coordonnée \"y\" de l'île:\n ");
         scanf("%d",&coordy);

         if (game_get_node_number(g,coordx,coordy)==-1){
            printf("\n");
            printf("impossible d'ajouter de pont à cet endroit !\n");
            goto debut;
         }

         printf(" veuiller choisir une direction 1:OUEST 2:EST 3:NORD 4:SUD \n ");
         scanf("%d",&choix2);

         node_num = game_get_node_number(g,coordx,coordy); // A revoir pour la position

         if ( can_add_bridge_dir(g,node_num,intostr(choix2))){
            add_bridge_dir(g,node_num,intostr(choix2));

         }
         else if (!(can_add_bridge_dir(g,node_num,intostr(choix2)))){
            printf("\n");
            printf("Vous ne pouvez pas ajouter de pont vers cette direction.\n");
            printf("\n");
         }
      }
                                                 // SOUS MENU INTERACTION //
      if (choix == 2){
        sup: // étiquette pour revenir à l'option supprimer sans préciser à nouveau que l'on veut supprimer un pont
         printf("Quelles sont les coordonnées 1:précédent 2:autres\n");
         scanf("%d",&choix);

         if (choix==1 && get_degree_dir(g,node_num,intostr(choix2))>0){
            del_bridge_dir(g,node_num,intostr(choix2));
         }

         else if (choix == 1 && get_degree(g,node_num)==0){
            printf("\n");
            printf("Il n'y a rien à supprimer");
            printf("\n");
         }

         if (choix== 2 && get_degree(g,node_num)>0){
            printf(" veuiller entrer la coordonnée \"x\" de l'île:\n ");
            scanf("%d",&coordx);

            printf(" veuiller entrer la coordonnée \"y\" de l'île:\n ");
            scanf("%d",&coordy);

            printf(" veuiller choisir une direction 1:OUEST 2:EST 3:NORD 4:SUD \n ");
            scanf("%d",&choix2);

            if (game_get_node_number(g,coordx,coordy)==-1 || (get_degree(g,game_get_node_number(g,coordx,coordy)!=-1 && get_degree_dir(g,node_num,intostr(choix2)<=0)))){
               printf("\n");
               printf("impossible de supprimer de pont à cet endroit !\n");
               goto debut;
            }

            del_bridge_dir(g,node_num,intostr(choix2));
         }
         else if (choix == 2 && get_degree(g,node_num)==0){
            printf("\n");
            printf("Il n'y a rien à supprimer");
            printf("\n");
         }
         else goto sup;
      }
   }
}






                                     //MAIN//

int main(void){
   system("clear");  // execute a shel built-in cmd !!
   int tnodes [7][3]= {{0,0,3},{0,1,5},{0,2,2},{1,1,1},{1,2,2},{2,0,2},{2,2,3}};
   node nodes[7]; // Tableau de nodes
   for (int i=0;i<7;i++)
      nodes[i]= new_node(tnodes[i][0],tnodes[i][1],tnodes[i][2]); //On rempli le tableau de node !
   game g = new_game(7, nodes);
   game_print(7,g, nodes);;
   delete_game(g);
   return EXIT_SUCCESS;
}
