#ifndef MQTT_C_FEZ_H
#define MQTT_C_FEZ_H

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
