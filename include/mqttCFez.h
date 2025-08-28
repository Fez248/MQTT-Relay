#ifndef MQTTCFEZ_H
#define MQTTCFEZ_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MAX_TOPIC_SIZE 256

extern char *address, *client_ID,
       *pre_topic_device, *pre_topic_server,
       *n_topics, *ca_cert,
       *cli_cert, *cli_key;

extern char **topicsAndVars;

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
