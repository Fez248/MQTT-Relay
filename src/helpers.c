#include "helpers.h"

#define handle_error(msg) { \
  fprintf(stderr, "%s", msg); \
  exit(EXIT_FAILURE); \
}

int num_digits(int n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    return floor(log10((double)n)) + 1;
}