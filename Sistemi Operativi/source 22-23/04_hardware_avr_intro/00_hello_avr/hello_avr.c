#include <util/delay.h>
#include <stdio.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it
#include <avr/io.h>

int main(void){
  // this initializes the printf/uart thingies
  printf_init(); 
  int k=0;
  while(1){
    printf("hello %d\n",++k);
    _delay_ms(100); // from delay.h, wait 1 sec
  }
  
}
