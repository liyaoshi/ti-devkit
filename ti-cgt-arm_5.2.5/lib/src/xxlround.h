/* xxlround.h -- common lround[fl] functionality */
#include <limits.h>
#include "xmath.h"
_STD_BEGIN

long (FFUN(lround))(FTYPE x)
	{	/* round x to nearest */
	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
	case _INFCODE:
		_Feraise(_FE_INVALID);
	case 0:
		return (0);
	default:	/* finite fraction */
		if (x < FLIT(0.0))
			x -= FLIT(0.5);
		else
			x += FLIT(0.5);
		FNAME(Dint)(&x, 0);
		if (x < (FTYPE)LONG_MIN || (FTYPE)LONG_MAX < x)
			_Feraise(_FE_INVALID);
		return ((long)x);
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
