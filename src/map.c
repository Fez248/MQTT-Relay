#include "map.h"

/*
 * Brief: 	Add new node to map
 * Params:	root --> root of the map where the node is to be added
 *		newNode --> node to be added
 * Return:	Returns the new height of the tree
 * Notes:	If a node with the same key already exists it is not added
 *
 */
int add_node(struct node **root, struct node *newNode) {
    if (!*root) {
        *root = newNode;
        newNode->left = newNode->right = NULL;
        return 1;
    }
    if ((*root)->var < newNode->var) return (*root)->rightHeight += add_node((*root)->right, newNode);
    else if ((*root)->var > newNode->var) return (*root)->leftHeight += add_node((*root)->left, newNode);
    return 0;
}

void print_tree(struct node *root, int depth) {
  if (root == NULL) return;
  print_tree(root->left, depth + strlen(root->var));
  for (int i = 0; i < depth; ++i) printf(" ");
  printf("%s\n", root->var);
  print_tree(root->right, depth + strlen(root->var));
}
