#define _GNU_SOURCE
#include "mqtt_c_fez.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define handle_error(msg) { \
  errno = -1; \
  perror(msg); \
  exit(-1); \
}

int init() {
  printf("Configuring library...\n");

  char *address = secure_getenv("ADDRESS");
  if (!address)
    handle_error("Address is null");
  
  printf("Address: %s\n", address);
}

