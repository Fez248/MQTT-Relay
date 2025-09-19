#ifndef HELPERS_H
#define HELPERS_H

#include <math.h>

#define handle_error(msg) { \
  fprintf(stderr, "%s", msg); \
  exit(EXIT_FAILURE); \
}

int num_digits(int n);

#endif