/*******************************************************************************
**
Name : Matrix Multiplication
* Purpose : Benchmark multiplying a 3x4 matrix by a 4x5 matrix.
* Matrix contains 16-bit values.
*
*******************************************************************************/
#include <msp430.h> 

typedef unsigned short UInt16;
const UInt16 m1[3][4] = {
    {
        0x01,
        0x02,
        0x03,
        0x04
    },
    {
        0x05,
        0x06,
        0x07,
        0x08
    },
    {
        0x09,
        0x0A,
        0x0B,
        0x0C
    }
};
const UInt16 m2[4][5] = {
    {
        0x01,
        0x02,
        0x03,
        0x04,
        0x05
    },
    {
        0x06,
        0x07,
        0x08,
        0x09,
        0x0A
    },
    {
        0x0B,
        0x0C,
        0x0D,
        0x0E,
        0x0F
    },
    {
        0x10,
        0x11,
        0x12,
        0x13,
        0x14
    }
};
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P4OUT &= 0x00;
    P4DIR |= BIT2; //Set up also analyser


    P4OUT |= BIT2; //Start logical analyser
    int m, n, p;
    volatile UInt16 m3[3][5];
    for (m = 0; m < 3; m++) {
        for (p = 0; p < 5; p++) {
            m3[m][p] = 0;
            for (n = 0; n < 4; n++) {
                m3[m][p] += m1[m][n] * m2[n][p];
            }
        }
    }
    P4OUT &= (~BIT2); //Stop analyser
    while(1);
    return;
}