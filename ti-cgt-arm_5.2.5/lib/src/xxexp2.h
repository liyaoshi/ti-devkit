/* xxexp2.h -- common exp2[fl] functionality */
#include "xmath.h"
_STD_BEGIN

static const FTYPE ln2 = FLIT(0.69314718055994530941723212145817658);

FTYPE (FFUN(exp2))(FTYPE x)
	{	/* compute 2^x */
	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
		return (x);
	case _INFCODE:
		return (FISNEG(x) ? FLIT(0.0) : x);
	case 0:
		return (FLIT(1.0));
	default:	/* finite */
		x *= ln2;
		switch (FNAME(Exp)(&x, FLIT(1.0), 0))
			{	/* report over/underflow */
		case 0:
			_Feraise(_FE_UNDERFLOW);
			break;
		case _INFCODE:
			_Feraise(_FE_OVERFLOW);
			}
		return (x);
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
