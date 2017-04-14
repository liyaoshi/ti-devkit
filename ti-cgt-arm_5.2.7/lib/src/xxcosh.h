/* xxcosh.h -- common cosh[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(cosh))(FTYPE x)
	{	/* compute cosh(x) */
	return (FNAME(Cosh)(x, FLIT(1.0)));
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
