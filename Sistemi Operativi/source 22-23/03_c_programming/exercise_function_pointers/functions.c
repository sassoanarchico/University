#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "functions.h"

//ia define the current action variable (already declared in the .h)
ActionPtrFn action = actionFnS1;

//ia define the payload variable (already declared in the .h)
unsigned int payload_size = 0;

void actionFnS1(unsigned char input) {
  /* printf("actionFnS1|input [ 0x%02x ]\n", input); */
  if (0xAA == input) {
    action = actionFnS2;
    printf("next state S2\n");
  } else {
    printf("next state S1\n");
  }
  return;
}

void actionFnS2(unsigned char input) {
  /* printf("actionFnS2|input [ 0x%02x ]\n", input); */
  if (0x55 == input) {
    action = actionFnS3;
    printf("next state S3\n");
  } else {
    action = actionFnS1;
    printf("next state S1\n");
  }
}

void actionFnS3(unsigned char input) {
  /* printf("actionFnS3|input [ 0x%02x ]\n", input); */
  payload_size = (unsigned int)(input);
  printf("actionFnS3|payload [ %d ]\n", payload_size);
  action = actionFnS4;
  printf("next state S4\n");
}

void actionFnS4(unsigned char input) {
  /* printf("actionFnS4|input [ 0x%02x ]\n", input); */
  //ia consume the payload
  if (payload_size--) {
    printf("actionFnS4|payload to read [ %d ] - value [0x%02x]\n",
           payload_size, input);
  } else {
    action = actionFnS5;
    printf("next state S5\n");
  }
}

void actionFnS5(unsigned char input) {
  /* printf("actionFnS5|input [ 0x%02x ]\n", input); */
  if (0xAA == input) {
    action = actionFnS2;
    printf("next state S2\n");
  } else {
    action = actionFnS1;
    printf("next state S1\n");
  }
}
