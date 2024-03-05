#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//ia include our custom uart (from previous exercise)
#include "my_uart.h"

//ia we will use the entire port B for this exercise. we recall (from the ds) that
//ia PORTB [ bit-07 bit-06 bit-05 bit-04 bit-03 bit-02 bit-01 bit-00 ]
//ia BOARD [ pin-13 pin-12 pin-11 pin-10 pin-50 pin-51 pin-52 pin-53 ]
//ia moreover, each "encoder" will be represented by 2 bits
//ia (with the entire port we will manage 4 encoders).
//ia hence, we manage each "pair" of pins as the encoder in exercise 6
//ia I (irvin) declare the folling pin-encoder mapping:
//ia [ pin-52 pin-53 ] -> encoder_0
//ia [ pin-50 pin-51 ] -> encoder_1
//ia [ pin-11 pin-10 ] -> encoder_2
//ia [ pin-13 pin-12 ] -> encoder_3

//ia port status
volatile uint8_t portb_prev_reading;
volatile uint8_t portb_curr_reading;

//ia PORTB interrupt stuff
#define PIN_MASK 0xFF                    //ia we use all pins in the port
#define MAX_ENCODERS 4                   //ia max number of encoder that we can handle
volatile uint16_t portb_int_counter = 0; //ia counter (just in case)

//ia the good old transition table
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

// encoder counters (16 bits, but could be more)
volatile uint16_t encoder_counts[MAX_ENCODERS];

// shift routine adjusted with sign
// if shift factor is negative, it performs a right shift
static inline uint8_t shiftRightWithSign(uint8_t value, int8_t shift_factor) {
  return (shift_factor >= 0) ? (value >> shift_factor) : value << (-shift_factor);
}

//ia aux function that handles the event and does the job
static inline void ENCODER_update(uint8_t encoder_num) {
  //ia isolate from the reading the bits of the encoder and construct the index
  //ia expasion for encoder_num = 0:
  //   prev_reading = [aabb ccxx] -> shift_factor = -2 -> shifting result = [bbcc xx00]
  //   curr_reading = [ddee ffyy] -> shift_factor =  0 -> shifting result = [ddee ffyy]
  uint8_t idx=
    // shift the previous value of (enc_num-1)*2 positions and mask it with 00001100
    (shiftRightWithSign(portb_prev_reading,(2*(encoder_num-1)))&0x0c)
    // shift the current value of  enc_num*2 positions and mask it with 00000011
    | (shiftRightWithSign(portb_curr_reading,(2*(encoder_num)))&0x03); 
  encoder_counts[encoder_num]+=_transition_table[idx];
}

//ia interrupt service routine for position PCINT0 -> monitoring entire portb
//ia since we do not want to loose any of the transitions and the ENCODER_update is very small
//ia we do the entire processing inside the ISR
ISR(PCINT0_vect) {
  portb_prev_reading = portb_curr_reading;
  portb_curr_reading = PINB; // we read 4 encoders
    
  for (int encoder_num = 0; encoder_num < MAX_ENCODERS; ++encoder_num) {
    ENCODER_update(encoder_num);
  }
    
  ++portb_int_counter;
}

//ia timer 5 interrupt stuff
#define TIMER_DURATION_MS 1000            //ia timer spawning time
volatile uint8_t timer_int_occurred = 0;  //ia flag
volatile uint16_t timer_int_counter = 0;  //ia cnt (just in case)

//ia interrupt service routine for timer 5 OCR
ISR(TIMER5_COMPA_vect) {
  timer_int_occurred = 1;
  ++timer_int_counter;
}

//ia auxiliary function to log the status and the encoders
void printStatus(void) {
  char string_to_write[80];
  
  //ia compose a string
  UART_putString((uint8_t*)string_to_write);
  sprintf(string_to_write,
          "t_int: %05u, t_enc:%05u, encoders: %05u %05u %05u %05u\n",
          timer_int_counter,
          portb_int_counter,
          encoder_counts[0], encoder_counts[1], encoder_counts[2], encoder_counts[3]);
  
  //ia print the string on the uart
  UART_putString((uint8_t*)string_to_write);
}


int main(void){
  //ia initialize encoder structures
  for (uint8_t encoder_num = 0;  encoder_num< MAX_ENCODERS; ++encoder_num) {
    encoder_counts[encoder_num] = 0;
  }
  
  //ia initialize all the peripherals
  //ia first the uart
  UART_init();

  //ia configure the timer according to example 03
  TCCR5A = 0;
  TCCR5B = (1 << WGM52) | (1 << CS50) | (1 << CS52); 
  uint16_t ocrval=(uint16_t)(15.62*TIMER_DURATION_MS);
  OCR5A = ocrval;

  //ia then the port  
  DDRB &= ~PIN_MASK; //set PIN_MASK pins as input
  PORTB |= PIN_MASK; //enable pull up resistors

  //ia finally install interrupts
  cli();
  PCICR |= (1 << PCIE0); // set interrupt on change, looking up PCMSK0
  PCMSK0 |= PIN_MASK;    // set PCINT0 to trigger an interrupt on state change
  TIMSK5 |= (1 << OCIE5A); //ia install the timer interrupt
  sei();

  //ia done
  UART_putString((uint8_t*)"initialization done!\n");

  //ia start the super loop
  while (1) {
    //ia check if it's time to say something
    if (timer_int_occurred) {
      printStatus();
      timer_int_occurred = 0; //ia interrupt has been served
    }
  }
}
