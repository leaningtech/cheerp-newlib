/* sf_sin.c -- float version of s_sin.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

#include "fdlibm.h"

/* Small multiples of pi/2 rounded to double precision. */
static const double
s1pio2 = 1*M_PI_2, /* 0x3FF921FB, 0x54442D18 */
s2pio2 = 2*M_PI_2, /* 0x400921FB, 0x54442D18 */
s3pio2 = 3*M_PI_2, /* 0x4012D97C, 0x7F3321D2 */
s4pio2 = 4*M_PI_2; /* 0x401921FB, 0x54442D18 */

#ifdef __STDC__
	float sinf(float x)
#else
	float sinf(x)
	float x;
#endif
{
	double y;
	__int32_t n,ix;

	GET_FLOAT_WORD(ix,x);

	unsigned sign = ix >> 31;

    /* |x| ~< pi/4 */
	ix &= 0x7fffffff;
	if(ix <= 0x3f490fd8) return __sindf(x);

	if (ix <= 0x407b53d1) {  /* |x| ~<= 5*pi/4 */
		if (ix <= 0x4016cbe3) {  /* |x| ~<= 3pi/4 */
			if (sign)
				return -__cosdf(x + s1pio2);
			else
				return __cosdf(x - s1pio2);
		}
		return __sindf(sign ? -(x + s2pio2) : -(x - s2pio2));
	}
	if (ix <= 0x40e231d5) {  /* |x| ~<= 9*pi/4 */
		if (ix <= 0x40afeddf) {  /* |x| ~<= 7*pi/4 */
			if (sign)
				return __cosdf(x + s3pio2);
			else
				return -__cosdf(x - s3pio2);
		}
		return __sindf(sign ? x + s4pio2 : x - s4pio2);
	}

    /* sin(Inf or NaN) is NaN */
	else if (!FLT_UWORD_IS_FINITE(ix)) return x-x;

    /* argument reduction needed */
	else {
	    n = __rem_pio2f(x,&y);
	    switch(n&3) {
		case 0: return  __sindf(y);
		case 1: return  __cosdf(y);
		case 2: return -__sindf(y);
		default:
			return -__cosdf(y);
	    }
	}
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double sin(double x)
#else
	double sin(x)
	double x;
#endif
{
	return (double) sinf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
