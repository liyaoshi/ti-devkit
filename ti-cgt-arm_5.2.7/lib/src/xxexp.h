/* xxexp1.h -- common exp[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(exp))(FTYPE x)
	{	/* compute e^x */
	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
		return (x);
	case _INFCODE:
		return (FISNEG(x) ? FLIT(0.0) : x);
	case 0:
		return (FLIT(1.0));
	default:	/* finite */
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
