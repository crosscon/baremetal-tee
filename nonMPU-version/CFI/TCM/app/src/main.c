/* 
    Author: Michele Grisafi
    Email: michele.grisafi@unitn.it
    License: MIT 
*/
/*
  This sample application simply calls the receiveUpdate API to
  initiate a secure update.
*/
#include <msp430.h>
#include <TCMhook.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer


  //P1OUT |= BIT0; //Red pin to signal end of program
  callReceiveUpdate();

  while(1);
  //
  return 0;
}
