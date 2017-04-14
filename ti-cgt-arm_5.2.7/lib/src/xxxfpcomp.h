/* xxxfpcomp.h -- common _[FL]Fpcomp functionality */
#include "xmath.h"
_STD_BEGIN

int FNAME(Fpcomp)(FTYPE x, FTYPE y)
	{	/* compare x and y */
	if (FNAME(Dtest)(&x) == _NANCODE || FNAME(Dtest)(&y) == _NANCODE)
		return (0);
	else if (x < y)
		return (_FP_LT);
	else if (y < x)
		return (_FP_GT);
	else
		return (_FP_EQ);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
