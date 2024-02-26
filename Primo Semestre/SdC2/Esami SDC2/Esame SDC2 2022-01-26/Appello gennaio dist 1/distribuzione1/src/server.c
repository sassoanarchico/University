#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>  // htons()
#include <netinet/in.h> // struct sockaddr_in
#include <sys/socket.h>
#include <pthread.h>
#include "common.h"
#include <semaphore.h>
#include <signal.h>


#define BUFFER_SIZE      10

typedef struct handler_args_s
{
    int socket_desc;
} handler_args_t;


typedef struct message_s
{
  char type;
  int value;
} message_t;


/**
 * COMPLETARE QUI
 *
 * Obiettivi:
 * - definire i semafori ritenuto necessari per la soluzione del problema
 * 
 */


int socket_desc;

int buf [BUFFER_SIZE];
int idx = 0;



void init_socket(){
    // some fields are required to be filled with 0
    struct sockaddr_in server_addr = {0};
    int ret;
    // we will reuse it for accept()

    server_addr.sin_addr.s_addr = INADDR_ANY; // we want to accept connections from any interface
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(SERVER_PORT); // don't forget about network byte order!


    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - instanziare una STREAM socket per il server
     * - facilitare il riavvio della socket (codice presente qui sotto)
     * - associare la socket all'indirizzo del server (server_addr) definito sopra
     * - mettere la socket in ascolto
     * - gestire gli errori
     */

    /* We enable SO_REUSEADDR to quickly restart our server after a crash:
     * for more details, read about the TIME_WAIT state in the TCP protocol */
    int reuseaddr_opt = 1;
    ret = setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt));
    if (ret) handle_error("Cannot set SO_REUSEADDR option");

}

void openSemaphores() {
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - aprire i semafori necessari ed inizializzarli al corretto valore
     * - gestire gli errori
     */

}



// Wrapper function that take as input handler_args_t struct and then call
// connection_handler.
void *thread_connection_handler(void *arg) {
    handler_args_t *args = (handler_args_t *)arg;
    int sock_desk = args->socket_desc;
    int ret, recv_bytes;

    message_t m;
    size_t message_len = sizeof(m);



    while (1) {
        // read message from client
        memset(&m, 0, message_len);
        recv_bytes = 0;
        printf("waiting for command\n");
        fflush(stdout);
        do {
            ret = recv(sock_desk, &m + recv_bytes, message_len - recv_bytes, 0);
            if (ret == -1 && errno == EINTR) continue;
            if (ret == -1) handle_error("Cannot read from the socket");
            if (ret == 0) break;
            recv_bytes += ret;
        } while (recv_bytes < message_len);

        // check whether I have just been told to quit...
        if (m.type == 'q'){
            printf("received command %c\n",m.type);
            fflush(stdout);
            break;
        }
        int answer;
        if (m.type == 'w'){
          printf("received command %c with value %d\n",m.type,m.value);
          fflush(stdout);
          printf("writing value in the pile... ");fflush(stdout);
            
            /**
             * COMPLETARE QUI
             * 
             * In caso di comado 'w' si deve inserire un elemento nella pila
             * in concorrenza con altri thread che possono inserire o estrarre
             * elementi dalla pila
             * Obiettivi:
             * - gestire i semafori all'interno dell'if come si ritiene più 
             *   opportuno al fine di proteggere correttamente la sezione critica.
             * - gestire gli errori
             */
          buf[idx] = m.value;
          int pos = idx;
          idx++;
          answer = 1;
          printf("done\n");fflush(stdout);
          printf("inserted value %d in position %d\n",m.value,pos);fflush(stdout);
          printf("sending back confirmation .... ");
        }
        if (m.type == 'r'){
          printf("received command %c\n",m.type);
          fflush(stdout);
          printf("reading value from the pile... ");fflush(stdout);
            /**
             * COMPLETARE QUI
             * 
             * In caso di comado 'r' si deve prelevare un elemento dalla pila
             * in concorrenza con altri thread che possono inserire o estrarre
             * elementi dalla pila
             * Obiettivi:
             * - sistemare i semafori all'interno dell'if come si ritiene più 
             *   opportuno al fine di proteggere correttamente la sezione critica.
             * - gestire gli errori
             */
          idx--;
          answer = buf[idx];
          int pos = idx;
          printf("done\n");fflush(stdout);
          printf("retrieved value %d from pos %d\n",answer,pos);fflush(stdout);
          printf("sending back %d .... ",answer);
        }
        fflush(stdout);

        int bytes_sent=0;
        while ( bytes_sent < sizeof(int)) {
            ret = send(sock_desk, &answer + bytes_sent, sizeof(int) - bytes_sent, 0);
            if (ret == -1 && errno == EINTR) continue;
            if (ret == -1) handle_error("Cannot write to the socket");
            bytes_sent += ret;
        }
        printf("done\n");fflush(stdout);
    }
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi:
     * - liberare le risorse non necessarie
     * - gestire gli errori
     */

    printf("thread closed\n");fflush(stdout);
    pthread_exit(NULL);
}

void mthreadServer() {
    int ret = 0;

    // loop to manage incoming connections spawning handler threads
    int sockaddr_len = sizeof(struct sockaddr_in);
    while (1) {

        /**
         * COMPLETARE QUI
         * 
         * Obiettivi:
         * - accettare una connessione in ingresso dal client
         * - preparare gli argomenti necessari nella variabile thread_args
         * - gestire gli errori
         */



        printf("Incoming connection accepted...\n");

        pthread_t thread;
        handler_args_t *thread_args = malloc(sizeof(handler_args_t));


        ret = pthread_create(&thread, NULL, thread_connection_handler, (void *)thread_args);
        if (ret) handle_error_en(ret, "Could not create a new thread");

        ret = pthread_detach(thread); // I won't phtread_join() on this thread
        if (ret) handle_error_en(ret, "Could not detach the thread");
    }
}

void close_everything() {
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi:
     * - chiudere la socket
     * - chiudere i semafori
     * - gestire gli errori
     */

}

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num)
{
    printf("\n SIGINT or CTRL-C detected. Exiting gracefully \n");
    close_everything();
    fflush(stdout);
    exit(0);
}


int main(int argc, char** argv) {

    /* Set the SIGINT (Ctrl-C) signal handler to sigintHandler
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler);


    //init semaphores
    openSemaphores();
    printf("semaphores opened\n");
    fflush(stdout);

    //init_socket
    init_socket();
    printf("socket opened\n");
    fflush(stdout);

    //start server activity
    mthreadServer();

  return 0;
}
