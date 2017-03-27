#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h" 

//Code cellule permettant l'affichage
#define code_E -1   //Code concernant une cellule vide
#define code_N 0    //Code concernant une cellule noeud
#define code_P 1    //Code concernant une cellule ayant un pont verticale

struct bridge_s
{
    int node_dep;//Pont de départ
    dir direction;//Direction de départ
};

typedef struct bridge_s bridge;

struct PrintTab
{
    int node_num;//Numéro du noeud responsable de la cellule
    int code;//Code d'affichage d'une cellule
} ;

typedef struct PrintTab* printtab;

struct game_s
{
    unsigned int nb_node;//Nombre de noeud présent sur le plateau
    unsigned int nb_bridges;//Nombre de pont maximum du plateau
    int max_x;
    int max_y;
    int lvl;
    printtab* tab_Cross;//Tableau d'affichage du plateau
    int current_size;//Nombre de pont présent sur le plateau
    int nb_max_bridges;//Nombre maximum de pont entre les noeuds
    int nb_dir;//Nombre de direction disponible
    node* nodes;//Tableau de noeuds présent
    bridge* bridges;//Tableau de ponts présent
};

void taille_tab(node *nodes,int* pt_x, int* pt_y, int nb_nodes)
{
    (*pt_x)=-1;
    (*pt_y)=-1;
    for(int i= 0; i < nb_nodes; i++)
    {
        if((*pt_x) < get_x(nodes[i]) )
            (*pt_x) = get_x(nodes[i]);
        if((*pt_y) < get_y(nodes[i]) )
            (*pt_y) = get_y(nodes[i]);
    }
    (*pt_x)+=1;
    (*pt_y)+=1;
}

//La fonction inverse renvoie la même direction ( opt = true ) ou l'opposé ( opt = false )
dir inverse(dir dir)
{
    //opt = true : on renvoie la bonne direction, l'inverse de la direction sinon
    if( (!(dir%2) && !(dir%4)) || ( dir%2 && !((dir-1)%4)) )
        return dir+2;
    else
        return dir-2;
}

