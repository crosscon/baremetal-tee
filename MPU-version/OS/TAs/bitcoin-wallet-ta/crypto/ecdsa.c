#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include <tee_client_api.h>
//#include <tee_internal_api_extensions.h>

#include "bignum.h"
#include "ecdsa.h"
#include "memzero.h"

// Set cp2 = cp1
void point_copy(const curve_point *cp1, curve_point *cp2)
{
	*cp2 = *cp1;
}


//////////////////////////////////////////////////////////////
// cp2 = cp1 + cp2
void point_add(const ecdsa_curve *curve, const curve_point *cp1, curve_point *cp2)
{
	bignum256 lambda, inv, xr, yr;

	if (point_is_infinity(cp1)) {
		return;
	}
	if (point_is_infinity(cp2)) {
		point_copy(cp1, cp2);
		return;
	}
	if (point_is_equal(cp1, cp2)) {
		point_double(curve, cp2);
		return;
	}
	if (point_is_negative_of(cp1, cp2)) {
		point_set_infinity(cp2);
		return;
	}

	bn_subtractmod(&(cp2->x), &(cp1->x), &inv, &curve->prime);
	bn_inverse(&inv, &curve->prime);
	bn_subtractmod(&(cp2->y), &(cp1->y), &lambda, &curve->prime);
	bn_multiply(&inv, &lambda, &curve->prime);

	// xr = lambda^2 - x1 - x2
	xr = lambda;
	bn_multiply(&xr, &xr, &curve->prime);
	yr = cp1->x;
	bn_addmod(&yr, &(cp2->x), &curve->prime);
	bn_subtractmod(&xr, &yr, &xr, &curve->prime);
	bn_fast_mod(&xr, &curve->prime);
	bn_mod(&xr, &curve->prime);

	// yr = lambda (x1 - xr) - y1
	bn_subtractmod(&(cp1->x), &xr, &yr, &curve->prime);
	bn_multiply(&lambda, &yr, &curve->prime);
	bn_subtractmod(&yr, &(cp1->y), &yr, &curve->prime);
	bn_fast_mod(&yr, &curve->prime);
	bn_mod(&yr, &curve->prime);

	cp2->x = xr;
	cp2->y = yr;
}
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// cp = cp + cp
void point_double(const ecdsa_curve *curve, curve_point *cp)
{
	bignum256 lambda, xr, yr;

	if (point_is_infinity(cp)) {
		return;
	}
	if (bn_is_zero(&(cp->y))) {
		point_set_infinity(cp);
		return;
	}

	// lambda = (3 x^2 + a) / (2 y)
	lambda = cp->y;
	bn_mult_k(&lambda, 2, &curve->prime);
	bn_inverse(&lambda, &curve->prime);

	xr = cp->x;
	bn_multiply(&xr, &xr, &curve->prime);
	bn_mult_k(&xr, 3, &curve->prime);
	bn_subi(&xr, -curve->a, &curve->prime);
	bn_multiply(&xr, &lambda, &curve->prime);

	// xr = lambda^2 - 2*x
	xr = lambda;
	bn_multiply(&xr, &xr, &curve->prime);
	yr = cp->x;
	bn_lshift(&yr);
	bn_subtractmod(&xr, &yr, &xr, &curve->prime);
	bn_fast_mod(&xr, &curve->prime);
	bn_mod(&xr, &curve->prime);

	// yr = lambda (x - xr) - y
	bn_subtractmod(&(cp->x), &xr, &yr, &curve->prime);
	bn_multiply(&lambda, &yr, &curve->prime);
	bn_subtractmod(&yr, &(cp->y), &yr, &curve->prime);
	bn_fast_mod(&yr, &curve->prime);
	bn_mod(&yr, &curve->prime);

	cp->x = xr;
	cp->y = yr;
}
//////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// set point to internal representation of point at infinity
void point_set_infinity(curve_point *p)
{
	bn_zero(&(p->x));
	bn_zero(&(p->y));
}
////////////////////////////////////////////////////////////

// return true iff p represent point at infinity
// both coords are zero in internal representation
int point_is_infinity(const curve_point *p)
{
	return bn_is_zero(&(p->x)) && bn_is_zero(&(p->y));
}


