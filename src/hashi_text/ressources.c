#include <stdlib.h>
#include <stdio.h>
#include "ressources.h"

int VAR_1=1;
char VAR_2[]="deux";
int* ptr = &VAR_1;

int choix =0; 
int choix2=0; 
int coordx=0; 
int coordy=0; 
int node_num=0; 
int var = 0; // variables nécéssaire lors intéraction avec la machine
char msg[256] = " "; // tableau de caractère qui stockera les messages d'erreurs	