game new_game (int nb_nodes, node *nodes, int nb_max_bridges, int nb_dir )//OPT
{
    int tot_req_deg = 0;
    game g = (game) malloc (sizeof(struct game_s));//On alloue de la mémoire à la structure de jeu
    if( g == NULL)//Vérification de si l'allocation a eu lieu
    {
        fprintf(stderr, "new_game : Fail of allocation of pointer game\n");
        exit(EXIT_FAILURE);
    }
    taille_tab(nodes, &g->max_x, &g->max_y,nb_nodes);
    g->tab_Cross = (printtab*) malloc (sizeof(printtab)*g->max_y);//On alloue de la mémoire à la structure de jeu
    if( g->tab_Cross == NULL)//Vérification de si l'allocation a eu lieu
    {
        fprintf(stderr, "new_game : Fail of allocation of pointer tab_Cross\n");
        exit(EXIT_FAILURE);
    }
    struct PrintTab setup = {code_E,code_E};
    for( int i=0; i < g->max_y; i++)
    {
        g->tab_Cross[i] = (printtab) malloc (sizeof(struct PrintTab)*g->max_x);//On alloue de la mémoire à la structure de jeu
        if( g->tab_Cross[i] == NULL)//Vérification de si l'allocation a eu lieu
        {
            fprintf(stderr, "new_game : Fail of allocation case %d of pointer tab_Cross\n",i);
            exit(EXIT_FAILURE);
        }
        for( int j=0; j < g->max_x; j++)
            g->tab_Cross[i][j] = setup;

    }
    g->nodes = (node*) malloc (sizeof(node*)*nb_nodes);//On alloue nb_nodes emplacements de mémoire pour le tableau de nodes de la structure de jeu
    if( g->nodes == NULL)//Vérification de si l'allocation a eu lieu
    {
        fprintf(stderr, "new_game : Fail of allocation of pointer node\n");
        exit(EXIT_FAILURE);
    }
    g->nb_node = nb_nodes;//On initialise le nombre de nodes du jeu
    for(unsigned int i = 0 ; i < nb_nodes ; ++i)//On somme le nombre total de degrés requis && on initialise le tableau de node
    {
        g->nodes[i] = new_node(get_x(nodes[i]), get_y(nodes[i]), get_required_degree(nodes[i]));
        g->tab_Cross[get_y(nodes[i])][get_x(nodes[i])].node_num=i;
        g->tab_Cross[get_y(nodes[i])][get_x(nodes[i])].code=code_N;
        tot_req_deg += get_required_degree(nodes[i]);
    }
    g->nb_bridges = tot_req_deg/2;//On initialise le nombre de ponts du jeu
    g->bridges = (bridge*) malloc (sizeof(struct bridge_s)*g->nb_bridges);//On alloue g->nb_bridges emplacements de mémoire pour le tableau de ponts de la structure de jeu
    if( g->bridges == NULL)//Vérification de si l'allocation a eu lieu
    {
        fprintf(stderr, "new_game : Fail of allocation of pointer bridge\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<g->nb_bridges; i++)
    {
        g->bridges[i].node_dep = code_E;//Pont de départ
        g->bridges[i].direction=code_E;
    }
    g->current_size = 0;//On initialise le nombre de ponts de la structure de jeu à 0
    g->nb_max_bridges = nb_max_bridges;
    g->nb_dir = nb_dir;
    return g;
}

int game_nb_dir (cgame g)//OPT
{
    return g->nb_dir;
}

int game_nb_max_bridges (cgame g)//OPT
{
    return g->nb_max_bridges;
}

int game_nb_nodes(cgame g)
{
    //On renvoie le contenu du champs nb_node de la structure cgame de la variable g
    return g->nb_node;
}

game copy_game(cgame g_src)
{
    game new = new_game(g_src->nb_node, g_src->nodes, g_src->nb_max_bridges, g_src->nb_dir);

    new->lvl=g_src->lvl;
    new->current_size=g_src->current_size;
    for(int i=0; i<g_src->nb_bridges; i++)
    {
        new->bridges[i] = g_src->bridges[i];
    }
    for(int i=0 ; i<g_src->max_y ; i++)
    {
        for(int j=0 ; j<g_src->max_x ; j++)
        {
            new->tab_Cross[i][j]=g_src->tab_Cross[i][j];
        }
    }
    return new;
}

node game_node(cgame g, int node_num)
{
if( node_num >= 0 && node_num < game_nb_nodes(g)) 
	{
    return g->nodes[node_num];
}
return NULL;
}

void delete_game(game g)
{
    for(int i = 0; i < g->max_y; i++)
        free(g->tab_Cross[i]);
    free(g->tab_Cross);
    for(int i = 0; i < game_nb_nodes(g); i++)
        free(game_node (g, i));
    free(g->nodes);
    free(g->bridges);
    free(g);
}

void nodeOK( cgame g, int index,  int max_colo,  bool passage[game_nb_nodes (g)][max_colo])
{
    if( game_nb_dir(g) <= 4 && (passage[index][1] && passage[index][2] && passage[index][3] && passage[index][4] ))//On vérifie si toutes les directions de la node index ont été vérifiées
        passage[index][0] = true;
    //Toutes les directions sont vérifiées donc on valide ( assigne true ) à la node pour éviter de revérifier
    else	 if( game_nb_dir(g) > 4 && (passage[index][1] && passage[index][2] && passage[index][3] && passage[index][4] && passage[index][7] && passage[index][8] && passage[index][9] && passage[index][10] ))
        passage[index][0] = true;
}

void bridgesOK(cgame g, int index, int max_colo,  bool passage[game_nb_nodes (g)][max_colo])
{
    int nb_bridge = 0;
    for( int i = 0; i< g->nb_bridges && g->current_size >0; i++)
    {
        if( index == g->bridges[i].node_dep || (g->bridges[i].node_dep > -1 && index == get_neighbour_dir(g, g->bridges[i].node_dep, g->bridges[i].direction) ))//On recherche le nombre de ponts qui lient la node index
            nb_bridge++;
    }
    if( nb_bridge == get_required_degree(game_node (g, index)))//On vérifie si le nombre de ponts requis est correct
    {
        passage[index][6] = true;
    }
}

bool g1Bridge( cgame g, int n1, int n2, dir d)
{
    for(int i=0; i < g->nb_bridges && g->current_size >0; i++)
    {
        if((  g->bridges[i].node_dep == n1 && get_neighbour_dir(g, g->bridges[i].node_dep, g->bridges[i].direction) == n2 && g->bridges[i].direction == d)||( g->bridges[i].node_dep > -1 &&  get_neighbour_dir(g, g->bridges[i].node_dep, g->bridges[i].direction) == n1 && g->bridges[i].node_dep == n2 && g->bridges[i].direction == inverse(d)))//On vérifie si les nodes n1 et n2 ont au moins un pont dans le tableau de ponts
            return true;
    }
    return false;
}

void verifDirection(cgame g, int num_colo, int index, dir d,int max_colo,  bool passage[game_nb_nodes (g)][max_colo], int dInv);

void connexion_nodes_aux(node n, cgame g, int max_colo,  bool passage[game_nb_nodes (g)][max_colo])
{
    int index = 0 ;
    for( int i = 0; !(game_node (g, i) == n) && i < game_nb_nodes (g); i++, index ++); //On récupère l'index de la node.
    bridgesOK(g,index, max_colo, passage);  //On vérifie si le nombre de ponts de la node index est respecté
    if( ! passage[index][0] )//On vérifie toutes les directions de la node index
    {

        passage[index][5] = true;//On vérifie qu'elle a été rencontrée lors du traitement
        verifDirection(g, 1, index, NORTH, max_colo, passage, 3);//puts("N");
        verifDirection(g, 2, index, EAST, max_colo, passage, 4);//puts("E");
        verifDirection(g, 3, index, SOUTH,  max_colo, passage, 1);//puts("S");
        verifDirection(g, 4, index, WEST,  max_colo,passage, 2);//puts("W");
        if(game_nb_dir(g) > 4)
        {
            verifDirection(g, 7, index, NE,  max_colo,passage, 9);
            verifDirection(g, 8, index, SE,  max_colo, passage, 10);
            verifDirection(g, 9, index, SW,  max_colo,passage, 7);
            verifDirection(g, 10, index, NW,  max_colo,passage, 8);
        }
        nodeOK(g,index, max_colo,passage);
    }
}

void verifDirection(cgame g, int num_colo, int index, dir d,int max_colo,  bool passage[game_nb_nodes (g)][max_colo], int dInv)
{
    int neighbour_num, neighbour_index=0;
    if( ! passage[index][num_colo] )//On vérifie si la direction n'a pas déjà été vérifiée
    {
        neighbour_num = get_neighbour_dir (g, index, d); //on récupère l'indice du voisin dans la direction d
        if (neighbour_num > -1 && g1Bridge( g, index, neighbour_num, d ) )//On vérifie si il y a un voisin puis si il y a au moins un pont
        {
            for( int i = 0; !(game_node (g, i) == game_node (g, neighbour_num)) && i < game_nb_nodes (g); i++, neighbour_index ++); //On récupère l'index du voisin
            passage[neighbour_index][dInv] = true;//On vérifie le pont ayant permis le passage de la récursion
            passage[index][num_colo] = true;//On vérifie que la direction num_colo a été vérifiée pour la node d'indice index lors du traitement
            connexion_nodes_aux( game_node (g, neighbour_num), g,  max_colo,passage); //On relance le traitement dans la node voisine
        }
        else//Il n'y a pas de voisin donc la direction num_colo est vérifiée
            passage[index][num_colo] = true;
    }
}

/*===============*/

bool game_over(cgame g)
{
    for(int i = 0 ; i <game_nb_nodes (g); ++i)//On somme le nombre total de degrés requis && on initialise le tableau de node
    {
        if(get_required_degree(game_node(g,i))- get_degree(g,i) > 0)
            return false;
    }
    int nb_node_meet = 0;
    int nb_pt = 0;
    int col = ( (game_nb_dir(g) > 4) ? 11 : 7);
    //On crée le tableau de vérification
    bool verifMeet[game_nb_nodes (g)][col];

    for( int i  = 0; i < game_nb_nodes (g); i++)
        for( int j = 0; j < col; j++)//On initialise tout le tableau Ã  false
            verifMeet[i][j]=false;
    connexion_nodes_aux(game_node(g,0),g, col, verifMeet);//On lance toutes les vérifications à partir de la node index 0
    for(int i=0; i<game_nb_nodes (g) && verifMeet[i][5] ; i++, nb_node_meet++);//On compte le nombre de nodes rencontrÃ©es lors du traitement
    for(int i=0; i<game_nb_nodes (g) && verifMeet[i][6] ; i++, nb_pt++);//On compte le nombre de nodes ayant rempli leur nombre de ponts lors du traitement
    if( nb_node_meet == game_nb_nodes (g) && nb_pt == game_nb_nodes (g) )//La connexité et le nombre de ponts requis pour chaque node sont bons donc la partie est finie
        return true;
    else
        return false;
}

bool cross_bridge(cgame g, int node_num,dir d)
{
if( node_num >= 0 && node_num < game_nb_nodes(g) && d >= 0 && d < game_nb_dir(g) ) 
	{
    int acc_x=0,acc_y=0;//Accumulateur de déplacement sur les axes
    if( d == NORTH || d == SOUTH )
    {
        acc_y =( (d==NORTH) ? 1 : -1);//On assigne la direction verticale et le code cellule
        acc_x =0;
    }
    else if( d == WEST || d == EAST )//On assigne la direction horizontale et le code cellule
    {
        acc_y =0;
        acc_x =( (d==EAST) ? 1 : -1);
    }
    else if( d == NW || d == SE )//On assigne la direction de l diagonale décroissante et le code cellule
    {
        acc_y =( (d==NW) ? 1 : -1);
        acc_x =( (d==NW) ? -1 : 1);
    }
    else if( d == SW || d == NE )//On assigne la direction de l diagonale croissante et le code cellule
    {
        acc_y =( (d==NE) ? 1 : -1);
        acc_x =( (d==NE) ? 1 : -1);
    }
    for(int x=get_x(game_node (g, node_num))+acc_x,y=get_y(game_node (g, node_num))+acc_y; g->tab_Cross[y][x].code != code_N; x+=acc_x, y+=acc_y)
    {
        //On vérifie si il y a un croisement avec un code cellule différent du code assigné
        if((g->tab_Cross[y][x].code== code_P || (g->tab_Cross[y+acc_y][x].code == code_P && g->tab_Cross[y][x+acc_x].code == code_P && g->tab_Cross[y+acc_y][x+acc_x].code != code_N)) && get_degree_dir(g,node_num,d) == 0 )
        {
            return true;
        }
    }
}
    return false;
}

bool can_add_bridge_dir(cgame g, int node_num, dir d)
{
   int nb_bridge_n1=0,nb_bridge_n2=0;
    if( ( node_num >= 0 && node_num < game_nb_nodes(g) && d >= 0 && d < game_nb_dir(g) ) &&( get_neighbour_dir(g, node_num, d) >= 0 ))//On vérifie si il y a un voisin
    {
        nb_bridge_n1=get_degree_dir(g,node_num,d);//On récuperer le degrée actuel de la node dans une direction
        nb_bridge_n2=get_degree_dir(g,get_neighbour_dir(g, node_num, d),inverse(d));//On récuperer le degrée actuel de la node voisine dans une direction
        //On vérifie qu'il y a des ponts dans le tableau puis on regarde si il y a un croisement en fonction des coordonnées saisie
        if( cross_bridge(g,node_num,d) )//Il y a un croisement de pont
        {
            return false;
        }
        else if(get_required_degree(game_node (g, node_num))==get_degree(g, node_num))//Le nombre maximum de ponts est atteint
        {
            return false;
        }
        else if( (get_required_degree(game_node (g, get_neighbour_dir(g, node_num, d)))==get_degree(g, get_neighbour_dir(g, node_num, d))))// Le nommbre maximum de ponts du voisin est atteint
        {
            return false;
        }
        else if( nb_bridge_n1 >= game_nb_max_bridges(g) )//Le nombre maximum de ponts est atteint dans la direction choisie pour la node choisie
        {
            return false;
        }
        else if( nb_bridge_n2 >=  game_nb_max_bridges(g))//Le nombre maximum de ponts est atteint dans la direction choisie pour la node voisine de la node choisie
        {
            return false;
        }
        else//Aucune condition n'est vérifiée donc le pont est possible
            return true;
    }
    //Dans le cas où il n'y pas de voisin
    return false;
}

void add_bridge_dir (game g, int node_num, dir d)
{
	if( node_num >= 0 && node_num < game_nb_nodes(g) && d >= 0 && d < game_nb_dir(g) ) 
	{
    int i= 0 ;
    for(; i<g->nb_bridges && g->current_size>0 && g->bridges[i].node_dep != code_E; i++);//On recherche 2 emplacements de libre pour placer nos ponts

    //On ajoute le pont
    g->bridges[i].node_dep = node_num;
    g->bridges[i].direction = d;

    g->current_size++;;//On incrémente le nombre de ponts du tableau de ponts

    int acc_x=0,acc_y=0;//Accumulateur de déplacement sur les axes
    if( d == NORTH || d == SOUTH )
    {
        acc_y =( (d==NORTH) ? 1 : -1);//On assigne la direction verticale et le code cellule

    }
    else if( d == WEST || d == EAST )//On assigne la direction horizontale et le code cellule
    {
        acc_x =( (d==EAST) ? 1 : -1);
    }
    else if( d == NW || d == SE )//On assigne la direction de l diagonale décroissante et le code cellule
    {
        acc_y =( (d==NW) ? 1 : -1);
        acc_x =( (d==NW) ? -1 : 1);
    }
    else if( d == SW || d == NE )//On assigne la direction de l diagonale croissante et le code cellule
    {
        acc_y =( (d==NE) ? 1 : -1);
        acc_x =( (d==NE) ? 1 : -1);
    }
    //if(get_degree_dir(g,node_num,d) == 0 )
    {
        for(int x=get_x(game_node (g, node_num))+acc_x,y=get_y(game_node (g, node_num))+acc_y; g->tab_Cross[y][x].code != code_N; y+=acc_y,x+=acc_x)
        {
            g->tab_Cross[y][x].code = code_P;
            g->tab_Cross[y][x].node_num = node_num;
        }
    }
	}
}

int game_get_node_number (cgame g, int x, int y)
{
    if( ( x >= 0 && x < g->max_x && y >= 0 && y < g->max_y ) && g->tab_Cross[y][x].code == code_N )
        return g->tab_Cross[y][x].node_num;
    return -1;
}

int get_degree_dir (cgame g, int node_num, dir d)
{
if( node_num >= 0 && node_num < game_nb_nodes(g) && d >= 0 && d < game_nb_dir(g) ) 
	{
    int count=0;
    for(int i = 0; i < g->nb_bridges && g->current_size >0 ; i++)
    {
        if(( g->bridges[i].node_dep == node_num && g->bridges[i].direction == d )||( g->bridges[i].node_dep > -1 &&  get_neighbour_dir(g, g->bridges[i].node_dep, g->bridges[i].direction) == node_num && g->bridges[i].direction == inverse(d) ))//On compte le nombre de ponts de la node dans le tableau de ponts dans la direction d
            count++;
    }
    return count;
}
return -1;
}

int get_degree (cgame g, int node_num)//OPT
{
if( node_num >= 0 && node_num < game_nb_nodes(g)) 
	{
    int count=0;
    for(int i = 0; i<game_nb_dir(g); i++)
    {
        count+=get_degree_dir(g,node_num,i);
    }
    return count;
}
return -1;
}

int get_neighbour_dir( cgame g, int node_num, dir d)
{
if( node_num >= 0 && node_num < game_nb_nodes(g) && d >= 0 && d < game_nb_dir(g) ) 
	{
    int acc_x=0,acc_y=0;//Accumulateur de déplacement sur les axes
    if( d == NORTH || d == SOUTH )
    {
        acc_y =( (d==NORTH) ? 1 : -1);//On assigne la direction verticale et le code cellule
        acc_x =0;
    }
    else if( d == WEST || d == EAST )//On assigne la direction horizontale et le code cellule
    {
        acc_y =0;
        acc_x =( (d==EAST) ? 1 : -1);
    }
    else if( d == NW || d == SE )//On assigne la direction de l diagonale décroissante et le code cellule
    {
        acc_y =( (d==NW) ? 1 : -1);
        acc_x =( (d==NW) ? -1 : 1);
    }
    else if( d == SW || d == NE )//On assigne la direction de l diagonale croissante et le code cellule
    {
        acc_y =( (d==NE) ? 1 : -1);
        acc_x =( (d==NE) ? 1 : -1);
    }
    for( int x = get_x( game_node(g, node_num))+acc_x, y=get_y( game_node(g, node_num))+acc_y; x >= 0 && x < g->max_x && y >= 0 && y < g->max_y; x+=acc_x,y+=acc_y)
    {
        if( game_get_node_number(g,x,y) > -1 )//On s'arrête au moment où on trouve un voisin
            return game_get_node_number(g,x,y);
    }
}
    //On renvoie -1 si il n'y a pas de voisin
    return -1;
}

void del_bridge_dir (game g, int node_num, dir d)
{
if( node_num >= 0 && node_num < game_nb_nodes(g) && d >= 0 && d < game_nb_dir(g) ) 
	{
    int x = get_x(game_node(g,node_num));
    int y = get_y(game_node(g,node_num));
    int acc_x=0,acc_y=0;//Accumulateur de déplacement sur les axes
    if( d == NORTH || d == SOUTH )
    {
        acc_y =( (d==NORTH) ? 1 : -1);//On assigne la direction verticale et le code cellule
        acc_x =0;
    }
    else if( d == WEST || d == EAST )//On assigne la direction horizontale et le code cellule
    {
        acc_y =0;
        acc_x =( (d==EAST) ? 1 : -1);
    }
    else if( d == NW || d == SE )//On assigne la direction de l diagonale décroissante et le code cellule
    {
        acc_y =( (d==NW) ? 1 : -1);
        acc_x =( (d==NW) ? -1 : 1);
    }
    else if( d == SW || d == NE )//On assigne la direction de l diagonale croissante et le code cellule
    {
        acc_y =( (d==NE) ? 1 : -1);
        acc_x =( (d==NE) ? 1 : -1);
    }
    for(int i = 0; i < g->nb_bridges && g->current_size >0; i++)//On recherche les ponts dans le tableau de ponts et on les supprime
    {
        if(( g->bridges[i].node_dep == node_num && g->bridges[i].direction == d )||( g->bridges[i].node_dep > -1 &&  get_neighbour_dir(g, g->bridges[i].node_dep, g->bridges[i].direction) == node_num && g->bridges[i].direction == inverse(d) ))
        {
            if(i < g->current_size-1)
            {
                g->bridges[i]= g->bridges[g->current_size-1];
                g->bridges[g->current_size-1].node_dep = code_E;
                g->bridges[g->current_size-1].direction = code_E;
            }
            else
            {
                g->bridges[i].node_dep = code_E;
                g->bridges[i].direction = code_E;
            }
            g->current_size--;    //On décrémente le compteur de ponts
            for(x=x+acc_x,y=y+acc_y; g->tab_Cross[y][x].code != code_N; y+=acc_y,x+=acc_x)
            {
                g->tab_Cross[y][x].code = code_E;
                g->tab_Cross[y][x].node_num = code_E;
            }
            return;
        }
    }
}
}
