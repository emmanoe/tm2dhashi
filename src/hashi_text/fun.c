#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int max_x(int nb_nodes, game g){

   int max=0;

   for (int i = 0;i<nb_nodes;i++){

      if (get_x(game_node(g,i))>max)
         max = get_x(game_node(g,i));
   }

   return max;
}

int max_y(int nb_nodes, game g){

   int max=0;

   for (int i = 0;i<nb_nodes;i++){
      if (get_y(game_node(g,i))>max)
         max = get_y(game_node(g,i));
   }

   return max;
}

int max2 (int maxx, int maxy){
   int max = 0;
   if (maxx > maxy)
      max = maxx;
   if (maxx < maxy)
      max = maxy;
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
