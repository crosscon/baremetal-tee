/*
 * prime_factoriziation.h
 *
 *  Created on: Apr 27, 2021
 *      Author: beaglehot
 */

#ifndef INC_PRIME_FACTORIZATION_H_
#define INC_PRIME_FACTORIZATION_H_

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

#endif /* INC_PRIME_FACTORIZATION_H_ */
