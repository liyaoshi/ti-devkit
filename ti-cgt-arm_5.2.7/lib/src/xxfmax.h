/* xxfmax.h -- common fmax[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(fmax))(FTYPE x, FTYPE y)
	{	/* compute larger of x and y */
	if (FNAME(Dtest)(&x) == _NANCODE)
		return (y);
	else if (FNAME(Dtest)(&y) == _NANCODE)
		return (x);
	else if (x < y)
		return (y);
	else
		return (x);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
