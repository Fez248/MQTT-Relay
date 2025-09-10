#ifndef MQTTCFEZ_H
#define MQTTCFEZ_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define MAX_TOPIC_SIZE 256

extern char *address, *client_ID,
       *pre_topic_device, *pre_topic_server,
       *ca_cert, *cli_cert, *cli_key;

extern int n_topics;

// We are building a map yeaaah
struct node {
  char *var;
  char *topic;
  struct node *left;
  struct node *right;
  struct node *parent;
};

struct MapStruct {
  struct node *root; 
};

extern char **topics;

void freePointers();

// Load map
void load();

// Sort map
void sort();

// Search in map for VarTopic with var as key
struct VarTopic* search(char *var);

// Load config from .env file
int init();

// Connect to the MQTT server and set up callback
// If we use the callback we are in async mode
int connect(void (*callback)());

// Send msg to the MQTT server
int send();

// Read msg from the MQTT server
// If we use the read function we are in sync mode
int read();

#endif
