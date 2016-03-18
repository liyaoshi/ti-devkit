/* xxlgamma.h -- common lgamma[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE FNAME(Lgamma)(FTYPE x);
FTYPE FNAME(Tgamma)(FTYPE x);
extern FTYPE FNAME(Gamma_big);

static const FTYPE pi = FLIT(3.14159265358979323846264338327950287);

FTYPE (FFUN(lgamma))(FTYPE x)
	{	/* compute ln(gamma(x)) */
	FTYPE y = x;

	switch (FNAME(Dint)(&y, 0))
		{	/* test for special codes */
	case _NANCODE:
		return (x);
	case _INFCODE:
		return (FCONST(Nan));
	case 0:
		if (x <= FLIT(0.0))
			{	/* x is zero or a negative integer, huge */
			_Feraise(_FE_DIVBYZERO);
			return (FCONST(Inf));
			}
	default:	/* result finite, may fall through */
		if (x < -FNAME(Gamma_big))
			return (FNAME(Log)(pi / (-x * FNAME(Sin)(pi * (y - x), 0)), 0)
				- FNAME(Lgamma)(-x));
		else if (x <= FNAME(Gamma_big))
			return (FNAME(Log)(FNAME(Tgamma)(x), 0));
		else
			return (FNAME(Lgamma)(x));
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
