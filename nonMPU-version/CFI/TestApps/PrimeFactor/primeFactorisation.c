/*
    AUTHOR: Christian Bender
    DATE: 12.02.2019
    DESCRIPTION: This program calculates the prime factoriziation of a positive
   integer > 1
*/

#include <stdlib.h>
#include <msp430.h>
/* initial length of the dynamic array */
#define LEN 10

/* increasing range */
#define STEP 5

/*
    this type is for the representation of the prim factoriziation
    - its series/range of prime factors
    - its length : numbers of prime factors
*/
typedef struct data
{
    int *range;
    int length;
} range;
typedef range *Range;

/* int_fac : calculates the prime factoriziation of positive integers */
Range int_fact(int);

/* print_arr : prints the integer (heap) array*/
void print_arr(Range);

/* increase : increases the dynamic integer array */
int *increase(int *, int);

/* destroy: destroys the range-structure */
void destroy(Range);

/*
    main : simle frame program with a simple UI
*/


Range int_fact(int n)
{
    
    int len = LEN;
    int count = 0;
    int i = 0;
    
    int *range = (int *)malloc(sizeof(int) * len);
    
    Range pstr = (Range)malloc(sizeof(range));
    

    while (n % 2 == 0)
    {
        n /= 2;
        if (i < len)
        {
            range[i] = 2;
            i++;
        }
        else
        {
            range = increase(range, len);
            len += STEP;
            range[i] = 2;
            i++;
        }
        count++;
    }

    int j = 3;
    while (j * j <= n)
    {
        while (n % j == 0)
        {
            n /= j;
            if (i < len)
            {
                range[i] = j;
                i++;
            }
            else
            {
                range = increase(range, len);
                len += STEP;
                range[i] = j;
                i++;
            }
            count++;
        }

        j += 2;
    }

    if (n > 1)
    {
        if (i < len)
        {
            range[i] = n;
            i++;
        }
        else
        {
            range = increase(range, len);
            len += STEP;
            range[i] = n;
            i++;
        }
        count++;
    }

    pstr->range = range;
    pstr->length = count;
    return pstr;
}



int *increase(int *arr, int len)
{
    int *tmp = (int *)realloc(arr, sizeof(int) * (len + STEP));
    return tmp;
    //    assert(arr);
}

void destroy(Range r)
{
    free(r->range);
    free(r);
}
int main()
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    // Setup leds
    P4OUT &= 0x00;
    P4DIR |= BIT2; //Set up also analyser
    P4OUT |= BIT2; //STart analyser
    int n = 4095; /* for user input */
    
    Range r = int_fact(n);
    destroy(r);
    //register unsigned int stop = TA0R; // Stop timer
    P4OUT &= (~BIT2); //Stop analyser
    while(1);
}