//////////////////////////////////////////////////////////////
// return true iff both points are equal
int point_is_equal(const curve_point *p, const curve_point *q)
{
	return bn_is_equal(&(p->x), &(q->x)) && bn_is_equal(&(p->y), &(q->y));
}

//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// returns true iff p == -q
// expects p and q be valid points on curve other than point at infinity
int point_is_negative_of(const curve_point *p, const curve_point *q)
{
	// if P == (x, y), then -P would be (x, -y) on this curve
	if (!bn_is_equal(&(p->x), &(q->x))) {
		return 0;
	}

	// we shouldn't hit this for a valid point
	if (bn_is_zero(&(p->y))) {
		return 0;
	}

	return !bn_is_equal(&(p->y), &(q->y));
}

//////////////////////////////////////////////////////////////

// Negate a (modulo prime) if cond is 0xffffffff, keep it if cond is 0.
// The timing of this function does not depend on cond.
void conditional_negate(uint32_t cond, bignum256 *a, const bignum256 *prime)
{
	int j;
	uint32_t tmp = 1;
	assert(a->val[8] < 0x20000);
	for (j = 0; j < 8; j++) {
		tmp += 0x3fffffff + 2*prime->val[j] - a->val[j];
		a->val[j] = ((tmp & 0x3fffffff) & cond) | (a->val[j] & ~cond);
		tmp >>= 30;
	}
	tmp += 0x3fffffff + 2*prime->val[j] - a->val[j];
	a->val[j] = ((tmp & 0x3fffffff) & cond) | (a->val[j] & ~cond);
	assert(a->val[8] < 0x20000);
}


//random.c
//////////////////////////////////////////////////////////////
// generate random K for signing/side-channel noise
static void generate_k_random(bignum256 *k, const bignum256 *prime) {
	do {
		int i;
		uint32_t random;
		for (i = 0; i < 8; i++) {
			TEE_GenerateRandom(&random, 4);
			k->val[i] = random & 0x3FFFFFFF;
		}
		TEE_GenerateRandom(&random, 4);
		k->val[8] = random & 0xFFFF;
		// check that k is in range and not zero.
	} while (bn_is_zero(k) || !bn_is_less(k, prime));
}

//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
void curve_to_jacobian(const curve_point *p, jacobian_curve_point *jp, const bignum256 *prime) {
	// randomize z coordinate
	generate_k_random(&jp->z, prime);

	jp->x = jp->z;
	bn_multiply(&jp->z, &jp->x, prime);
	// x = z^2
	jp->y = jp->x;
	bn_multiply(&jp->z, &jp->y, prime);
	// y = z^3

	bn_multiply(&p->x, &jp->x, prime);
	bn_multiply(&p->y, &jp->y, prime);
}

//////////////////////////////////////////////////////////////

void jacobian_to_curve(const jacobian_curve_point *jp, curve_point *p, const bignum256 *prime) {
	p->y = jp->z;
	bn_inverse(&p->y, prime);
	// p->y = z^-1
	p->x = p->y;
	bn_multiply(&p->x, &p->x, prime);
	// p->x = z^-2
	bn_multiply(&p->x, &p->y, prime);
	// p->y = z^-3
	bn_multiply(&jp->x, &p->x, prime);
	// p->x = jp->x * z^-2
	bn_multiply(&jp->y, &p->y, prime);
	// p->y = jp->y * z^-3
	bn_mod(&p->x, prime);
	bn_mod(&p->y, prime);
}

