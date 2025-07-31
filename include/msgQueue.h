#ifndef MSGQUEUE_H
#define MSGQUEUE_H

#include <sys/msg.h>

struct msg_content {                                                        
  char name[30];                                                            
  char value[30];                                                           
};                                                                          
                                                                            
struct msg_msgbuf {                                                         
  long mtype;                                                               
  struct msg_content content;                                               
};  

int createKey(int keys[2]);



#endif
