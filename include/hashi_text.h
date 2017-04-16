#ifndef HASHI_TEXT_H
#define HASHI_TEXT_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

/* **************************************************************** */
/*
 * Description: game_print afiche le jeu créé sur l'interpréteur de commande
 * Parameters:
 * *g le jeu à afficher
 */

void game_print(int nb_nodes,game g, int game_nb_max_bridges, int nb_dir);


/* **************************************************************** */

#endif