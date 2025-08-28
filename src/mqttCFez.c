#define _GNU_SOURCE
#include "mqttCFez.h"

#define handle_error(msg) { \
  errno = -1; \
  perror(msg); \
  exit(-1); \
}

char *address, *client_ID,
       *pre_topic_device, *pre_topic_server,
       *n_topics, *ca_cert,
       *cli_cert, *cli_key;

// I have to test which of these two options is most efficient
// Array of topics and array of vars with the topic each one triggers
char **topics;
char ***varsAndTopics;

// Array of topics with all the vars that trigger them
char **topicsAndVars;

int init() {
  printf("Configuring library...\n");

  address = secure_getenv("ADDRESS");
  if (!address)
    handle_error("ADDRESS is null");
  printf("ADDRESS: %s\n", address);
     
  client_ID = secure_getenv("CLIENT_ID");
  if (!client_ID)
    handle_error("CLIENT_ID is null");
  printf("CLIENT_ID: %s\n", client_ID);

  pre_topic_device = secure_getenv("PRE_TOPIC_DEVICE");
  if (!pre_topic_device)
    handle_error("PRE_TOPIC_DEVICE is null");
  printf("PRE_TOPIC_DEVICE: %s\n", pre_topic_device);

  pre_topic_server = secure_getenv("PRE_TOPIC_SERVER");
  if (!pre_topic_server)
    handle_error("PRE_TOPIC_SERVER is null");
  printf("PRE_TOPIC_SERVER: %s\n", pre_topic_server);

  n_topics = secure_getenv("N_TOPICS");
  if (!n_topics)
    handle_error("N_TOPICS is null");
  int aux_Size = strlen("VARS_TOPIC_") + strlen(n_topics);
  n_topics = (char *) atoi(n_topics); // This is IoT I have to safe space
  printf("N_TOPICS: %i\n", (int *) n_topics); // I'll change it dnt worry

  ca_cert = secure_getenv("CA_CERT");
  if (!ca_cert)
    handle_error("CA_CERT is null");
  printf("CA_CERT: %s\n", ca_cert);
  
  cli_cert = secure_getenv("CLI_CERT");
  if (!cli_cert)
    handle_error("CLI_CERT is null");
  printf("CLI_CERT: %s\n", cli_cert);

  cli_key = secure_getenv("CLI_KEY");
  if (!cli_key)
    handle_error("CLI_KEY is null");
  printf("CLI_KEy: %s\n", cli_key);

  // Lets do this come on
  char *aux = malloc(aux_Size);
  topicsAndVars = malloc(sizeof(char *) * (long unsigned int) n_topics);
  for (int i = 1; i <= (int) n_topics; ++i) {
    sprintf(aux, "VARS_TOPIC_%i", i);
    *topicsAndVars = secure_getenv(aux);
    if (!*topicsAndVars)
      handle_error("%s is null\n");
    printf("%s: %s\n", aux, *topicsAndVars);
  }

  printf("Library configured correctly\n");

  // Lets do this one more time ohohoho
  // Starships were meant to flyy
  // Hands up and touch the skyy
}

