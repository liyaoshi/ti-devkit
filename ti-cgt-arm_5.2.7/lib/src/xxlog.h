/* xxlog.h -- common log[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(log))(FTYPE x)
	{	/* compute ln(x) */
	return (FNAME(Log)(x, 0));
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
