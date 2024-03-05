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
#include <stdint.h>
#include <time.h>
#include <errno.h>

//ia global variables
static const uint8_t shmem_size = 1;
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
  //ia install sigint handler (safe return when pressing ctrl+c)
  if (signal(SIGINT, sigHandler) == SIG_ERR)
  {
    printf("p1|error can't catch SIGINT\n");
  }

  //ia resource names (should be the same also in the other process)
  sem_name_0 = "s0";
  sem_name_1 = "s1";
  resource_name = "object";

  //ia open the two semaphores (if not there create them) and
  //ia intialize their counter according to their purpose
  //bb create if not already exists
  //bb write and read permissions
  //bb initial value of semaphor specified
  sem_t *sem_0 = sem_open(sem_name_0, O_CREAT, 0666, 0); //! full guard
  sem_t *sem_1 = sem_open(sem_name_1, O_CREAT, 0666, 1); //! empty guard

  //ia open the shared memory (if not there, create it)
  int fd = shm_open(resource_name, O_RDWR | O_CREAT, 0666);
  if (fd < 0)
  {
    printf("p1|cannot create shared memory object, error: %s \n", strerror(errno));
    exit(-1);
  }

  //ia resize the shared memory to the wanted size (one char here)
  int ftruncate_result = ftruncate(fd, shmem_size);
  if (ftruncate_result < 0)
  {
    printf("p1|cannot truncate shared memory object, error: %s \n", strerror(errno));
    exit(-1);
  }

  //ia map the shared memory in user space through mmap
  void *my_memory_area = mmap(NULL, shmem_size, PROT_WRITE, MAP_SHARED, fd, 0);

  //ia since we do not want to get stuck in the wait, we do the timedout wait
  //ia (that waits some time and then it returns an error)
  //ia this struct contains manages time (check the manual doing `man 2 clock_gettime`)
  struct timespec ts;

  //ia start producing (aka writing on the shared memory)
  uint8_t i = 0;
  while (run)
  {
    //ia since we want to have a timeout on this wait, we use the sem_timedwait instead of
    //ia the normal sem_wait. this fuction requires info about the time that we want to wait,
    //ia still, it's an absolute time (2020.05.21.12.59.31.xxxx).
    //ia hence we get the current time at this moment, and we say that it should wait
    //ia until this moment + 10 seconds.
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 10;

    //ia we invoke the wait and we check if the wait has been timed out
    if (sem_timedwait(sem_1, &ts) == -1 && errno == ETIMEDOUT)
    {
      //ia timeout expired, end cycle
      printf("p1|timeout expired\n");
      break;
    }

    //ia actual write
    char *buffer = (char *)my_memory_area;
    sprintf(buffer, "%d", i++);

    //ia some logging
    printf("p1|sent [ %s ]\n", buffer);

    //ia inform the system that you inserted a new element in the memory
    sem_post(sem_0);

    //ia wait a bit
    sleep(1);
  }

  //ia producing finished, checking out
  printf("p1|unlinking shmem ... ");
  if (shm_unlink(resource_name) < 0)
  {
    printf("error [ %s ] \n", strerror(errno));
  }
  else
  {
    printf("OK!\n");
  }

  printf("p1|closing semaphore [ %s ] ... ", sem_name_0);
  if (sem_close(sem_0) < 0)
  {
    printf("error [ %s ] \n", strerror(errno));
  }
  else
  {
    printf("OK!\n");
  }

  printf("p1|closing semaphore [ %s ] ... ", sem_name_1);
  if (sem_close(sem_1) < 0)
  {
    printf("error [ %s ] \n", strerror(errno));
  }
  else
  {
    printf("OK!\n");
  }

  printf("p1|unlinking semaphore [ %s ] ... ", sem_name_0);
  if (sem_unlink(sem_name_0) < 0)
  {
    printf("error [ %s ] \n", strerror(errno));
  }
  else
  {
    printf("OK!\n");
  }

  printf("p1|unlinking semaphore [ %s ] ... ", sem_name_1);
  if (sem_unlink(sem_name_1) < 0)
  {
    printf("error [ %s ] \n", strerror(errno));
  }
  else
  {
    printf("OK!\n");
  }

  printf("p1|exit\n");
  return 0;
}

void sigHandler(int sig_number_)
{
  //ia this should never happen - it's just my ocd :)
  if (sig_number_ != SIGINT)
  {
    printf("p1|error, wrong signal\n");
    exit(EXIT_FAILURE);
  }

  //ia safe checkout
  printf("p1|received SIGINT, stopping production\n");
  run = false;
}
