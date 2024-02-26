#include "common.h"

#include <fcntl.h>  // O_CREAT and O_EXCL flags
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

sem_t *sem_filled, *sem_empty, *sem_cs;

void initSemaphores() {
    // delete stale semaphores from a previous crash (if any)
    sem_unlink(SEMNAME_FILLED);
    sem_unlink(SEMNAME_EMPTY);
    sem_unlink(SEMNAME_CS);

    /* We create three named semaphores:
    * - sem_filled to check that our buffer is not empty
    *   (we need to initialize it to 0)
    * - sem_empty to check that our buffer is not full
    *   (we need to initialize it to the buffer's capacity BUFFER_SIZE)
    * - sem_cs to enforce mutual exclusion when accessing the file
    */

    /* TODO: create the semaphores as described above */

    sem_filled = NULL;
    if (sem_filled == SEM_FAILED) handle_error("sem_open filled");

    sem_empty = NULL;
    if (sem_empty == SEM_FAILED) handle_error("sem_open empty");

    sem_cs = NULL;
    if (sem_cs == SEM_FAILED) handle_error("sem_open cs");
}

void closeSemaphores() {
    /* When the program that controls the producer(s) terminates, we
     * need to close all the the semaphores we previously opened */

    /* TODO: implement the operations described above, and handle
     * possible errors using the predefined handle_error() macro */


}

static inline int performRandomTransaction() {
    struct timespec pause = {0};
    pause.tv_nsec = 10*1000000; // 10 ms (10*10^6 ns)
    nanosleep(&pause, NULL);

    int amount = rand() % (2 * MAX_TRANSACTION);
    return (amount >= MAX_TRANSACTION) ? (MAX_TRANSACTION-amount-1) : (amount+1);
}

void produce(int id, int numOps) {
    int localSum = 0;
    while (numOps > 0) {

        /* Before adding an element to the buffer, we have to check that
         * it is not full by using the semaphore sem_empty.
         * We need also to access to the critical section by enforcing
         * mutual esclusion, which can be achieved using sem_cs. */

        /* TODO: implement the operations described above, and handle
         * possible errors using the predefined handle_error() macro */


        // CRITICAL SECTION
        int value = performRandomTransaction();
        writeToBufferFile(value, BUFFER_SIZE, BUFFER_FILENAME);
        localSum += value;

        /* On leaving the critical section we have to "release" the
         * shared resource via sem_cs, and notify the consumer(s) that
         * a new element is available using the semaphore sem_filled. */

        /* TODO: implement the operations described above, and handle
         * possible errors using the predefined handle_error() macro */


        numOps--;
    }
    printf("Producer %d ended. Local sum is %d\n", id, localSum);
}

int main(int argc, char** argv) {
    srand(PRNG_SEED);
    initFile(BUFFER_SIZE, BUFFER_FILENAME);
    initSemaphores();

    int i, ret;
    for (i=0; i<NUM_PRODUCERS; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            handle_error("fork");
        } else if (pid == 0) {
            produce(i, OPS_PER_PRODUCER);
            _exit(EXIT_SUCCESS);
        }
    }

    for (i=0; i<NUM_PRODUCERS; ++i) {
        int status;
        ret = wait(&status);
        if (ret == -1) handle_error("wait");
        if (WEXITSTATUS(status)) handle_error_en(WEXITSTATUS(status), "child crashed");
    }

    printf("Producers have terminated. Exiting...\n");
    closeSemaphores();

    exit(EXIT_SUCCESS);
}
