#include "msgQueue.h"

int createKey(int keys[2]) {
  key_t keySnd, keyRcv;
  
  if ((keySnd = ftok("/home", 'S')) == -1) {
    perror("ftok");
    return -1;
  }

  if ((keyRcv == ftok("/home", 'R')) == -1) {
    perror("ftok");
    return -1;
  }

  if ((
}

// struct msg_msgbuf bufSnd, bufRcv;
