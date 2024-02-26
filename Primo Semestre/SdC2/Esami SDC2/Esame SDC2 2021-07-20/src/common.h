#ifndef __COMMON_H__ // accorgimento per evitare inclusioni multiple di un header
#define __COMMON_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// macro to simplify error handling
#define GENERIC_ERROR_HELPER(cond, errCode, msg) do {               \
        if (cond) {                                                 \
            fprintf(stderr, "%s: %s\n", msg, strerror(errCode));    \
            exit(EXIT_FAILURE);                                     \
        }                                                           \
    } while(0)

#define ERROR_HELPER(ret, msg)      GENERIC_ERROR_HELPER((ret < 0), errno, msg)

// macros for handling errors
#define handle_error_en(en, msg)    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error(msg)           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MSG_MAX_LENGTH 512

#define MAX_CONN_QUEUE  3   // max number of connections the server can queue
#define SERVER_ADDRESS  "127.0.0.1"
#define QUIT_COMMAND    "QUIT"
#define SERVER_PORT     2015
#define DEBUG           1   // display debug messages

#define WELCOME_STRING_FORMAT "Hi! I'm an echo server. You are %s talking on port %hu. I will send you back whatever you send me. I will stop if you send me %s :-)"

#endif
