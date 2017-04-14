/* xxnextafter.h -- common nextafter[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE FFUN(nexttoward)(FTYPE, long double);

FTYPE (FFUN(nextafter))(FTYPE x, FTYPE y)
	{	/* compute next value after x going toward y */
	return (FFUN(nexttoward)(x, (long double)y));
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
