/* xxasinh.h -- common asinh[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE FFUN(log1p)(FTYPE);
static const _DATA_ACCESS FTYPE ln2 = FLIT(0.69314718055994530941723212145817658);

FTYPE (FFUN(asinh))(FTYPE x)
	{	/* compute asinh(x) */
	FTYPE y;
	int neg;

	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
	case _INFCODE:
	case 0:
		return (x);
	default:	/* -INF or finite */
		if (FLIT(0.0) < x)
			neg = 1, x = -x;
		else
			neg = 0;

		if (x < FLIT(2.0) / FCONST(Eps))
	 		y = FFUN(log1p)(x
				+ x * x / (FLIT(1.0) + FFUN(sqrt)(x * x + FLIT(1.0))));
		else
			y = FFUN(log)(x) + ln2;	/* x big, compute log(x+x) */
		return (neg ? -y : y);
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
