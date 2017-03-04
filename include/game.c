#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "node.h"
#include "game.h"


struct game_s{
  int nb_nodes;
  node * nodes;
  int** bridges;
  int nb_max_bridges;
  int nb_dir;
};

enum orientation {HOR = -1, VERT = -2, DIAG_R = -3, DIAG_L = -4};


void max_grid(cgame g, int * max_x, int * max_y){
  node n;
  for(int i = 0; i < g->nb_nodes; i++){
     n = g->nodes[i];
    if(get_x(n) > *max_x){*max_x = get_x(n);}
    if(get_y(n) > *max_y){*max_y = get_y(n);}
  }
}

game new_game (int nb_nodes, node * nodes, int nb_max_bridges, int nb_dir){
  game g = malloc(sizeof(struct game_s));
  if(g == NULL){
    fprintf(stderr, "Not enough memory");
    exit(EXIT_FAILURE);
  }
  g -> bridges = (int**) malloc(nb_nodes * sizeof(int*));
  if(g -> bridges == NULL){
    fprintf(stderr, "Not enough memory");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<nb_nodes; i++){
    g->bridges[i] = (int*)malloc(nb_dir*sizeof(int));
    if(g -> bridges[i] == NULL){
      fprintf(stderr, "Not enough memory");
      exit(EXIT_FAILURE);
    }
  }
  node * g_nodes = malloc(nb_nodes * sizeof(node));
  if(g_nodes == NULL){
    fprintf(stderr, "Not enough memory");
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < nb_nodes; i++){
    g_nodes[i] = new_node(get_x(nodes[i]),get_y(nodes[i]), get_required_degree(nodes[i]));
  }
  for(int i = 0; i < nb_nodes; i++){
    for(int j =0; j < nb_dir; j++){
      g->bridges[i][j] = 0;
    }
  }

  g -> nb_nodes = nb_nodes;
  g -> nodes = g_nodes;
  g -> nb_max_bridges = nb_max_bridges;
  g -> nb_dir = nb_dir;
  return g;
}

