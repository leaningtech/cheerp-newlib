/* sf_cos.c -- float version of s_cos.c.
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
c1pio2 = 1*M_PI_2, /* 0x3FF921FB, 0x54442D18 */
c2pio2 = 2*M_PI_2, /* 0x400921FB, 0x54442D18 */
c3pio2 = 3*M_PI_2, /* 0x4012D97C, 0x7F3321D2 */
c4pio2 = 4*M_PI_2; /* 0x401921FB, 0x54442D18 */

#ifdef __STDC__
	float cosf(float x)
#else
	float cosf(x)
	float x;
#endif
{
	double y;
	__int32_t n,ix;

	GET_FLOAT_WORD(ix,x);

	unsigned sign = ix >> 31;

    /* |x| ~< pi/4 */
	ix &= 0x7fffffff;
	if(ix <= 0x3f490fd8) return __cosdf(x);

	if (ix <= 0x407b53d1) {  /* |x| ~<= 5*pi/4 */
		if (ix > 0x4016cbe3)  /* |x|  ~> 3*pi/4 */
			return -__cosdf(sign ? x+c2pio2 : x-c2pio2);
		else {
			if (sign)
				return __sindf(x + c1pio2);
			else
				return __sindf(c1pio2 - x);
		}
	}
	if (ix <= 0x40e231d5) {  /* |x| ~<= 9*pi/4 */
		if (ix > 0x40afeddf)  /* |x| ~> 7*pi/4 */
			return __cosdf(sign ? x+c4pio2 : x-c4pio2);
		else {
			if (sign)
				return __sindf(-x - c3pio2);
			else
				return __sindf(x - c3pio2);
		}
	}

    /* cos(Inf or NaN) is NaN */
	else if (!FLT_UWORD_IS_FINITE(ix)) return x-x;

    /* argument reduction needed */
	else {
	    n = __rem_pio2f(x,&y);
	    switch(n&3) {
		case 0: return  __cosdf(y);
		case 1: return -__sindf(y);
		case 2: return -__cosdf(y);
		default:
		        return  __sindf(y);
	    }
	}
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double cos(double x)
#else
	double cos(x)
	double x;
#endif
{
	return (double) cosf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
