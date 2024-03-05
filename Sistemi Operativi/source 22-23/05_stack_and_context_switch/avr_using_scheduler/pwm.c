#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <encoder_new.h>

void pwm_thread (uint32_t useless_numba) {
 // we will use timer 1
  // configuration bits for PWM
  // fast PWM, 8 bit, non inverted
  // output compare set low
  TCCR1A = (1<<WGM10)|(1<<COM1C0)|(1<<COM1C1);
  TCCR1B = ((1<<WGM12)|(1<<CS10));

  // clear all higher bits of output compare for timer
  OCR1AH=0;
  OCR1BH=0;
  OCR1C=1;
  
  // the LED is connected to pin 13
  // that is the bit 7 of port b, we set it as output
  const uint8_t mask=(1<<7);
  // we configure the pin as output
  DDRB |= mask;//mask;

  uint16_t previous_counter=0;
  while(1){
    // we write on the output compare register a value
    // that will be proportional to the opposite of the
    // duty_cycle
    if (previous_counter!=encoder_counter) {
      
      OCR1CL= encoder_counter &0xFF; 
      cli();
      printf("pwm: %u\n", (int) OCR1CL);
      sei();
    }
    previous_counter=encoder_counter;
    _delay_ms(1); // from delay.h, wait 1 sec
  }
}

