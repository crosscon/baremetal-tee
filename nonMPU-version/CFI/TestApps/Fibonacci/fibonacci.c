
#include <msp430.h>

int fibbonacci(int n) {
   if(n == 0){
      return 0;
   } else if(n == 1) {
      return 1;
   } else {
      return (fibbonacci(n-1) + fibbonacci(n-2));
   }
}

int main() {
   WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
   P4OUT &= 0x00;
   P4DIR |= BIT2; //Set up also analyser
   P4OUT |= BIT2; //Start logical analyser

   int fib = fibbonacci(4);
   P4OUT &= (~BIT2);
   while(1);
}
