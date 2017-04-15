#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "node.h"


void draw_bridge(game g, int node_num, char **t, node a, dir d){
int x = get_x(a);
	int y = get_y(a);
	int h = 0;
	int v = 0;
		switch(d){
		case NORTH:
			v=1;
		break;
		case EAST:
			h=1;
		break;
		case SOUTH:
			v=-1;
		break;
		case WEST:
			h=-1;
		break;
		case NW:
			v=1;
			h=-1;
			break;
		case NE:
			v=1;
			h=1;
			break;
		case SW:
			v=-1;
			h=-1;
			break;
		case SE:
			v=-1;
			h=1;
			break;
	}

	x+=h;
	y+=v;

	while(!(t[x][y]>48 && t[x][y]<57)){ //dans la table ascii : 48 et 57 -> 0 et 9 
		if(t[x][y] == ' ' && v != 0 && h ==0)
			t[x][y] = '|';
		else if(t[x][y] == '|' && v != 0)
			t[x][y]='H';

		if(t[x][y] == ' ' && h != 0 && v == 0)
			t[x][y] = '-';
		else if(t[x][y] == '-' && h != 0)
			t[x][y]='=';

		x+=h;
		y+=v;
	}


}