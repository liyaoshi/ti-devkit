/* xxxdclass.h -- common _[FL]Dclass functionality */
#include "xmath.h"
_STD_BEGIN

int FNAME(Dclass)(FTYPE x)
	{	/* test floating-point classification */
	return (FNAME(Dtest)(&x));
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
