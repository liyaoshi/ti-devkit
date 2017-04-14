/* xxround.h -- common round[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(round))(FTYPE x)
	{	/* round x to nearest */
	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
	case _INFCODE:
	case 0:
		return (x);
	default:	/* finite fraction */
		if (x < FLIT(0.0))
			x -= FLIT(0.5);
		else
			x += FLIT(0.5);
		FNAME(Dint)(&x, 0);
		return (x);
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
