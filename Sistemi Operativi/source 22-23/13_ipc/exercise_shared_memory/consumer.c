#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>

//ia variable that tells us when to exit
static volatile bool run = true;

//ia sigint handler otherwise you have to reboot the damn pc every time
void sigHandler(int sig_number_);

//ia two semaphores are required:
//ia - one to check if the queue is empty,
//ia - one to check if the queue is full
char *sem_name_0;
char *sem_name_1;
char *resource_name;

int main(int argc, char **argv)
{
  if (signal(SIGINT, sigHandler) == SIG_ERR)
  {
    printf("p2|error can't catch SIGINT\n");
  }

  //ia resource names (should be the same also in the other process)
  sem_name_0 = "s0";
  sem_name_1 = "s1";
  resource_name = "object";

  //ia open the two semaphores (if not there create them) and
  //ia initialize their counter according to their purpose
  sem_t *sem_0 = sem_open(sem_name_0, O_CREAT, 0666, 0); //! full
  sem_t *sem_1 = sem_open(sem_name_1, O_CREAT, 0666, 1); //! empty

  //ia open the shared memory in read-only mode.
  //ia note that if it's not this will throw an error and close the program
  int fd = shm_open(resource_name, O_RDONLY, 0666);
  if (fd < 0)
  {
    printf("p2|cannot link to shared memory object, error: %s \n", strerror(errno));
    exit(-1);
  }

  //ia we have to get the shmem size from the shmem itself (since we are sheer readers)
  int shmem_size = 0;

  //ia to do so, we use the good old fstat syscall
  struct stat shm_status;
  if (fstat(fd, &shm_status) < 0)
  {
    printf("p2|cannot get stats from memory object, error: %s \n", strerror(errno));
    exit(-1);
  }

  //ia this is the size of the file and, thus, of the shmem
  shmem_size = shm_status.st_size;

  //ia map the shared memory in user space through mmap
  void *my_memory_area = mmap(NULL, shmem_size, PROT_READ, MAP_SHARED, fd, 0);

  //ia since we do not want to get stuck in the wait, we do the timedout wait
  //ia (that waits some time and then it returns an error)
  //ia this struct contains manages time (check the manual doing `man 2 clock_gettime`)
  struct timespec ts;

  //ia start consuming (aka reading from memory)
  while (run)
  {
    /* sem_wait(sem_0); */

    //ia since we want to have a timeout on this wait, we use the sem_timedwait instead of
    //ia the normal sem_wait. this fuction requires info about the time that we want to wait,
    //ia still, it's an absolute time (2020.05.21.12.59.31.xxxx).
    //ia hence we get the current time at this moment, and we say that it should wait
    //ia until this moment + 10 seconds.
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 10;

    //ia we invoke the wait and we check if the wait has been timed out
    if (sem_timedwait(sem_0, &ts) == -1 && errno == ETIMEDOUT)
    {
      //ia timeout expired, end cycle
      printf("p2|timeout expired\n");
      break;
    }

    int n = atoi((char *)my_memory_area);
    printf("p2|received [ %d ]\n", n);
    sem_post(sem_1);
  }

  //ia cycle finished, checking out
  printf("p2|unlinking shmem ... ");
  if (shm_unlink(resource_name) < 0)
  {
    printf("error [ %s ] \n", strerror(errno));
  }
  else
  {
    printf("OK!\n");
  }

  printf("p2|closing semaphore [ %s ] ... ", sem_name_0);
  if (sem_close(sem_0) < 0)
  {
    printf("error [ %s ] \n", strerror(errno));
  }
  else
  {
    printf("OK!\n");
  }

  printf("p2|closing semaphore [ %s ] ... ", sem_name_1);
  if (sem_close(sem_1) < 0)
  {
    printf("error [ %s ] \n", strerror(errno));
  }
  else
  {
    printf("OK!\n");
  }

  printf("p2|exit\n");
  return 0;
}

void sigHandler(int sig_number_)
{
  if (sig_number_ != SIGINT)
  {
    printf("p2|error, wrong signal\n");
    exit(EXIT_FAILURE);
  }
  printf("p2|received SIGINT, stopping consumption\n");
  run = false;
}
