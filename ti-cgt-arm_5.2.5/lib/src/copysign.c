/* copysign function */
#include "xmath.h"
_STD_BEGIN

#if defined(_32_BIT_DOUBLE)
double (copysign)(double x, double y)
	{
            return (copysignf)(x, y);
        }
#else
double (copysign)(double x, double y)
	{	/* copy sign from y to x */
	unsigned short *const px = (unsigned short *)(char *)&x + _D0;
	unsigned short *const py = (unsigned short *)(char *)&y + _D0;

	*px = *px & ~_DSIGN | *py & _DSIGN;
	return (x);
	}
#endif /* defined(_32_BIT_DOUBLE) */
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
