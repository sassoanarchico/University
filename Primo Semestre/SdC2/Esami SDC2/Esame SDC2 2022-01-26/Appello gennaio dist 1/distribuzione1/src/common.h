#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// macros for handling errors
#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

// macros for server.c and client.c
#define PRNG_SEED           0
#define SERVER_ADDRESS  "127.0.0.1"
#define SERVER_PORT      2019
#define MAX_CONN_QUEUE  3   // max number of connections the server can queue

// methods defined in common.c
void initRandomGenerator();
int generateRandomNumber(int max);
