#ifndef _GAME_H_
#define _GAME_H_
#include <stdbool.h>
#include "node.h"

/**
 * @file game.h
 *
 * @brief This file describes the board of a  hashiwokakero game, the state of a game and all functions needed to manipulate it.
 **/

/**
 * @enum dir_e
 * @brief The enumeration of possible directions of an edge
 **/
typedef enum dir_e {NORTH, WEST, SOUTH, EAST, NW, SW, SE, NE} dir;


/**
 * @struct game_s
 * @brief The state of the game is described by the set of nodes and all the bridges already built.
 * The lower left corner has coordinates (0,0).
 *
 * cgame is a pointer toward a constant game.
 * That means that it is not possible to modify the game using this pointer.
 * See also: http://www.geeksforgeeks.org/const-qualifier-in-c/
 * See also this more technical discussion: http://stackoverflow.com/questions/8504411/typedef-pointer-const-weirdness
 **/
typedef struct game_s* game;
typedef const struct game_s* cgame;


/**
 * @brief Create a new game given a set of nodes.
 * The nodes of the created game are copies of the ones given as argument.
 * @param nb_nodes number of nodes of g
 * @param nodes array of nodes. T
 * @param maximal number of bridges allowed between two nodes of the game
 * @param number of directions allowed in the game. The possible values for this parameter are 4 or 8.
 * @return a pointer toward the generated game
 **/
game new_game (int nb_nodes, node *nodes, int nb_max_bridges, int nb_dir);

/**
 * @brief Destroy the game and free allocated memory
 * @param g the game to destroy
 **/
void delete_game (game g);

/**
 * @brief Clone the game g_src
 * @param g_src the game to clone
 * @return the clone of g_src
 **/
game copy_game (cgame g_src);

/**
 * @brief Return the number of nodes of the game g
 */
int game_nb_nodes (cgame g);

/**
 * @brief Return the number direction of the game g
 */
int game_nb_dir (cgame g);

/**
 * @brief Return the number max of bridges in the game g
 */
int game_nb_max_bridges (cgame g);


/**
 * @brief Return the node of g with number num
 * @param node_num the number of the node. This value must be between 0 and game_nb_nodes(g)-1.
 **/
node game_node (cgame g, int node_num);

/**
 * @brief Test if the game is over.
 * @return true if all the constraints are satisfied
 **/
bool game_over (cgame g);

/**
 * @brief Test if it is possible to add a bridge to node of index node_num in direction d such that
 *   1) it doesn't degenarate a crossing with another bridge
 *   2) the number of bridges in that direction remains smaller our equal to 2.
 **/
bool can_add_bridge_dir (cgame g, int node_num, dir d);


/**
 * @brief Add a bridge from node of index node_num in direction d.
 * @pre the addition of the bridge must be possible (i.e. can_add_bridge_dir(g, node_num_d) == 0).
 **/
void add_bridge_dir (game g, int node_num, dir d);


/**
 * @brief delete a bridge from node of index node_num in direction d.
 * @pre the node of index node_num must have at least one node in direction d
 **/
void del_bridge_dir (game g, int node_num, dir d);



/**
 * @brief Return the number of bridges from node of index node_num in direction d
 * @param node_num the number of the node. This value must be between 0 and game_nb_nodes(g)-1.
 **/
int get_degree_dir (cgame g, int node_num, dir d);


/**
 * @brief Return the number of bridges connected to the node of index node_num.
 * @param node_num the number of the node. This value must be between 0 and game_nb_nodes(g)-1.
 **/
int get_degree (cgame g, int node_num);


/**
 * @brief Return the index of the neighbour of node node_num in direction d. Such neighbour is the first node found from the node_num in direction d.
 * @return the index of the neighbour if there is one. -1 otherwise.
 **/
int get_neighbour_dir (cgame g, int node_num, dir d);


/**
 * @brief return the index of the node with coordinate (x,y) if it exists, -1 otherwise.
 **/
int game_get_node_number (cgame g, int x, int y);




#endif // _GAME_H_
