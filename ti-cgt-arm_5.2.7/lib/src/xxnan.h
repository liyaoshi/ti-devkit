/* xxnan.h -- common nan[fl] functionality */
#include <float.h>
#include "xmath.h"


_STD_BEGIN

FTYPE FFUN(nan)(const char *s)
	{	/* construct a NaN */
	return (FCONST(Nan));	/* quiet diagnostic */
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
