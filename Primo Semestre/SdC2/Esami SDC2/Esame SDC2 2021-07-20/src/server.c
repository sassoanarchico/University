#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>  // htons()
#include <netinet/in.h> // struct sockaddr_in
#include <sys/socket.h>
#include <signal.h>

#include "common.h"
#include "io.h"

int listening_socket_desc;
pid_t server_pid;
int shutting_down = 0;

void reverse_string(char* buf) {
    int i;
    int len = strlen(buf);
    char tmp;
    for(i = 0; i < len/2; i++) {
        tmp = buf[i];
        buf[i] = buf[len-i-1];
        buf[len-i-1] = tmp;
    }
}

void connection_handler(int socket_desc, struct sockaddr_in *client_addr)
{
    int ret;

    char buf[MSG_MAX_LENGTH];

    char *quit_command = QUIT_COMMAND;
    size_t quit_command_len = strlen(quit_command);

    sprintf(buf, "Hi! I'm an echo server.\nI will send you back whatever"
            " you send me. I will stop if you send me %s :-)\n", quit_command);

    send_to_socket(socket_desc, buf);

    // echo loop
    while (1) {
        // read message from client
        ret = recv_from_socket(socket_desc, buf, MSG_MAX_LENGTH);
        if(ret == 0) handle_error("Error reading from socket");

        printf("[Child] Received request: %s\n", buf);

        if (ret == quit_command_len && !memcmp(buf, quit_command, quit_command_len)) break;

        reverse_string(buf);

        send_to_socket(socket_desc, buf);
        printf("[Child] Sent response: %s\n", buf);
    }

    printf("[Child] Connection closed");

}

void signal_handler(int sig_no) {
    if (getpid() == server_pid) {
        shutting_down = 1;
    }
}

int main(int argc, char *argv[])
{
    int ret;

    int client_desc;

    // some fields are required to be filled with 0
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};

    int sockaddr_len = sizeof(struct sockaddr_in); // we will reuse it for accept()

    server_addr.sin_addr.s_addr = INADDR_ANY; // we want to accept connections from any interface
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT); // don't forget about network byte order!

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - Craere una stream socket
     * - Gestire eventuali errori
     *
     */


    /***/

    /* We enable SO_REUSEADDR to quickly restart our server after a crash:
     * for more details, read about the TIME_WAIT state in the TCP protocol */
    int reuseaddr_opt = 1;
    ret = setsockopt(listening_socket_desc, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt));
    if(ret) handle_error("Cannot set SO_REUSEADDR option");

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - Inizializzare la socket per connessione lato server
     * - Gestire eventuali errori
     *
     */


    /***/

    // We set up a handler for SIGTERM and SIGINT signals
    server_pid = getpid();
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = &signal_handler;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    printf("[Parent] Server started!\n");

    // loop to manage incoming connections forking the server process
    while (1) {
        pid_t pid;
        // accept incoming connection
        client_desc = accept(listening_socket_desc, (struct sockaddr *)&client_addr, (socklen_t *)&sockaddr_len);
        if (shutting_down) break;
        if (client_desc == -1 && errno == EINTR) continue; // check for interruption by (other) signals
        if (client_desc == -1) handle_error("Cannot open socket for incoming connection");

        printf("[Parent] Incoming connection accepted...\n");

        /**
         * COMPLETARE QUI
         *
         * Obiettivi:
         * - creare un processo figlio per gestire la connessione
         * - nel processo figlio:
         *      * rilasciare le risorse che il figlio non ha bisogno di usare
         *      * invocare la funzione connection_handler
         *      * rilasciare le risorse acquisite dal figlio
         * - nel processo padre:
         *      * rilasciare le risorse che il padre non ha bisogno di usare
         *      * resettare la struttura dati necessaria per accettare nuove
         *        connessioni
         * - gestire eventuali errori, terminando l'applicazione
         *
         */


        /***/
        memset(&client_addr, 0, sizeof(struct sockaddr));
    }

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - rilasciare le risorse acquisite dal processo principale del server
     * - gestire eventuali errori, terminando l'applicazione
     *
     */


    /***/

    exit(EXIT_SUCCESS);
}
