#include <msp430.h>
#include <string.h>
//#include "aux_fun.h"
#define CHUNK_SIZE 64
#define TOTAL_LEN_LEN 8
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
typedef signed int int16_t;
typedef signed char int8_t;
typedef unsigned char bool;

void calc_sha_256(uint8_t hash[32], const void *input, size_t len);
/*
 * ABOUT bool: this file does not use bool in order to be as pre-C99 compatible as possible.
 */

/* https://github.com/amosnier/sha-2
 * Comments from pseudo-code at https://en.wikipedia.org/wiki/SHA-2 are reproduced here.
 * When useful for clarification, portions of the pseudo-code are reproduced here too.
 */

/*
 * Initialize array of round constants:
 * (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
 */
static const uint32_t k[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

struct buffer_state {
    const uint8_t * p;
    size_t len;
    size_t total_len;
    int single_one_delivered; /* bool */
    int total_len_delivered; /* bool */
};

static inline uint32_t right_rot(uint32_t value, unsigned int count)
{
    /*
     * Defined behaviour in standard C for all count where 0 < count < 32,
     * which is what we need here.
     */
    return value >> count | value << (32 - count);
}

static void init_buf_state(struct buffer_state * state, const void * input, size_t len)
{
    state->p = input;
    state->len = len;
    state->total_len = len;
    state->single_one_delivered = 0;
    state->total_len_delivered = 0;
}

/* Return value: bool */
static int calc_chunk(uint8_t chunk[CHUNK_SIZE], struct buffer_state * state)
{
    size_t space_in_chunk;

    if (state->total_len_delivered) {
        return 0;
    }

    if (state->len >= CHUNK_SIZE) {
        memcpy(chunk, state->p, CHUNK_SIZE);
        state->p += CHUNK_SIZE;
        state->len -= CHUNK_SIZE;
        return 1;
    }

    memcpy(chunk, state->p, state->len);
    chunk += state->len;
    space_in_chunk = CHUNK_SIZE - state->len;
    state->p += state->len;
    state->len = 0;

    /* If we are here, space_in_chunk is one at minimum. */
    if (!state->single_one_delivered) {
        *chunk++ = 0x80;
        space_in_chunk -= 1;
        state->single_one_delivered = 1;
    }

    /*
     * Now:
     * - either there is enough space left for the total length, and we can conclude,
     * - or there is too little space left, and we have to pad the rest of this chunk with zeroes.
     * In the latter case, we will conclude at the next invokation of this function.
     */
    if (space_in_chunk >= TOTAL_LEN_LEN) {
        const size_t left = space_in_chunk - TOTAL_LEN_LEN;
        size_t len = state->total_len;
        int i;
        memset(chunk, 0x00, left);
        chunk += left;

        /* Storing of len * 8 as a big endian 64-bit without overflow. */
        chunk[7] = (uint8_t) (len << 3);
        len >>= 5;
        for (i = 6; i >= 0; i--) {
            chunk[i] = (uint8_t) len;
            len >>= 8;
        }
        state->total_len_delivered = 1;
    } else {
        memset(chunk, 0x00, space_in_chunk);
    }

    return 1;
}

/*
 * Limitations:
 * - Since input is a pointer in RAM, the data to hash should be in RAM, which could be a problem
 *   for large data sizes.
 * - SHA algorithms theoretically operate on bit strings. However, this implementation has no support
 *   for bit string lengths that are not multiples of eight, and it really operates on arrays of bytes.
 *   In particular, the len parameter is a number of bytes.
 */
void calc_sha_256(uint8_t hash[32], const void * input, size_t len)
{

    uint32_t h[] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
    unsigned i, j;

    /* 512-bit chunks is what we will operate on. */
    uint8_t chunk[64];

    struct buffer_state state;

    init_buf_state(&state, input, len);

    while (calc_chunk(chunk, &state)) {
        uint32_t ah[8];

        const uint8_t *p = chunk;

        /* Initialize working variables to current hash value: */
        for (i = 0; i < 8; i++)
            ah[i] = h[i];


        for (i = 0; i < 4; i++) {
            uint32_t w[16];

            for (j = 0; j < 16; j++) {
                if (i == 0) {
                    w[j] = (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
                        (uint32_t) p[2] << 8 | (uint32_t) p[3];
                    p += 4;
                } else {
                    /* Extend the first 16 words into the remaining 48 words w[16..63] of the message schedule array: */
                    const uint32_t s0 = right_rot(w[(j + 1) & 0xf], 7) ^ right_rot(w[(j + 1) & 0xf], 18) ^ (w[(j + 1) & 0xf] >> 3);
                    const uint32_t s1 = right_rot(w[(j + 14) & 0xf], 17) ^ right_rot(w[(j + 14) & 0xf], 19) ^ (w[(j + 14) & 0xf] >> 10);
                    w[j] = w[j] + s0 + w[(j + 9) & 0xf] + s1;
                }
                const uint32_t s1 = right_rot(ah[4], 6) ^ right_rot(ah[4], 11) ^ right_rot(ah[4], 25);
                const uint32_t ch = (ah[4] & ah[5]) ^ (~ah[4] & ah[6]);
                const uint32_t temp1 = ah[7] + s1 + ch + k[i << 4 | j] + w[j];
                const uint32_t s0 = right_rot(ah[0], 2) ^ right_rot(ah[0], 13) ^ right_rot(ah[0], 22);
                const uint32_t maj = (ah[0] & ah[1]) ^ (ah[0] & ah[2]) ^ (ah[1] & ah[2]);
                const uint32_t temp2 = s0 + maj;

                ah[7] = ah[6];
                ah[6] = ah[5];
                ah[5] = ah[4];
                ah[4] = ah[3] + temp1;
                ah[3] = ah[2];
                ah[2] = ah[1];
                ah[1] = ah[0];
                ah[0] = temp1 + temp2;
            }
        }

        /* Add the compressed chunk to the current hash value: */
        for (i = 0; i < 8; i++)
            h[i] += ah[i];
    }

    /* Produce the final hash value (big-endian): */
    for (i = 0, j = 0; i < 8; i++)
    {
        hash[j++] = (uint8_t) (h[i] >> 24);
        hash[j++] = (uint8_t) (h[i] >> 16);
        hash[j++] = (uint8_t) (h[i] >> 8);
        hash[j++] = (uint8_t) h[i];
    }
}
__attribute__ ((naked,section(".crt_0010init")))
void __gcc_disable_watchdog() {
    WDTCTL = (WDTPW + WDTHOLD);
}
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P4OUT &= 0x00;
    P4DIR |= BIT2; //Set up also analyser
    P4OUT |= BIT2; //Start logical analyser

    uint8_t hash[32];
    calc_sha_256(hash, "GDReWGcDRLww2kr1s1EghwwJDwypvufEw8TbRZ70elWBVFzbSuYvIEeG0i1i", 60);
    P4OUT &= (~BIT2); //Stop analyser
    while(1);
}
