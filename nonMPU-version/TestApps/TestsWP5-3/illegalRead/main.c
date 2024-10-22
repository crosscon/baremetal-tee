#include <msp430.h>

int main(void){
    __asm("MOV #0x1100, R9"); //Load the 0xc400 address into R9, which points to the TEE code
    __asm("MOV @R9, R8"); //Attempt to write to the TEE code

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