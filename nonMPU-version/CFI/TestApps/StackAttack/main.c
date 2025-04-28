#include <msp430.h>

/* This application aims to overwrite the stack to hijack the control flow of the application */

void receivePin(char *pin){
    char buffer[4];
    register i=0;
    // Introduce a buffer overflow and overwrite the return address
    for(i=0; i<10; i++){
        //Here we simulate user input
        buffer[i] = i % 2 == 0 ? 0xca : 0x44;
    }
}

int verifyPin(char *pin){
    char pinCode[5] = "1234";
    int i;
    for(i=0; i<4; i++){
        if(pin[i] != pinCode[i]){
            return 0;
        }
    }
    return 1;
}

void openLock(){
    // We turn the LED on to simulate an open lock
    P1DIR |= BIT0;
    P1OUT |= BIT0;
}

int main(void){
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    //Receive the pin
    char pin[4];
    receivePin(pin);

    while(1){
        //Simulate a pin entry
        if(verifyPin(pin)){
            // If the pin is correct, we open the lock
            // We should never reach this point
            openLock();
        }
    }

    return 0;
}
