#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <stdlib.h>

struct node {
  char *var;
  char *topic;
  uint8_t leftHeight;
  uint8_t rightHeight;
  struct node *left;
  struct node *right;
};

struct MapStruct {
  struct node *root; 
};

int add_node(struct node **root, struct node *newNode);

void print_tree(struct node *root, int depth);

#endif