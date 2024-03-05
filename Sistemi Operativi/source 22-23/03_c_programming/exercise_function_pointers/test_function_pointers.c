#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main(int argc, char **argv) {
  printf("test_function_pointers|start\n");

  while (1) {
    int input;

    // ia read from the keyboard in hex
    printf("test_function_pointers|enter a value in hex form - es \"ff\"\n");
    scanf("%x", &input);

    /* if (0xff < input) { */
    /*   printf("test_function_pointers|WARNING, input value [ 0x%02x ] exceeds
     * limit [ 0xff ]\n", input); */
    /*   continue; */
    /* } */

    printf("test_function_pointers|input [ 0x%02x ]\n", input);

    (*action)(input);
  }

  printf("test_function_pointers|end\n");
  return 0;
}
