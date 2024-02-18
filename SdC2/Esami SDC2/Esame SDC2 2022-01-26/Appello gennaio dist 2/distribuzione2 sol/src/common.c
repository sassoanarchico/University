#include "common.h"

void initRandomGenerator(){
    srand(PRNG_SEED);
}

int generateRandomNumber(int max) {
    //rand() returns a random integer in the interval [0, RAND_MAX) 
    return rand() % (max);
}