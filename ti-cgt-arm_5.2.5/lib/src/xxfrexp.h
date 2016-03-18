/* xxfrexp.h -- common frexp[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(frexp))(FTYPE x, int *pexp)
	{	/* compute frexp(x, &i) */
	short binexp;

	FNAME(Dunscale)(&binexp, &x);
	*pexp = binexp;
	return (x);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
