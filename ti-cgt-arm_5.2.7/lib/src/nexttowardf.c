/* nexttowardf function -- IEEE version */
#include "xmath.h"
_STD_BEGIN

float (nexttowardf)(float x, long double y)
	{	/* compute next value after x going toward y */
	unsigned short *const px = (unsigned short *)(char *)&x;

	if (0 < _FDtest(&x) || _LDtest(&y) == _NANCODE || x == y)
		;
	else if (x < y && 0.0F < x || y < x && x < 0.0F)
		{	/* increment magnitude of x */
		if ((++px[_F1] & 0xffff) == 0
			&& (++px[_F0] & ~_FSIGN) == _FMAX << _FOFF)
			{	/* raise overflow and inexact */
			_Feraise(_FE_OVERFLOW);
			_Feraise(_FE_INEXACT);
			}
		}
	else
		{	/* decrement magnitude of x */
		if (x == 0.0F)
			{	/* change zero to tiny of opposite sign */
			px[_F1] = 1;
			px[_F0] ^= _FSIGN;
			}
		else if ((--px[_F1] & 0xffff) == 0xffff)
			--px[_F0];
		if ((px[_F0] & _FMASK) == 0)
			{	/* zero or denormalized, raise underflow and inexact */
			_Feraise(_FE_UNDERFLOW);
			_Feraise(_FE_INEXACT);
			}
		}
	return (x);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
