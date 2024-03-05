#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it

static const uint8_t mask = 0x03;

static const int8_t _transition_table [] ={
      0,  //0000
      1,  //0001
     -1,  //0010
      0,  //0011
     -1,  //0100
      0,  //0101
      0,  //0110
      1,  //0111
      1,  //1000
      0,  //1001
      0,  //1010
     -1,  //1011
      0,  //1100
     -1,  //1101
      1,  //1110
      0   //1111
};

int main(void){

    printf_init();

    DDRA &= ~mask;
    PORTA |= mask;

    uint8_t prev_state = 0x0;
    int counter = 0;

    while(1){
        uint8_t curr_state = PINA & mask;

        uint8_t idx = (prev_state << 2) | curr_state;

        int8_t value = _transition_table[idx];

        counter += value;

        printf("Curr state: %02x\n",curr_state);
        printf("Idx: %d\n",idx);
        printf("Value: %d\n",value);
        printf("Counter: %d\n",counter);
        printf("****************");

        prev_state = curr_state;
        _delay_ms(1000); // from delay.h, wait 1.0s
    }

    return 0;
}
