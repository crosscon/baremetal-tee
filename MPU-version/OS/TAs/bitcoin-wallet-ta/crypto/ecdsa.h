#ifndef __ECDSA_H__
#define __ECDSA_H__

#include <stdint.h>
#include "options.h"
#include "bignum.h"

// curve point x and y
typedef struct {
	bignum256 x, y;
} curve_point;

typedef struct jacobian_curve_point {
	bignum256 x, y, z;
} jacobian_curve_point;

typedef struct {

	bignum256 prime;       // prime order of the finite field
	curve_point G;         // initial curve point
	bignum256 order;       // order of G
	bignum256 order_half;  // order of G divided by 2
	int       a;           // coefficient 'a' of the elliptic curve
	bignum256 b;           // coefficient 'b' of the elliptic curve

#if USE_PRECOMPUTED_CP
	const curve_point cp[64][8];
#endif

} ecdsa_curve;

// 4 byte prefix + 40 byte data (segwit)
// 1 byte prefix + 64 byte data (cashaddr)
#define MAX_ADDR_RAW_SIZE 65
// bottle neck is cashaddr
// segwit is at most 90 characters plus NUL separator
// cashaddr: human readable prefix + 1 separator + 104 data + 8 checksum + 1 NUL
// we choose 130 as maximum (including NUL character)
#define MAX_ADDR_SIZE 130
// 4 byte prefix + 32 byte privkey + 1 byte compressed marker
#define MAX_WIF_RAW_SIZE (4 + 32 + 1)
// (4 + 32 + 1 + 4 [checksum]) * 8 / log2(58) plus NUL.
#define MAX_WIF_SIZE (57)

void point_copy(const curve_point *cp1, curve_point *cp2);
void point_add(const ecdsa_curve *curve, const curve_point *cp1, curve_point *cp2);
void point_double(const ecdsa_curve *curve, curve_point *cp);
void point_multiply(const ecdsa_curve *curve, const bignum256 *k, const curve_point *p, curve_point *res);
void point_set_infinity(curve_point *p);
int point_is_infinity(const curve_point *p);
int point_is_equal(const curve_point *p, const curve_point *q);
int point_is_negative_of(const curve_point *p, const curve_point *q);
void scalar_multiply(const ecdsa_curve *curve, const bignum256 *k, curve_point *res);
void conditional_negate(uint32_t cond, bignum256 *a, const bignum256 *prime);
void curve_to_jacobian(const curve_point *p, jacobian_curve_point *jp, const bignum256 *prime);
void jacobian_to_curve(const jacobian_curve_point *jp, curve_point *p, const bignum256 *prime);
void point_jacobian_add(const curve_point *p1, jacobian_curve_point *p2, const ecdsa_curve *curve);
void point_jacobian_double(jacobian_curve_point *p, const ecdsa_curve *curve);
void ecdsa_get_public_key33(const ecdsa_curve *curve, const uint8_t *priv_key, uint8_t *pub_key);
void ecdsa_get_public_key65(const ecdsa_curve *curve, const uint8_t *priv_key, uint8_t *pub_key);

#endif
