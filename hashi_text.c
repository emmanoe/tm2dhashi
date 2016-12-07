#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "node.h"



                                                //FONCTION DIVERSE//

/*
 * Description: system est une fonction qui execute une "shell built-in command" commande intégrée dans le shell
 * Idéal pour effacer les données sur l'interpréteur de commande avant de lancer notre programme.
 * Parameter :
 * char *command la commande à executer.
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

   switch (i){

      case 1:

      return WEST;
      break;

   case 2:

      return EAST;
      break;


   case 3:

      return NORTH;
      break;

   case 4:

      return SOUTH;
      break;

      default:
         return EXIT_FAILURE;

   }

}






/*
 * Description: printspace affiche les espace dans l'instance du jeu afin de représenter les trous laissé par les noeuds inexistant aux coordonnées x,y
 */
void printspace(game g,int x,int y, int nb_nodes, node nodes[]){ // Print de l'espace pour représenter les pont inexistant !

   int max = max_x_y(nb_nodes, nodes);

   if (get_degree_dir(g,game_get_node_number(g,x-1,y),EAST)==0){

      /* printf("CCCC"); */
      for (int i=0;i<5;i++) // Pour i infèrieur à la distance entre deux noeuds qui ont des coordonnées consécutive sur x

         printf(" "); // On affiche le pont

      int ind = x+1; // Méthode pour détecter les trous entre 2 noeuds

      if (ind < max &&  game_get_node_number(g,ind,y) == -1){

         while (game_get_node_number(g,ind,y) == -1 )

            ind++; // on compte le nombres de trous entre deux noeuds

         for (int i=0;i<(5*(ind-1))+(3*(ind-1));i++) // Fonction linéaire 5 est le coefficient de proportionalité de de la formule par rapport à 'ind'

            printf("C"); // On comble ces trous

      }

      if ( game_get_node_number(g,x+1,y) != -1)

         printf("   "); //suivi d'espace pour l'esthétique

   }

}



                                         // PARTIE PRINTF INSTANCE DE JEU//
/*
 * Description: game_print afiche le jeu créé sur le l'interpréteur de commande
 * Parameters:
 * -nb_nodes le nombre de noeuds dans le jeu
 * -g le jeu à afficher
 * -nodes[] le tableau de noeuds
 */
