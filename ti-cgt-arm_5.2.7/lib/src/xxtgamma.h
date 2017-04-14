/* xxtgamma.h -- common tgamma[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE FNAME(Lgamma)(FTYPE x);
FTYPE FNAME(Tgamma)(FTYPE x);
extern FTYPE FNAME(Gamma_big);

static const FTYPE pi = FLIT(3.14159265358979323846264338327950287);

FTYPE (FFUN(tgamma))(FTYPE x)
	{	/* compute gamma(x) */
	FTYPE y = x;

	switch (FNAME(Dint)(&y, 0))
		{	/* test for special codes */
	case _NANCODE:
		return (x);
	case _INFCODE:
		if (!FISNEG(x))
			return (x);
		else
			{	/* -INF is invalid */
			_Feraise(_FE_INVALID);
			return (FCONST(Nan));
			}
	case 0:
		if (x == FLIT(0.0))
			{	/* gamma(0) is +/-INF */
			_Feraise(_FE_DIVBYZERO);
			return (FISNEG(x) ? -FCONST(Inf) : FCONST(Inf));
			}
		else if (x < FLIT(0.0))
			{	/* x a negative integer, undefined */
			_Feraise(_FE_INVALID);
			return (FCONST(Nan));
			}
	default:	/* result finite, may fall through */
		if (x < -FNAME(Gamma_big))
			{	/* large negative, use reflection relation */
			FTYPE z = x;

			y = x - y;
			FNAME(Dint)(&z, -1);
			if (x - z < FLIT(-1.0))
				y = -y;	/* floor(x) is odd negative integer */
			z = pi / (-x * FNAME(Sin)(pi * y, 0));
			x = -FNAME(Lgamma)(-x);
			FNAME(Exp)(&x, z, 0);
			return (z);
			}
		else if (x <= FNAME(Gamma_big))
			return (FNAME(Tgamma)(x));
		else
			{	/* large positive, exponentiate lgamma(x) */
			x = FNAME(Lgamma)(x);
			FNAME(Exp)(&x, FLIT(1.0), 0);
			return (x);
			}
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
