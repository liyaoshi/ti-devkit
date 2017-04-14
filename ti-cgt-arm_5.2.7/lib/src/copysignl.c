/* copysignl function */
#include "xmath.h"
_STD_BEGIN

#if defined(_32_BIT_LDOUBLE)
long double (copysignl)(long double x, long double y)
	{
            return (copysignf)(x, y);
        }
#elif !defined(_32_BIT_DOUBLE)
long double (copysignl)(long double x, long double y)
	{
            return (copysign)(x, y);
        }
#else
long double (copysignl)(long double x, long double y)
	{	/* copy sign from y to x */
	unsigned short *const px = (unsigned short *)(char *)&x + _L0;
	unsigned short *const py = (unsigned short *)(char *)&y + _L0;

	*px = *px & ~_LSIGN | *py & _LSIGN;
	return (x);
	}
#endif /* defined(_32_BIT_LDOUBLE) */
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