void game_print(int nb_nodes,game g, node nodes[], int game_nb_max_bridges){ /* Affiche l'instance de jeu créée */

   int choix =0; int choix2=0; int coordx=0; int coordy=0; int node_num=0; // variables nécéssaire lors intéraction avec la machine

   char msg[256] = " "; // tableau de caractère qui stockera les messages d'erreurs

   printf("\n");



  debut: //étiquette début pour éviter de quitter le jeu soudainement !!

   while (1){
      system("clear");

      int max = max_x_y(nb_nodes, nodes);
      printf("- Configuration du jeu -\n");

      printf("\n");

      printf("Nombre maximum de ponts entre 2 îles : %d\n",game_nb_max_bridges);

      printf("\n");

      printf("Nombre de directions pris en comptes : 8 \n");

      printf("\n");

      printf("     -----------------------------------------------------------------  \n");

      printf("                                 HASHIWOKAKERO                          \n");

      printf("\n");

      for (int y = max ; y>=0; y--){ // Boucle for utilisée car moins de test par rapport au while et plus maniable "ex:rajout des nodes vides"

         for (int x = 0; x<=max; x++){

            if (game_get_node_number(g,x,y)!= -1){ // Si le noeud existe

               printf(" %d ",get_required_degree(nodes[game_get_node_number(g,x,y)])); // On affiche son degré







                 //PARTIE PONT HORIZENTAL


               if ( get_degree_dir(g,game_get_node_number(g,x,y),EAST) == 1 ){ // Si il y a 1 pont à ce noeud vers l'EST et que Le nombre
                  // de ponts maximum n'est pas dépassé

                  for (int i=0;i<5;i++) // Pour i infèrieur à la distance entre deux noeuds qui ont des coordonnées consécutive sur x

                     printf("-"); // On affiche le pont

                  int ind = x+1; // Méthode pour détecter les trous entre 2 noeuds

                  if (ind < max &&  game_get_node_number(g,ind,y) == -1){

                     while (game_get_node_number(g,ind,y) == -1 )

                        ind++; // on compte le nombres de trous entre deux noeuds

                     for (int i=0;i<(5*(ind-1))+(3*(ind-1));i++) // Fonction linéaire 5 est le coefficient de proportionalité de de la formule par rapport à 'ind'

                        printf("-"); // On comble ces trous

                  }

               }




               else if ( get_degree_dir(g,game_get_node_number(g,x,y),EAST) == 2 )  { // Si il y a 2 ponts à ce noeud vers l'EST

                  for (int i=0;i<5;i++) // Pour i infèrieur à la distance entre deux noeuds qui ont des coordonnées consécutive sur x

                     printf("="); // On affiche un le pont

                  int ind = x+1; // Méthode pour détecter les trous entre 2 noeuds

                  if (ind < max &&  game_get_node_number(g,ind,y)==-1 ){

                     while (game_get_node_number(g,ind,y)==-1)


                        ind++;

                     for (int i=0;i<(5*(ind-1))+(3*(ind-1));i++) // 5 = nombre de trait entre de node avec leur  consecutif, ind represente le nombre de fois a repeter l'operation

                        printf("=");

                  }

               }

               else if ( get_degree_dir(g,game_get_node_number(g,x,y),EAST) == 3 )  { // Si il y a 2 ponts à ce noeud vers l'EST

                  for (int i=0;i<5;i++) // Pour i infèrieur à la distance entre deux noeuds qui ont des coordonnées consécutive sur x

                     printf("*"); // On affiche un le pont

                  int ind = x+1; // Méthode pour détecter les trous entre 2 noeuds

                  if (ind < max &&  game_get_node_number(g,ind,y)==-1 ){

                     while (game_get_node_number(g,ind,y)==-1)


                        ind++;

                     for (int i=0;i<(5*(ind-1))+(3*(ind-1));i++) // 5 = nombre de trait entre de node avec leur  consecutif, ind represente le nombre de fois a repeter l'operation

                        printf("*");

                  }

               }

               else if ( get_degree_dir(g,game_get_node_number(g,x,y),EAST) == 4 )  { // Si il y a 2 ponts à ce noeud vers l'EST

                  for (int i=0;i<5;i++) // Pour i infèrieur à la distance entre deux noeuds qui ont des coordonnées consécutive sur x

                     printf("#"); // On affiche un le pont

                  int ind = x+1; // Méthode pour détecter les trous entre 2 noeuds

                  if (ind < max &&  game_get_node_number(g,ind,y)==-1 ){

                     while (game_get_node_number(g,ind,y)==-1)


                        ind++;

                     for (int i=0;i<(5*(ind-1))+(3*(ind-1));i++) // 5 = nombre de trait entre de node avec leur  consecutif, ind represente le nombre de fois a repeter l'operation

                        printf("#");

                  }

               }


               if (get_degree_dir(g,game_get_node_number(g,x,y),EAST)==0)
                  printf("     "); //suivi d'espace pour l'esthétique

            }


            else if(x>0 && game_get_node_number(g,x-1,y) != -1){ // Si le noeud n'existe pas pour (x,y) on affiche un espace

               if (game_get_node_number(g,x,y-1) != -1 || game_get_node_number(g, x, y+1) != -1){

                  if (game_get_node_number(g,x,y-1) != -1 && get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH) == 1) // On verifie qu'il existe un noeud aux deux etrémités
                                                                                                                         // du pont et si ils ont un pont qui passe par le vide
                     printf(" |");

                  if (game_get_node_number(g,x,y-1) != -1 && get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH) == 2)

                     printf(" H");

                  if (game_get_node_number(g,x,y-1) != -1 && get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH) == 3)

                     printf(" *");

                  if (game_get_node_number(g,x,y-1) != -1 && get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH) == 4)

                     printf(" #");

                  else printspace(g,x,y,nb_nodes,nodes);// On print l'espace si on tombe sur le cas par default

               }

            }
         }




         printf("\n");

               //PARTIE PONT VERTICAL | ou H

         for (int x =0;x<=max;x++){

            if (game_get_node_number(g,x,y) != -1 && game_get_node_number(g,x,y-1) != -1){ // Si le noeud et son voisin du bas existe

               if (get_degree_dir(g,game_get_node_number(g,x,y),SOUTH) == 1 || get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH) == 1){

                  printf(" |");
                  printf("      ");

               }
               else if (get_degree_dir(g,game_get_node_number(g,x,y),SOUTH) == 2){

                  printf(" H");
                  printf("      ");

               }

               else if (get_degree_dir(g,game_get_node_number(g,x,y),SOUTH) == 3){

                  printf(" *");
                  printf("      ");

               }

               else if (get_degree_dir(g,game_get_node_number(g,x,y),SOUTH) == 4){

                  printf(" #");
                  printf("      ");

               }

               else if (get_degree_dir(g,game_get_node_number(g,x,y),SOUTH)==0){

                  printf("        ");

               }

            }

            else if (game_get_node_number(g,x,y) != -1 && game_get_node_number(g,x,y-1) == -1){ // On dessine le pont qui traverse le vide laissé par le noeud inexistant

               if ((get_degree_dir(g,game_get_node_number(g,x,y),SOUTH)==1 )){

                  printf(" |");

                  printf("      ");

               }

               if ((get_degree_dir(g,game_get_node_number(g,x,y),SOUTH) == 2 )){

                  printf(" H");

                  printf("      ");

               }

               if ((get_degree_dir(g,game_get_node_number(g,x,y),SOUTH) == 3 )){

                  printf(" *");

                  printf("      ");

               }

               if ((get_degree_dir(g,game_get_node_number(g,x,y),SOUTH) == 4 )){

                  printf(" #");

                  printf("      ");

               }

               else printf("      ");

            }

            else if (game_get_node_number(g,x,y) == -1){ // On print l'espace si on tombe sur le cas par default

               if ( game_get_node_number(g,x,y-1) != -1 && (get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH)==1 ) )
                  printf("   |");

               if ( game_get_node_number(g,x,y-1) != -1 && (get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH)==2 ) )
                  printf("   H");

               if ( game_get_node_number(g,x,y-1) != -1 && (get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH)==3 ) )
                  printf("   *");

               if ( game_get_node_number(g,x,y-1) != -1 && (get_degree_dir(g,game_get_node_number(g,x,y-1),NORTH)==4 ) )
                  printf("   #");

            }

         }



         printf("\n");

      }





                                                 // PARTIE INTERACTION//

      printf("%s\n",msg); // Print le message d'erreur
      sprintf(msg," "); // Vide le tableau de message d'erreur

      printf(" Choisissez une action 1:ajouter 2:supprimer 0:quitter\n ");

      scanf("%d",&choix);

      if (choix ==0)
         break;

      if (choix == 1){
         printf(" veuillez entrer la coordonnée \"x\" de l'île:\n ");
         scanf("%d",&coordx);

         printf(" veuillez entrer la coordonnée \"y\" de l'île:\n ");
         scanf("%d",&coordy);

         if (game_get_node_number(g,coordx,coordy)==-1){
            //printf("\n");
            sprintf(msg,"impossible d'ajouter de pont à cet endroit !\n");
            goto debut;
         }

         printf(" veuillez choisir une direction 1:OUEST 2:EST 3:NORD 4:SUD \n ");
         scanf("%d",&choix2);


         //AJOUTER BRIDGES
         node_num = game_get_node_number(g,coordx,coordy); // A revoir pour la position

         if ( can_add_bridge_dir(g,node_num,intostr(choix2)) && get_degree_dir(g,node_num,intostr(choix2)) < game_nb_max_bridges ){ // On vérifie les condition nécéssaire
            add_bridge_dir(g,node_num,intostr(choix2));

         }
         else if (!(can_add_bridge_dir(g,node_num,intostr(choix2)))) {
            //printf("\n");
            sprintf(msg,"Vous ne pouvez pas ajouter de pont vers cette direction.\n");
            //printf("\n");
         }

         else if ( get_degree_dir(g,node_num,intostr(choix2)) >= game_nb_max_bridges ){


            //printf("\n");
            sprintf(msg,"Vous ne pouvez pas ajouter de pont vers cette direction car le nombre de ponts autorisé a été atteint .\n");
            //printf("\n");
         }

      }
                                                 // SOUS MENU INTERACTION //


      // SUPPRIMER BRIDGES !
      if (choix == 2){
        sup: // étiquette pour revenir à l'option supprimer sans préciser à nouveau que l'on veut supprimer un pont
         printf("Quelles sont les coordonnées 1:précédent 2:autres\n");
         scanf("%d",&choix);

         if (choix==1 && get_degree_dir(g,node_num,intostr(choix2))>0){
            del_bridge_dir(g,node_num,intostr(choix2));
         }

         else if (choix == 1 && get_degree(g,node_num)==0){
            //printf("\n");
            sprintf(msg,"Il n'y a rien à supprimer");
            //printf("\n");
         }

         if (choix== 2 && get_degree(g,node_num)>0){
            printf(" veuiller entrer la coordonnée \"x\" de l'île:\n ");
            scanf("%d",&coordx);

            printf(" veuiller entrer la coordonnée \"y\" de l'île:\n ");
            scanf("%d",&coordy);

            printf(" veuiller choisir une direction 1:OUEST 2:EST 3:NORD 4:SUD \n ");
            scanf("%d",&choix2);

            node_num = game_get_node_number(g,coordx,coordy);

            if (game_get_node_number(g,coordx,coordy)==-1 || get_degree_dir(g,node_num,intostr(choix2))<=0){
               //printf("\n");
               sprintf(msg,"impossible de supprimer de pont à cet endroit !\n");
               goto debut;
            }

            else if(game_get_node_number(g,coordx,coordy)!=-1 && get_degree_dir(g,node_num,intostr(choix2))!=0){
               del_bridge_dir(g,node_num,intostr(choix2));
            }
         }
         else if (choix == 2 && get_degree(g,node_num)==0){
            //printf("\n");
            sprintf(msg,"Il n'y a rien à supprimer");
            //printf("\n");
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

   game g = new_game(7, nodes,4,4);
   game_print(7,g, nodes,4);

   if(game_over(g)){
      printf("\n");
      printf("\n");
      printf("GAME OVER                            \n");
   }
   else if(!game_over(g)){
      printf("\n");
      printf("YOU LOSE !\n");
   }

   delete_game(g);
   return EXIT_SUCCESS;
}
