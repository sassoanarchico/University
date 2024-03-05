#pragma once

//ia define the type of our custom function
typedef void (*ActionPtrFn)(unsigned char);

//ia current action to be executed
extern ActionPtrFn action;

//ia payload size (modified in S3)
extern unsigned int payload_size;

//ia all the actual functions that handle the states
void actionFnS1(unsigned char input);
void actionFnS2(unsigned char input);
void actionFnS3(unsigned char input);
void actionFnS4(unsigned char input);
void actionFnS5(unsigned char input);
