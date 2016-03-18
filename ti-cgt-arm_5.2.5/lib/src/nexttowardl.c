/* nexttowardl function -- IEEE version */
#include "xmath.h"
_STD_BEGIN

#if defined(_32_BIT_LDOUBLE)
long double (nexttowardl)(long double x, long double y)
	{
            return (nexttowardf)(x, y);
        }
#else
long double (nexttowardl)(long double x, long double y)
	{	/* compute next value after x going toward y */
	unsigned short *const px = (unsigned short *)(char *)&x;

	if (0 < _LDtest(&x) || _LDtest(&y) == _NANCODE || x == y)
		;
	else if (x < y && 0.0L < x || y < x && x < 0.0L)
		{	/* increment magnitude of x */

 #if _DLONG == 0	/* assume IEEE 754 8 byte */
		if (
                    (++px[_D3] & 0xffff) == 0 && (++px[_D2] & 0xffff) == 0 &&
			(++px[_D1] & 0xffff) == 0
			&& (++px[_D0] & ~_DSIGN) == _DMAX << _DOFF)
			{	/* raise overflow and inexact */
			_Feraise(_FE_OVERFLOW);
			_Feraise(_FE_INEXACT);
			}

 #elif _DLONG == 1	/* assume IEEE 754 10 byte */
		if ((++px[_L4] & 0xffff) == 0
			&& (++px[_L3] & 0xffff) == 0
			&& (++px[_L2] & 0xffff) == 0
			&& (++px[_L1] & 0xffff) == 0)
			if ((++px[_L0] & _LMASK) < _LMAX)
				px[_L1] = 0x8000;	/* replace leading bit */
			else
				{	/* raise overflow and inexact */
				_Feraise(_FE_OVERFLOW);
				_Feraise(_FE_INEXACT);
				}

 #else	/* assume IEEE 754 16 byte */
		if ((++px[_L7] & 0xffff) == 0
			&& (++px[_L6] & 0xffff) == 0
			&& (++px[_L5] & 0xffff) == 0
			&& (++px[_L4] & 0xffff) == 0
			&& (++px[_L3] & 0xffff) == 0
			&& (++px[_L2] & 0xffff) == 0
			&& (++px[_L1] & 0xffff) == 0
			&& (++px[_L0] & _LMASK) == _LMAX)
			{	/* raise overflow and inexact */
			_Feraise(_FE_OVERFLOW);
			_Feraise(_FE_INEXACT);
			}
 #endif /* _DLONG */

		}
	else
		{	/* decrement magnitude of x */

 #if _DLONG == 0	/* assume IEEE 754 8 byte */
		if (x == 0.0)
			{	/* change zero to tiny of opposite sign */
			px[_D3] = 1;
			px[_D0] ^= _DSIGN;
			}
		else if (
                    (--px[_D3] & 0xffff) == 0xffff && 
                    (--px[_D2] & 0xffff) == 0xffff && 
                    (--px[_D1] & 0xffff) == 0xffff)
			--px[_D0];

 #elif _DLONG == 1	/* assume IEEE 754 10 byte */
		if (x == 0.0)
			{	/* change zero to tiny of opposite sign */
			px[_L4] = 1;
			px[_L0] ^= _DSIGN;
			}
		else if ((--px[_L4] & 0xffff) == 0xffff
			&& (--px[_L3] & 0xffff) == 0xffff
			&& (--px[_L2] & 0xffff) == 0xffff)
			{	/* decrement msw and renormalize as needed */
			if (--px[_L1] < 0x8000 && (px[_L0] & _LMASK) != 0)
				px[_L1] = 0xffff, --px[_L0];
			}

 #else	/* assume IEEE 754 16 byte */
		if (x == 0.0)
			{	/* change zero to tiny of opposite sign */
			px[_L7] = 1;
			px[_L0] ^= _DSIGN;
			}
		else if ((--px[_L7] & 0xffff) == 0xffff
			&& (--px[_L6] & 0xffff) == 0xffff
			&& (--px[_L5] & 0xffff) == 0xffff
			&& (--px[_L4] & 0xffff) == 0xffff
			&& (--px[_L3] & 0xffff) == 0xffff
			&& (--px[_L2] & 0xffff) == 0xffff
			&& (--px[_L1] & 0xffff) == 0xffff)
			--px[_L0];
 #endif /* _DLONG */

		if ((px[_L0] & _LMASK) == 0)
			{	/* zero or denormalized, raise underflow and inexact */
			_Feraise(_FE_UNDERFLOW);
			_Feraise(_FE_INEXACT);
			}
		}
	return (x);
	}
#endif /* defined(_32_BIT_LDOUBLE) */
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
