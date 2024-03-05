#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h" 

const uint8_t encoder_mask=0x03;

static const int8_t _transition_table []=
  {
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

uint16_t encoder_counter=0x0;
  
void encoder_thread(uint32_t nome) {
  DDRB &= ~encoder_mask;
  PORTB |= encoder_mask;
  uint8_t previous_state=0x0;
  while (1) {
    uint8_t current_state = PINB & encoder_mask;

    if (current_state != previous_state) {
      uint8_t idx= (previous_state<<2 | current_state);
      encoder_counter += _transition_table[idx];
      cli();
      printf("state change %x -> %x, value: %u\n",
             (int) previous_state,
             (int) current_state,
             encoder_counter);
      sei();
    }
    previous_state = current_state;
    _delay_ms(1);
  }
}
