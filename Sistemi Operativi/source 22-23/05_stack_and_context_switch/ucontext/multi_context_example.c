#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

// ia a bit of constants
#define STACK_SIZE 16384
const uint64_t num_iterations = 5;
const uint64_t max_contexts = 100;

// ia main context, our safe way back home
ucontext_t main_context;


typedef void (*ContextFnType)(void *);

typedef void (*UContextFnType)();

// ia the struct that we pass as context argument
typedef struct ContextWithStack {
  ucontext_t context;
  char stack[STACK_SIZE];
  ContextFnType fn;
  int number;
  struct ContextWithStack* next_cws;
} ContextWithStack;

// ia auxiliary function just to keep things organized
ContextWithStack * ContextWithStack_alloc(int number, ContextFnType fn) {
  ContextWithStack *cws = (ContextWithStack *)malloc(sizeof(ContextWithStack));
  cws->fn = fn;
  cws->number = number;

  getcontext(&cws->context);
  cws->context.uc_stack.ss_sp = cws->stack;
  cws->context.uc_stack.ss_size = STACK_SIZE;
  cws->context.uc_stack.ss_flags = 0;
  cws->context.uc_link = &main_context;
  cws->next_cws = 0;
  makecontext(&cws->context, (UContextFnType)cws->fn, 1, cws);
  return cws;
}

// ia context handler function
void contextFn(void *arg) {
  ContextWithStack *cws = (ContextWithStack *)arg;
  printf("context [%03d] started!\n", cws->number);
  for (int i = 0; i < num_iterations; ++i) {
    printf("context [%03d] -- iteration [%05d]\n", cws->number, i);
    if (&cws->next_cws->context)
      swapcontext(&cws->context, &cws->next_cws->context);
  }
  swapcontext(&cws->context, &main_context);
}

// ia main program
int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: %s <int n>: spawns n contexts and jumps between them. n in "
           "[1..100] \n",
           argv[0]);
    exit(0);
  }

  //ia gather how many context to create from cmd line
  int num_contexts = atoi(argv[1]);
  if (num_contexts < 0) {
    printf("ERROR, n must be positive\n");
    exit(EXIT_FAILURE);
  }
  
  if (num_contexts > max_contexts) {
    printf("ERROR, n must be <100 \n");
    exit(EXIT_FAILURE);
  }
  
  //ia create a circular list of contexts
  ContextWithStack *first = 0;
  ContextWithStack *last = 0;
  
  for (int c = 0; c < num_contexts; ++c) {
    //ia create a new context
    ContextWithStack *new_cws = ContextWithStack_alloc(c, contextFn);

    //ia handle first context (or if num_contexts == 1)
    if (!first) {
      first = last = new_cws;
    }

    //ia connect and update list
    last->next_cws = new_cws;
    last = new_cws;
  }
  last->next_cws = first;

  //ia running contexts
  printf("running [ %03d ] contexts with [ %05lu ] iterations\n", num_contexts, num_iterations);
  fflush(stdout); //ia just in case

  //ia start the context waterfall
  swapcontext(&main_context, &first->context);

  //ia we will jump back here :)
  printf("back to main\n");

  //ia remember to free the structures!
  ContextWithStack *next = first;
  for (int c = 0; c < num_contexts; ++c) {
    next = first->next_cws;
    free(first);
    first = next;
  }
  
  return 0;
}
