#ifndef MQTTCFEZ_H
#define MQTTCFEZ_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define MAX_TOPIC_SIZE 256

struct node {
  char *var;
  char *topic;
  uint8_t leftHeight;
  uint8_t rightHeight;
  struct node *left;
  struct node *right;
  struct node *parent;
};

struct MapStruct {
  struct node *root; 
};

struct Config {
    char *address;
    char *client_ID;
    char *pre_topic_device;
    char *pre_topic_server;
    char *ca_cert;
    char *cli_cert;
    char *cli_key;

    int n_topics;
    char **topics;

    struct MapStruct map;
};

// Load config from .env file
struct Config *config_init();

// Connect to the MQTT server and set up callback
// If we use the callback we are in async mode
int connect(void (*callback)());

// Send msg to the MQTT server
int send();

// Read msg from the MQTT server
// If we use the read function we are in sync mode
int read();

#endif
