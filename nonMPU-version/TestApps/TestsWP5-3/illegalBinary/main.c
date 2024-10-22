#include <msp430.h>

int main(void){
    __asm("BR #0x3400"); //Jump to RAM (0x3400 points to RAM!)
    P1OUT |= BIT0; // Set output to 1 (red LED)
    P4DIR |= BIT7; // Set 4.7 pin in output (green LED)
    short red = 4;
    short green = 0;
    for(int i = 0; i < 40; i++){
      if(red > 0){
        P1OUT ^= BIT0; // Toggle red LED
        red--;
        if(red == 0){
            green = 4;
        }
      }else if(green > 0){
        P4OUT ^= BIT7; // Toggle green LED
        green--;
        if(green == 0){
            red = 4;
        }
      } 
      for(int j = 0; j < 10000; j++){ // Delay{
        __asm("nop");
      }
    }
    while(1);
    return 0;
}
