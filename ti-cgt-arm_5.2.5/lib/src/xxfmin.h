/* xxfmin.h -- common fmin[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(fmin))(FTYPE x, FTYPE y)
	{	/* compute larger of x and y */
	if (FNAME(Dtest)(&x) == _NANCODE)
		return (y);
	else if (FNAME(Dtest)(&y) == _NANCODE)
		return (x);
	else if (x < y)
		return (x);
	else
		return (y);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