void point_jacobian_add(const curve_point *p1, jacobian_curve_point *p2, const ecdsa_curve *curve) {
	bignum256 r, h, r2;
	bignum256 hcby, hsqx;
	bignum256 xz, yz, az;
	int is_doubling;
	const bignum256 *prime = &curve->prime;
	int a = curve->a;

	assert (-3 <= a && a <= 0);

	
	xz = p2->z;
	bn_multiply(&xz, &xz, prime); // xz = z2^2
	yz = p2->z;
	bn_multiply(&xz, &yz, prime); // yz = z2^3
	
	if (a != 0) {
		az  = xz;
		bn_multiply(&az, &az, prime);   // az = z2^4
		bn_mult_k(&az, -a, prime);      // az = -az2^4
	}
	
	bn_multiply(&p1->x, &xz, prime);        // xz = x1' = x1*z2^2;
	h = xz;
	bn_subtractmod(&h, &p2->x, &h, prime);
	bn_fast_mod(&h, prime);
	// h = x1' - x2;

	bn_add(&xz, &p2->x);
	// xz = x1' + x2

	// check for h == 0 % prime.  Note that h never normalizes to
	// zero, since h = x1' + 2*prime - x2 > 0 and a positive
	// multiple of prime is always normalized to prime by
	// bn_fast_mod.
	is_doubling = bn_is_equal(&h, prime);

	bn_multiply(&p1->y, &yz, prime);        // yz = y1' = y1*z2^3;
	bn_subtractmod(&yz, &p2->y, &r, prime);
	// r = y1' - y2;

	bn_add(&yz, &p2->y);
	// yz = y1' + y2

	r2 = p2->x;
	bn_multiply(&r2, &r2, prime);
	bn_mult_k(&r2, 3, prime);
	
	if (a != 0) {
		// subtract -a z2^4, i.e, add a z2^4
		bn_subtractmod(&r2, &az, &r2, prime);
	}
	bn_cmov(&r, is_doubling, &r2, &r);
	bn_cmov(&h, is_doubling, &yz, &h);
	

	// hsqx = h^2
	hsqx = h;
	bn_multiply(&hsqx, &hsqx, prime);

	// hcby = h^3
	hcby = h;
	bn_multiply(&hsqx, &hcby, prime);

	// hsqx = h^2 * (x1 + x2)
	bn_multiply(&xz, &hsqx, prime);

	// hcby = h^3 * (y1 + y2)
	bn_multiply(&yz, &hcby, prime);

	// z3 = h*z2
	bn_multiply(&h, &p2->z, prime);

	// x3 = r^2 - h^2 (x1 + x2)
	p2->x = r;
	bn_multiply(&p2->x, &p2->x, prime);
	bn_subtractmod(&p2->x, &hsqx, &p2->x, prime);
	bn_fast_mod(&p2->x, prime);

	// y3 = 1/2 (r*(h^2 (x1 + x2) - 2x3) - h^3 (y1 + y2))
	bn_subtractmod(&hsqx, &p2->x, &p2->y, prime);
	bn_subtractmod(&p2->y, &p2->x, &p2->y, prime);
	bn_multiply(&r, &p2->y, prime);
	bn_subtractmod(&p2->y, &hcby, &p2->y, prime);
	bn_mult_half(&p2->y, prime);
	bn_fast_mod(&p2->y, prime);
}


//////////////////////////////////////////////////////////////
void point_jacobian_double(jacobian_curve_point *p, const ecdsa_curve *curve) {
	bignum256 az4, m, msq, ysq, xysq;
	const bignum256 *prime = &curve->prime;

	assert (-3 <= curve->a && curve->a <= 0);

	m = p->x;
	bn_multiply(&m, &m, prime);
	bn_mult_k(&m, 3, prime);

	az4 = p->z;
	bn_multiply(&az4, &az4, prime);
	bn_multiply(&az4, &az4, prime);
	bn_mult_k(&az4, -curve->a, prime);
	bn_subtractmod(&m, &az4, &m, prime);
	bn_mult_half(&m, prime);

	// msq = m^2
	msq = m;
	bn_multiply(&msq, &msq, prime);
	// ysq = y^2
	ysq = p->y;
	bn_multiply(&ysq, &ysq, prime);
	// xysq = xy^2
	xysq = p->x;
	bn_multiply(&ysq, &xysq, prime);

	// z3 = yz
	bn_multiply(&p->y, &p->z, prime);

	// x3 = m^2 - 2*xy^2
	p->x = xysq;
	bn_lshift(&p->x);
	bn_fast_mod(&p->x, prime);
	bn_subtractmod(&msq, &p->x, &p->x, prime);
	bn_fast_mod(&p->x, prime);

	// y3 = m*(xy^2 - x3) - y^4
	bn_subtractmod(&xysq, &p->x, &p->y, prime);
	bn_multiply(&m, &p->y, prime);
	bn_multiply(&ysq, &ysq, prime);
	bn_subtractmod(&p->y, &ysq, &p->y, prime);
	bn_fast_mod(&p->y, prime);
}

//////////////////////////////////////////////////////////////

