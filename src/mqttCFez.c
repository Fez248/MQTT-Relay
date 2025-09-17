#define _GNU_SOURCE
#include "mqttCFez.h"

#define handle_error(msg) { \
  fprintf(stderr, "%s", msg); \
  exit(EXIT_FAILURE); \
}

int num_digits(int n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    return floor(log10((double)n)) + 1;
}

void balance_tree(struct node **root) {

}

// The returns are not correct and only temporal for testing
int add_node(struct node **root, struct node *parent, struct node *varTopic) {
  // Base case
  if (*root == NULL) {
    varTopic->leftHeight = varTopic->rightHeight = 0;
    varTopic->left = varTopic->right = NULL; 
    varTopic->parent = parent;
    *root = varTopic;
    return 0;
  }

  if (strcmp(varTopic->var, (*root)->var) < 0) {
    int ret = add_node(&((*root)->left), *root, varTopic);
    if (ret == -1) return -1;
    if (desbalanceado) balance_tree(root);
    return (*root)->leftHeight = (ret + 1);
  }
  else if (strcmp(varTopic->var, (*root)->var) > 0) {
    int ret = add_node(&((*root)->right), *root, varTopic);
    if (ret == -1) return -1;
    return (*root)->rightHeight = (ret + 1);
  }
  else return -1;
}

void load_map(struct Config *cfg, char *vars, int i) {
  if (!vars || !*vars) return; 

  // strtok_r modifies the original string, and we do not want
  // to modify the env var, so we must copy it 
  char *varsCopy = strdup(vars);
  if (!varsCopy) handle_error("strdup failed");

  char *savePtr = NULL;
  char *token = strtok_r(varsCopy, " ", &savePtr); 

  while (token) {
    struct node *varTopic = calloc(1, sizeof(struct node));
    varTopic->var = malloc(strlen(token) + 1);
    strcpy(varTopic->var, token);
    varTopic->topic = cfg->topics[i];    

    if (add_node(&(cfg->map.root), NULL, varTopic) == -1) printf("A node with this key already exists\n");

    token = strtok_r(NULL, " ", &savePtr);
  }
}

void load_topics(struct Config *cfg) {
  char *topicName = malloc(strlen("TOPIC_") + num_digits(cfg->n_topics) + 1);
  for (int i = 0; i < cfg->n_topics; ++i) {
    sprintf(topicName, "TOPIC_%i", i + 1); 
    cfg->topics[i] = secure_getenv(topicName);
    if (!cfg->topics[i]) handle_error("topics is NULL");
    printf("%s\n", cfg->topics[i]);
  }
  free(topicName);
}

void load_vars(struct Config *cfg) {
  char *topicName = malloc(strlen("VARS_TOPIC_") + num_digits(cfg->n_topics) + 1);
  for (int i = 0; i < cfg->n_topics; ++i) {
    sprintf(topicName, "VARS_TOPIC_%i", i + 1);
    char *vars = secure_getenv(topicName);
    if (!vars) handle_error("error reading vars");
    load_map(cfg, vars, i); 
  }
  free(topicName);
}

void print_tree(struct node *root, int depth) {
  if (root == NULL) return;
  print_tree(root->left, depth + strlen(root->var));
  for (int i = 0; i < depth; ++i) printf(" ");
  printf("%s\n", root->var);
  print_tree(root->right, depth + strlen(root->var));
}

void load(struct Config *cfg) {
  cfg->topics = malloc(sizeof(char *) * cfg->n_topics);
  load_topics(cfg); 
  load_vars(cfg);
  print_tree(cfg->map.root, 0);
}

struct Config *config_init(void) {
  printf("Configuring library...\n");

  struct Config *cfg = calloc(1, sizeof(*cfg));
  if (!cfg) handle_error("Calloc failed\n");

  cfg->address = secure_getenv("ADDRESS");
  if (!cfg->address) handle_error("ADDRESS is NULL");
  printf("ADDRESS: %s\n", cfg->address);
     
  cfg->client_ID = secure_getenv("CLIENT_ID");
  if (!cfg->client_ID) handle_error("CLIENT_ID is NULL");
  printf("CLIENT_ID: %s\n", cfg->client_ID);

  cfg->pre_topic_device = secure_getenv("PRE_TOPIC_DEVICE");
  if (!cfg->pre_topic_device) handle_error("PRE_TOPIC_DEVICE is NULL");
  printf("PRE_TOPIC_DEVICE: %s\n", cfg->pre_topic_device);

  cfg->pre_topic_server = secure_getenv("PRE_TOPIC_SERVER");
  if (!cfg->pre_topic_server) handle_error("PRE_TOPIC_SERVER is NULL");
  printf("PRE_TOPIC_SERVER: %s\n", cfg->pre_topic_server);

  char *n_topics_string = secure_getenv("N_TOPICS");
  if (!n_topics_string) handle_error("N_TOPICS is NULL");
  cfg->n_topics = atoi(n_topics_string);
  if (cfg->n_topics <= 0) handle_error("N_TOPICS must be > 0");
  printf("N_TOPICS: %i\n", cfg->n_topics);

  cfg->ca_cert = secure_getenv("CA_CERT");
  if (!cfg->ca_cert) handle_error("CA_CERT is NULL");
  printf("CA_CERT: %s\n", cfg->ca_cert);
  
  cfg->cli_cert = secure_getenv("CLI_CERT");
  if (!cfg->cli_cert) handle_error("CLI_CERT is NULL");
  printf("CLI_CERT: %s\n", cfg->cli_cert);

  cfg->cli_key = secure_getenv("CLI_KEY");
  if (!cfg->cli_key) handle_error("CLI_KEY is NULL");
  printf("CLI_KEY: %s\n", cfg->cli_key);

  load(cfg);

  printf("Library configured correctly\n");
  return cfg;
}

