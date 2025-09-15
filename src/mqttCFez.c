#define _GNU_SOURCE
#include "mqttCFez.h"

#define handle_error(msg) { \
  fprintf(stderr, "%s", msg); \
  exit(EXIT_FAILURE); \
}

char *address, *client_ID,
       *pre_topic_device, *pre_topic_server,
       *ca_cert, *cli_cert, *cli_key;

int n_topics;
      
char **topics;
struct MapStruct map;

int num_digits(int n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    return floor(log10((double)n)) + 1;
}

// asumme aux has exactly one space between vars, and none before neither
// after the whole string: TO DO: sanitize the input
void load_map(char *aux, int i) {
  if (!strlen(aux))
    return;
  
  char *start = aux;
  char *blank = strchr(start, ' ');
  if (!blank)
   blank = &aux[strlen(aux)]; 

  while (blank) {
    struct node *varTopic = malloc(sizeof(struct node));
    
    varTopic->var = malloc(sizeof(char) * (blank - start + 1));
    memcpy(varTopic->var, start, blank - start);
    (varTopic->var)[blank - start + 1] = '\0';
    // printf("%s\n", varTopic->var);

    varTopic->topic = topics[i];

    if (map.root == NULL) {
      varTopic->left = varTopic->right = varTopic->parent = NULL; 
      map.root = varTopic;
    }

    if (blank == &aux[strlen(aux)])
      blank = NULL;
    else {
      start = blank + 1;
      blank = strchr(start, ' '); 
      if (!blank)
        blank = &aux[strlen(aux)]; 
    }
  }
}

void load() {
  char *topicName = malloc(strlen("TOPIC_") + num_digits(n_topics) + 1);
  topics = malloc(sizeof(char *) * n_topics);

  for (int i = 0; i < n_topics; ++i) {
    sprintf(topicName, "TOPIC_%i\0", i + 1); 
    topics[i] = secure_getenv(topicName);
    if (!topics[i])
      handle_error("topics is null");
    printf("%s\n", topics[i]);
  } 
 
  free(topicName);
  topicName = malloc(strlen("VARS_TOPIC_") + num_digits(n_topics) + 1);
  for (int i = 0; i < (int) n_topics; ++i) {
    sprintf(topicName, "VARS_TOPIC_%i\0", i + 1);
    char *aux = secure_getenv(topicName);
    if (!aux)
      handle_error("error reading vars")
    load_map(aux, i); 
  }
  
  printf("Root var: %s, with topic: %s\n", (map.root)->var,
    (map.root)->topic);

}

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

  n_topics = atoi(secure_getenv("N_TOPICS"));
  if (n_topics == 0)
    handle_error("N_TOPICS is null");
  printf("N_TOPICS: %i\n", n_topics);

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

  /*
  // Lets do this come on
  char *aux = malloc(aux_Size);
  topicsAndVars = malloc(sizeof(char *) * (long unsigned int) n_topics);
  for (int i = 1; i <= (int) n_topics; ++i) {
    sprintf(aux, "VARS_TOPIC_%i", i);
    topicsAndVars[i - 1] =           secure_getenv(aux);
    if (!*topicsAndVars)
      handle_error("%s is null\n");
    printf("%s: %s\n", aux, topicsAndVars[i - 1]);
  }
  */
  printf("Library configured correctly\n");
  load();
  // Lets do this one more time ohohoho
  // Starships were meant to flyy
  // Hands up and touch the skyy
}

