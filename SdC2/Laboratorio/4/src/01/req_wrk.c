#include "common.h"

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>


// data array
int * data;
/** COMPLETE THE FOLLOWING CODE BLOCK
*
* Add any needed resource 
**/

int request() {
  /** COMPLETE THE FOLLOWING CODE BLOCK
  *
  * map the shared memory in the data array
  **/

  printf("request: mapped address: %p\n", data);

  int i;
  for (i = 0; i < NUM; ++i) {
    data[i] = i;
  }
  printf("request: data generated\n");

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Signal the worker that it can start the elaboration
    * and wait it has terminated
    **/
  printf("request: acquire updated data\n");

  printf("request: updated data:\n");
  for (i = 0; i < NUM; ++i) {
    printf("%d\n", data[i]);
  }

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Release resources
    **/


  return EXIT_SUCCESS;
}

int work() {

  /** COMPLETE THE FOLLOWING CODE BLOCK
  *
  * map the shared memory in the data array
  **/
  printf("worker: mapped address: %p\n", data);

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Wait that the request() process generated data
    **/

  printf("worker: waiting initial data\n");

  printf("worker: initial data acquired\n");

  printf("worker: update data\n");
  int i;
  for (i = 0; i < NUM; ++i) {
    data[i] = data[i] * data[i];
  }

  printf("worker: release updated data\n");

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Signal the requester that elaboration terminated
    **/


  /** COMPLETE THE FOLLOWING CODE BLOCK
   *
   * Release resources
   **/

  return EXIT_SUCCESS;
}



int main(int argc, char **argv){

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Create and open the needed resources 
    **/



    int ret;
    pid_t pid = fork();
    if (pid == -1) {
        handle_error("main: fork");
    } else if (pid == 0) {
        work();
        _exit(EXIT_SUCCESS);
    }

    request();
    int status;
    ret = wait(&status);
    if (ret == -1)
      handle_error("main: wait");
    if (WEXITSTATUS(status)) handle_error_en(WEXITSTATUS(status), "request() crashed");


   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Close and release resources
    **/

    _exit(EXIT_SUCCESS);

}