// res = k * p
void point_multiply(const ecdsa_curve *curve, const bignum256 *k, const curve_point *p, curve_point *res)
{

	int i, j;
	static bignum256 a;
	uint32_t *aptr;
	uint32_t abits;
	int ashift;
	uint32_t is_even = (k->val[0] & 1) - 1;
	uint32_t bits, sign, nsign;
	static jacobian_curve_point jres;
	curve_point pmult[8];
	const bignum256 *prime = &curve->prime;

	uint32_t tmp = 1;
	uint32_t is_non_zero = 0;

	assert (bn_is_less(k, &curve->order));

	for (j = 0; j < 8; j++) {
		is_non_zero |= k->val[j];
		tmp += 0x3fffffff + k->val[j] - (curve->order.val[j] & is_even);
		a.val[j] = tmp & 0x3fffffff;
		tmp >>= 30;
	}
	is_non_zero |= k->val[j];
	a.val[j] = tmp + 0xffff + k->val[j] - (curve->order.val[j] & is_even);
	assert((a.val[0] & 1) != 0);

	// special case 0*p:  just return zero. We don't care about constant time.
	if (!is_non_zero) {
		point_set_infinity(res);
		return;
	}

	pmult[7] = *p;
	point_double(curve, &pmult[7]);
	// compute 3*p, etc by repeatedly adding p^2.
	pmult[0] = *p;
	for (i = 1; i < 8; i++) {
		pmult[i] = pmult[7];
		point_add(curve, &pmult[i-1], &pmult[i]);
	}

	aptr = &a.val[8];
	abits = *aptr;
	ashift = 12;
	bits = abits >> ashift;
	sign = (bits >> 4) - 1;
	bits ^= sign;
	bits &= 15;
	curve_to_jacobian(&pmult[bits>>1], &jres, prime);
	for (i = 62; i >= 0; i--) {
		// sign = sign(a[i+1])  (0xffffffff for negative, 0 for positive)
		// invariant jres = (-1)^sign sum_{j=i+1..63} (a[j] * 16^{j-i-1} * p)
		// abits >> (ashift - 4) = lowbits(a >> (i*4))

		point_jacobian_double(&jres, curve);
		point_jacobian_double(&jres, curve);
		point_jacobian_double(&jres, curve);
		point_jacobian_double(&jres, curve);

		// get lowest 5 bits of a >> (i*4).
		ashift -= 4;
		if (ashift < 0) {
			// the condition only depends on the iteration number and
			// leaks no private information to a side-channel.
			bits = abits << (-ashift);
			abits = *(--aptr);
			ashift += 30;
			bits |= abits >> ashift;
		} else {
			bits = abits >> ashift;
		}
		bits &= 31;
		nsign = (bits >> 4) - 1;
		bits ^= nsign;
		bits &= 15;

		// negate last result to make signs of this round and the
		// last round equal.
		conditional_negate(sign ^ nsign, &jres.z, prime);

		// add odd factor
		point_jacobian_add(&pmult[bits >> 1], &jres, curve);
		sign = nsign;
	}
	conditional_negate(sign, &jres.z, prime);
	jacobian_to_curve(&jres, res, prime);
	memzero(&a, sizeof(a));
	memzero(&jres, sizeof(jres));
}

void scalar_multiply(const ecdsa_curve *curve, const bignum256 *k, curve_point *res)
{
	point_multiply(curve, k, &curve->G, res);
}

void ecdsa_get_public_key33(const ecdsa_curve *curve, const uint8_t *priv_key, uint8_t *pub_key)
{
	curve_point R;
	bignum256 k;

	bn_read_be(priv_key, &k);
	// compute k*G
	scalar_multiply(curve, &k, &R);
	pub_key[0] = 0x02 | (R.y.val[0] & 0x01);
	bn_write_be(&R.x, pub_key + 1);
	memzero(&R, sizeof(R));
	memzero(&k, sizeof(k));
}

void ecdsa_get_public_key65(const ecdsa_curve *curve, const uint8_t *priv_key, uint8_t *pub_key)
{
	curve_point R;
	bignum256 k;

	bn_read_be(priv_key, &k);
	// compute k*G
	scalar_multiply(curve, &k, &R);
	pub_key[0] = 0x04;
	bn_write_be(&R.x, pub_key + 1);
	bn_write_be(&R.y, pub_key + 33);
	memzero(&R, sizeof(R));
	memzero(&k, sizeof(k));
}