void delete_game (game g){
  for(int i = 0; i < g->nb_nodes; i++){
    free(g->bridges[i]);}
  free(g->bridges);
  for(int i = 0; i < g->nb_nodes; i++){
    delete_node(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
}

game copy_game (cgame g_src){
   game g = new_game(g_src -> nb_nodes, g_src -> nodes, g_src -> nb_max_bridges, g_src -> nb_dir);
   for(int i = 0; i < g_src -> nb_nodes; i++){
      for(int j = 0; j < g_src -> nb_dir; j++){
         g->bridges[i][j] = g_src -> bridges[i][j];
      }
   }
  return g;
}

int game_get_node_number (cgame g, int x, int y){
   node *nodes = g->nodes;
   for (int i=0; i<(g->nb_nodes) ; i++){
      int xt = get_x(nodes[i]);
      int yt = get_y(nodes[i]);
      if (xt == x && yt == y)
         return i;
   }
   return -1;
}

int get_neighbour_dir (cgame g, int node_num, dir d){
   node *T = g->nodes;
   int x = get_x(T[node_num]);
   int y = get_y(T[node_num]);
   int max_x = 0;
   int max_y = 0;
   max_grid(g, &max_x, &max_y);
    switch(d){
      case NORTH :
        y++;
        while(game_get_node_number(g,x,y)==-1 && y < max_y)
          y++;
        return game_get_node_number(g,x,y);
        break;

      case SOUTH:
        y--;
        while(game_get_node_number(g,x,y)==-1 && y>=0)
          y--;
        return game_get_node_number(g,x,y);
        break;

      case WEST:
        x--;
        while(game_get_node_number(g,x,y)==-1 && x>=0)
          x--;
        return game_get_node_number(g,x,y);
        break;

      case EAST:
        x++;
        while(game_get_node_number(g,x,y)==-1 && x < max_x)
          x++;
        return game_get_node_number(g,x,y);
        break;

      case NW :
        y++;
        x--;
        while(game_get_node_number(g,x,y)==-1 && y < max_y){
          y++;
          x--;
        }
        return game_get_node_number(g,x,y);
        break;

      case SW:
        y--;
        x--;
        while(game_get_node_number(g,x,y)==-1 && y>=0){
          y--;
          x--;
        }
        return game_get_node_number(g,x,y);
        break;

      case SE:
        y--;
        x++;
        while(game_get_node_number(g,x,y)==-1 && y>=0){
          y--;
          x++;
        }
        return game_get_node_number(g,x,y);
        break;

      case NE:
        y++;
        x++;
        while(game_get_node_number(g,x,y)==-1 && x < max_x){
          y++;
          x++;
        }
        return game_get_node_number(g,x,y);
        break;
    default:
      break;
   }
    return -1;

}

int game_nb_nodes (cgame g){
   return g -> nb_nodes;
}

int game_nb_dir (cgame g){
  return g->nb_dir;
}

int game_nb_max_bridges (cgame g){
  return g->nb_max_bridges;
}

node game_node (cgame g, int node_num){
   node *T = g -> nodes;
   return T[node_num];
}

int get_degree (cgame g, int node_num){
  int degree = 0;
  for(int i = 0; i < g->nb_dir; i++){
    degree = degree + g->bridges[node_num][i];
  }
  return degree;
}

void linked_aux(cgame g, int node_number, bool * connex_tab, int cmp){
  if(cmp < g->nb_nodes){
    cmp++;
    connex_tab[node_number] = true;
    if(g->nb_dir == 4){
      for(int d = NORTH; d <= EAST; d++){
        if(get_neighbour_dir(g, node_number, d) != -1 && get_degree_dir(g, node_number, d) > 0){
          linked_aux(g, get_neighbour_dir(g, node_number, d), connex_tab, cmp);
        }
      }
    }
    else if(g->nb_dir == 8){
      for(int d = NORTH; d <= NE; d++){
        if(get_neighbour_dir(g, node_number, d) != -1 && get_degree_dir(g, node_number, d) > 0){
          linked_aux(g, get_neighbour_dir(g, node_number, d), connex_tab, cmp);
        }
      }
    }
  }
}

bool linked(cgame g){
  bool * connex_tab = malloc(g->nb_nodes * sizeof(bool));
  if(connex_tab == NULL){
    fprintf(stderr, "Not enough memory !");
    exit(EXIT_FAILURE);}
  for(int i = 0; i < g->nb_nodes; i++){
    connex_tab[i] = false;
  }
  linked_aux(g, 0, connex_tab, 0);
  for(int i = 0; i < g->nb_nodes; i++){
    if(!connex_tab[i]){
      free(connex_tab);
      return false;
    }
  }
  free(connex_tab);
  return true;
}

bool game_over (cgame g){
   for (int i = 0 ; i<(g->nb_nodes) ; i++){
     int degree = get_degree(g, i);
     if (degree != get_required_degree(game_node(g, i)))
        return false;
   }
   return linked(g);
}

void vector_direction (int* x, int* y, dir d){
   switch (d){
      case NORTH :
         *x = 0;
         *y = 1;
         break;
      case SOUTH :
         *x = 0;
         *y = -1;
         break;
      case EAST :
         *x = 1;
         *y = 0;
         break;
      case WEST :
         *x = -1;
         *y = 0;
         break;
      case NW :
         *x = -1;
         *y = 1;
         break;
      case SW :
         *x = -1;
         *y = -1;
         break;
      case SE :
         *x = 1;
         *y = -1;
         break;
      case NE :
         *x = 1;
         *y = 1;
         break;
   }
}

enum orientation orientation(dir d){
  if(d == NORTH || d == SOUTH){
    return VERT;
  }
  else if(d == EAST || d == WEST){
    return HOR;
  }
  else if(d == SW || d == NE){
    return DIAG_R;
  }
  else{
    return DIAG_L;
  }
}

bool collisions(cgame g, int node_num, dir dest){
  int max_x = 0, max_y = 0, x, y, req_degree, x_v, y_v;
   node n;
   max_grid(g, &max_x, &max_y);
   max_x += 1;
   max_y += 1;
   int ** M = (int**)malloc(((2*max_x) - 1) * sizeof(int*));
   if(M == NULL){
      fprintf(stderr, "Not enough memory !");
      exit(EXIT_FAILURE);
   }
   for(int i = 0; i < (max_x*2) - 1; i++){
      M[i] = calloc(((2*max_y) - 1),  sizeof(int));
      if(M[i] == NULL){
         fprintf(stderr, "Not enough memory !");
         exit(EXIT_FAILURE);
      }
   }
   for(int i = 0; i < g->nb_nodes; i++){
      n = game_node(g, i);
      x = get_x(n);
      y = get_y(n);
      req_degree = get_required_degree(n);
      M[x*2][y*2] = req_degree;
   }
   for(int i = 0; i < g->nb_nodes; i++){
      n = game_node(g, i);
      if(g->nb_dir == 8){
         for(int d = NORTH; d < NE; d++){
            if(get_degree_dir(g, i, d)){
               x = get_x(n)*2;
               y = get_y(n)*2;
               vector_direction(&x_v, &y_v, d);
               while((x+x_v < (2*max_x)-1 && x+x_v >=0) && (y+y_v < (2*max_y)-1 && y+y_v >= 0) && (!(M[x+x_v][y+y_v]))){
                  x = x+x_v;
                  y = y+y_v;
                  M[x][y] = orientation(d);
               }
            }
         }
      }
      else{
         for(int d = NORTH; d < EAST; d++){
            if(get_degree_dir(g, i, d)){
               x = get_x(n)*2;
               y = get_y(n)*2;
               vector_direction(&x_v, &y_v, d);
               while((x+x_v < (2*max_x)-1 && x+x_v >=0) && (y+y_v < (2*max_y)-1 && y+y_v >= 0) && (!(M[x+x_v][y+y_v]))){
                  x = x+x_v;
                  y = y+y_v;
                  M[x][y] = orientation(d);
               }
            }
         }
      }
   }
   n = game_node(g, node_num);
   x = get_x(n)*2;
   y = get_y(n)*2;
   vector_direction(&x_v, &y_v, dest);
   while(M[x+x_v][y+y_v] <= 0){
      x = x + x_v;
      y = y + y_v;
      if(M[x][y] != orientation(dest) && M[x][y] != 0){
         for(int i = 0; i < (2*max_x)-1; i++){
            free(M[i]);
         }
         free(M);
         return false;
      }
   }
   for(int i = 0; i < (2*max_x)-1; i++){
      free(M[i]);
   }
   free(M);
   return true;
}

bool can_add_bridge_dir (cgame g, int node_num , dir d){
   node n = game_node(g, node_num);
   switch(d){
      case NORTH :
         return get_degree(g, node_num) < get_required_degree(n) && g->bridges[node_num][0]<g->nb_max_bridges && get_neighbour_dir(g, node_num, d) != -1 && collisions(g, node_num, d);
         break;

      case SOUTH:
         return get_degree(g, node_num) < get_required_degree(n) && g->bridges[node_num][2]<g->nb_max_bridges && get_neighbour_dir(g, node_num, d) != -1 && collisions(g, node_num, d);
         break;

      case WEST:
         return get_degree(g, node_num) < get_required_degree(n) && g->bridges[node_num][1]<g->nb_max_bridges && get_neighbour_dir(g, node_num, d) != -1 && collisions(g, node_num, d);
         break;

      case EAST:
         return get_degree(g, node_num) < get_required_degree(n) && g->bridges[node_num][3]<g->nb_max_bridges && get_neighbour_dir(g, node_num, d) != -1 && collisions(g, node_num, d);
         break;

      case NW :
         return get_degree(g, node_num) < get_required_degree(n) && g->bridges[node_num][4]<g->nb_max_bridges && get_neighbour_dir(g, node_num, d) != -1 && collisions(g, node_num, d);
         break;

      case SW:
         return get_degree(g, node_num) < get_required_degree(n) && g->bridges[node_num][5]<g->nb_max_bridges && get_neighbour_dir(g, node_num, d) != -1 && collisions(g, node_num, d);
         break;

      case SE:
         return get_degree(g, node_num) < get_required_degree(n) && g->bridges[node_num][6]<g->nb_max_bridges && get_neighbour_dir(g, node_num, d) != -1 && collisions(g, node_num, d);
         break;

      case NE:
         return get_degree(g, node_num) < get_required_degree(n) && g->bridges[node_num][7]<g->nb_max_bridges && get_neighbour_dir(g, node_num, d) != -1 && collisions(g, node_num, d);
         break;
      default:
         break;
   }
   return false;
}

void add_bridge_dir (game g, int node_num, dir d){
   int neighbour = get_neighbour_dir(g, node_num, d);
   switch(d){
      case NORTH :
         g->bridges[node_num][0]++;
         g->bridges[neighbour][2]++;
         break;

      case SOUTH:
         g->bridges[node_num][2]++;
         g->bridges[neighbour][0]++;
         break;

      case WEST:
         g->bridges[node_num][1]++;
         g->bridges[neighbour][3]++;
         break;

      case EAST:
         g->bridges[node_num][3]++;
         g->bridges[neighbour][1]++;
         break;

       case NW :
         g->bridges[node_num][4]++;
         g->bridges[neighbour][6]++;
         break;

      case SW:
         g->bridges[node_num][5]++;
         g->bridges[neighbour][7]++;
         break;

      case SE:
         g->bridges[node_num][6]++;
         g->bridges[neighbour][4]++;
         break;

      case NE:
         g->bridges[node_num][7]++;
         g->bridges[neighbour][5]++;
         break;
   default:
     break;
   }
}

void del_bridge_dir (game g, int node_num, dir d){
   int neighbour = get_neighbour_dir(g, node_num, d);
   switch(d){
   case NORTH :
     if(g->bridges[node_num][0]>0){
       g->bridges[node_num][0]--;
       g->bridges[neighbour][2]--;}
     break;

   case SOUTH:
     if(g->bridges[node_num][2]>0){
       g->bridges[node_num][2]--;
       g->bridges[neighbour][0]--;
     }
     break;

   case WEST:
     if(g->bridges[node_num][1]>0){
       g->bridges[node_num][1]--;
       g->bridges[neighbour][3]--;
     }
     break;

   case EAST:
     if(g->bridges[node_num][3]>0){
       g->bridges[node_num][3]--;
       g->bridges[neighbour][1]--;
     }
     break;

   case NW :
     if(g->bridges[node_num][4]>0){
       g->bridges[node_num][4]--;
       g->bridges[neighbour][6]--;}
     break;

   case SW:
     if(g->bridges[node_num][5]>0){
       g->bridges[node_num][5]--;
       g->bridges[neighbour][7]--;
     }
     break;

   case SE:
     if(g->bridges[node_num][6]>0){
       g->bridges[node_num][6]--;
       g->bridges[neighbour][4]--;
     }
     break;

   case NE:
     if(g->bridges[node_num][7]>0){
       g->bridges[node_num][7]--;
       g->bridges[neighbour][5]--;
     }
     break;
   default:
     break;
   }
}



int get_degree_dir (cgame g, int node_num, dir d){
  switch(d){
  case NORTH :
    return g->bridges[node_num][0];
    break;

  case SOUTH:
    return g->bridges[node_num][2];
    break;

  case WEST:
    return g->bridges[node_num][1];
    break;

  case EAST:
    return g->bridges[node_num][3];
    break;

  case NW :
    return g->bridges[node_num][4];
    break;

  case SW:
    return g->bridges[node_num][5];
    break;

  case SE:
    return g->bridges[node_num][6];
    break;

  case NE:
    return g->bridges[node_num][7];
    break;
  default:
    break;
   }
  return -1;
}
