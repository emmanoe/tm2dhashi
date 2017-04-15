#ifndef FUN_H
#define FUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "node.h"

/* **************************************************************** */


int system(const char *command);

int max_x(int nb_nodes, game g);

int max_y(int nb_nodes, game g);

int max2 (int maxx, int maxy);

dir intostr(int i);

/* **************************************************************** */

#endif
