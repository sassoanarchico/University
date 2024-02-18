#include <string.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>       // nanosleep()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "common.h"

// definizione struttura memoria
struct cell{
    int reward;
    int input;
};

struct shared_memory {
     /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - definire i semafori unnamed necessari per gestire la concorrenza
     * - devono essere gli stessi (stesso ordine) in elaborator.c (fare copia/incolla)
     */
    struct cell buf [BUFFER_SIZE];
    int read_index;
    int write_index;
    
    sem_t e_sem;
    sem_t n_sem;
    sem_t s_sem;
};


//definizione shared memory
struct shared_memory *myshm_ptr;
int fd_shm;


void openMemory() {
     /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - richiedere al kernerl l'accesso alla memoria condivisa creata da elaborator.c
     * - Gestire gli errori.
     *
     */
    
	 fd_shm=shm_open(SH_MEM_NAME,O_RDWR|O_EXCL,0666);
     if(fd_shm<0) handle_error("shm_open error\n");  
     
     myshm_ptr=mmap(NULL,sizeof(struct shared_memory),PROT_READ|PROT_WRITE,MAP_SHARED,fd_shm,0);
     if(myshm_ptr==MAP_FAILED) handle_error("mmap error\n");
}

void request(){
    int balance = generateRandomNumber(10000);
    while(1){
        /** 
         * COMPLETARE QUI
         *
         * Il producer genera una serie di input da scrivere nel buffer 
         * Ogni input dovraà essere elaborato dall'elaborator
         * a cui viene corrisposto un pagamento (reward)
         * Quando il pagamento supera la disponibilità il producer termina la
         * propria attività
         * 
         * Obiettivi:
         * - gestire la sezione critica opportunamente tramite i semafori
         * - gestire gli errori 
         **/

        int reward = generateRandomNumber(1000);
        if (reward>balance){
            printf("not enough money, exit\n");fflush(stdout);
            break;
        }
        balance -= reward;

        int input = generateRandomNumber(100);
        printf("Generated input %d\n",input);
        struct timespec pause = {0};
        pause.tv_nsec = 500000000; // 0.5 s (1*10^9 ns)
        nanosleep(&pause, NULL);

		int ret;
		
		ret=sem_wait(&(myshm_ptr->e_sem));
		if(ret<0) handle_error("sem_wait error\n");

		ret=sem_wait(&(myshm_ptr->s_sem));
		if(ret<0) handle_error("sem_wait error\n");


		//cs start
        myshm_ptr->buf[myshm_ptr->write_index].reward = reward;
        myshm_ptr->buf[myshm_ptr->write_index].input = input;
        myshm_ptr->write_index++;
        if (myshm_ptr->write_index == BUFFER_SIZE)
            myshm_ptr->write_index = 0;
		//cs stop
		
		ret=sem_post(&(myshm_ptr->s_sem));
		if(ret<0) handle_error("sem_post error\n");

		ret=sem_post(&(myshm_ptr->n_sem));
		if(ret<0) handle_error("sem_post error\n");

		
		
    }

}

void closeSemaphores() {
    /** 
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - gestire la chiusura dei semafori
     * - gestire gli errori 
     **/
     
    int ret;
	
	//chiusura semafori
	ret=sem_destroy(&(myshm_ptr->e_sem));
	if(ret<0) handle_error("sem_destroy error\n");
	
	ret=sem_destroy(&(myshm_ptr->s_sem));
	if(ret<0) handle_error("sem_destroy error\n");
	
	ret=sem_destroy(&(myshm_ptr->n_sem));
	if(ret<0) handle_error("sem_destroy error\n");
}

void closeMemory() {
    /** 
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - chiudere la memoria condivisa
     * - chiedere al kernel di eliminare la memoria condivisa
     * - gestire gli errori 
     **/
	int ret;
	//chiusura shmem
	ret=munmap(myshm_ptr,sizeof(struct shared_memory));
	if(ret<0) handle_error("munmap error");
	
	ret=close(fd_shm);
	if(ret<0) handle_error("shmem file descriptor error\n");
	
	
}


int main(int argc, char** argv) {
    initRandomGenerator();

    //load memory
    printf("opening shared memory\n");fflush(stdout);
    openMemory();

    //request cycle
    request();

    //close semaphores
    closeSemaphores();

    //close memory
    closeMemory();

    exit(EXIT_SUCCESS);
}

