/*******************************************************************************
**
Name : 32-bit Math
* Purpose : Benchmark 32-bit math functions.
*
*******************************************************************************/
#include <math.h>
#include <msp430.h>


typedef unsigned long UInt32;
UInt32 add(UInt32 a, UInt32 b) {
    return (a + b);
}
UInt32 mul(UInt32 a, UInt32 b) {
    return (a * b);
}
UInt32 div(UInt32 a, UInt32 b) {
    return (a / b);
}
void main(void) {
    /****************** GENERAL DEBUG SET-UP *******************/
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P4OUT &= 0x00;
    P4DIR |= BIT2; //Set up also analyser


    P4OUT |= BIT2; //Start logical analyser
    /****************** START APPLICATION ********************/
    volatile UInt32 result[4];
    result[0] = 43125;
    result[1] = 14567;
    result[2] = add(result[0], result[1]);
    result[1] = mul(result[0], result[2]);
    result[3] = div(result[1], result[2]);
/**************** END OF APP ***************************/
    P4OUT &= (~BIT2); //Stop analyser
    while(1);
    return 0;
}