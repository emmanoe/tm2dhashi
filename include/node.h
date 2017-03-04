#ifndef _NODE_H_
#define _NODE_H_
#include <stdbool.h> //The type bool is defined in this file


/**
 * @file node.h
 *
 * @brief A node represents an islande placed on the board of the game Hashiwokakero.
 *
 **/

/**
 * @struct node_s
 * @brief A node represents an island of the game Hashiwokakero. A node is characterized by its position and its required degree.
 */
typedef struct node_s* node;


/**
 * @brief Creates a new node
 * @param x,y coordinates of the node (Remark: x-axe is oriented from left to right and y-axe is oriented from bottom to top)
 * @param required_degree the integer representing the required degree of the node
 * @return a pointer toward the generated node
 */
node new_node (int x, int y, int required_degree);


/**
 * @brief Destroy the node and free allocated memory
 * @param n the node to destroy
 */
void delete_node (node n);


/**
 * @brief Returns the abscissa of the node n
 */
int get_x (node n);

/**
 * @brief Returns the ordinate of the node n
 */
int get_y (node n);

/**
 * @brief Returns the required degree of the node n
 */
int get_required_degree (node n);

#endif // _NODE_H_
