#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "buddy_allocator.h"

#define UTIME (uint64_t)time(NULL)
#define MEMORY_SIZE (1024 * 1024)

char date[32];
char* getDate(void) {
  time_t t = time(NULL);                        
  struct tm tm = *localtime(&t);                
  sprintf(date,"%d-%02d-%02d %02d:%02d:%02d", 
          tm.tm_year + 1900,                    
          tm.tm_mon + 1,                        
          tm.tm_mday,                           
          tm.tm_hour,                           
          tm.tm_min,                            
          tm.tm_sec);
  return date;
}

char memory[MEMORY_SIZE];
BuddyAllocator alloc;

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("ERROR, usage: <%s> <num-levels>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const int target_num_levels = atoi(argv[1]);
  if (target_num_levels < 0) {
    printf("ERROR, invalid number of level inserted\n");
    exit(EXIT_FAILURE);
  }

  //ia initialize the buddy allocator using a single buffer
  printf("%s|initialization of the allocator | target allocator levels [ %d ] | total memory [ %d ]\n", getDate(), target_num_levels, MEMORY_SIZE);
  BuddyAllocator_initSingleBuffer(&alloc, target_num_levels, MEMORY_SIZE, memory);
  printf("%s|success!\n", getDate());

  printf("%s|memory request\n", getDate());
  void *p1 = BuddyAllocator_malloc(&alloc, 100);
  printf("%s|memory address [ %p ]\n", getDate(), p1);

  printf("%s|memory request\n", getDate());
  void *p2 = BuddyAllocator_malloc(&alloc, 100);
  printf("%s|memory address [ %p ]\n", getDate(), p2);

  printf("%s|memory request\n", getDate());
  void *p3 = BuddyAllocator_malloc(&alloc, 100000);
  printf("%s|memory address [ %p ]\n", getDate(), p3);

  printf("%s|memory release\n", getDate());
  BuddyAllocator_free(&alloc, p1);
  printf("%s|memory release\n", getDate());
  BuddyAllocator_free(&alloc, p2);
  printf("%s|memory release\n", getDate());
  BuddyAllocator_free(&alloc, p3);

  printf("%s|test ended\n", getDate());
  return 0;
}
