#include <msp430.h>



void main(){

    WDTCTL = WDTPW + WDTHOLD;

    
    P4OUT &= 0x00;
    P4DIR |= BIT2; //Set up also analyser
    
    
    P4OUT |= BIT2; //Start logical analyser
    for(int ciao =0; ciao < 1000; ciao++){
        __asm("nop");
    }
    P4OUT &= (~BIT2); //Stop logical analyser
    
    /* START CLEARING SECTION TO BOOST PERFORMANCE */
    FCTL3 = FWPW; //Unlock memory controller
    FCTL1 = FWPW + ERASE; //Set erase mode BANK
    __asm("MOV.W #0, &0x7000");
    while ((FCTL3 & BUSY) == BUSY); //Wait for erasure
    FCTL3 = FWPW+LOCK;

    P4OUT |= BIT2; //STart analyser
    for(int ciao =0; ciao < 1000; ciao++){
        __asm("nop");
    }
    P4OUT &= (~BIT2); //Stop analyser
    

    while(1);

}