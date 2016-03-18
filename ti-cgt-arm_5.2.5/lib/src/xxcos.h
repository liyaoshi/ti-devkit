/* xxcos.h -- common cos[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(cos))(FTYPE x)
	{	/* compute cos(x) */
	return (FNAME(Sin)(x, 1));
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
