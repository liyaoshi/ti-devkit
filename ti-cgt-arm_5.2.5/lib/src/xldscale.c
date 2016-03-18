/* _LDscale function -- IEEE 754 version */
#include "xmath.h"
_STD_BEGIN

 #if _DLONG == 0
  #if defined(_32_BIT_LDOUBLE)
short _LDscale(long double *px, long lexp)
	{	/* scale *px by 2^lexp with checking -- 32-bit */
	return (_FDscale((float *)px, lexp));
	}
  #elif !defined(_32_BIT_DOUBLE)
short _LDscale(long double *px, long lexp)
	{	/* scale *px by 2^lexp with checking -- 64-bit */
	return (_Dscale((double *)px, lexp));
	}
  #else
short _LDscale(long double *px, long lexp)
	{	/* scale *px by 2^xexp with checking -- 64-bit */
	unsigned short *ps = (unsigned short *)(char *)px;
	short xchar = (short)((ps[_D0] & _DMASK) >> _DOFF);

	if (xchar == _DMAX)
		return ((short)((ps[_D0] & _DFRAC) != 0 || ps[_D1] != 0
                                || ps[_D2] != 0 || ps[_D3] != 0 ? _NANCODE : _INFCODE));
	else if (xchar == 0 && 0 < (xchar = _Dnorm(ps)))
		return (0);
	lexp += xchar;
	if (_DMAX <= lexp)
		{	/* overflow, return +/-INF */
		*px = ps[_D0] & _DSIGN ? -_Inf._Double : _Inf._Double;
		return (_INFCODE);
		}
	else if (0 < lexp)
		{	/* finite result, repack */
		ps[_D0] = (unsigned short)(ps[_D0] & ~_DMASK | (short)lexp << _DOFF);
		return (_FINITE);
		}
	else
		{	/* denormalized, scale */
		unsigned short sign = (unsigned short)(ps[_D0] & _DSIGN);
		ps[_D0] = (unsigned short)(1 << _DOFF | ps[_D0] & _DFRAC);
		if (--lexp < -(48+_DOFF))
			{	/* underflow, return +/-0 */
			ps[_D0] = sign, ps[_D1] = 0;
			ps[_D2] = 0, ps[_D3] = 0;
			return (0);
			}
		else
			{	/* nonzero, align fraction */
			short xexp;
			for (xexp = (short)lexp; xexp <= -16; xexp += 16)
				{	/* scale by words */
				ps[_D3] = ps[_D2], ps[_D2] = ps[_D1];
				ps[_D1] = ps[_D0], ps[_D0] = 0;
				}
			if ((xexp = (short)-xexp) != 0)
				{	/* scale by bits */
				ps[_D3] = (unsigned short)(ps[_D3] >> xexp
					| ps[_D2] << (16 - xexp));
				ps[_D2] = (unsigned short)(ps[_D2] >> xexp
					| ps[_D1] << (16 - xexp));
				ps[_D1] = (unsigned short)(ps[_D1] >> xexp
					| ps[_D0] << (16 - xexp));
				ps[_D0] >>= xexp;
				}
			ps[_D0] |= sign;
			return (_FINITE);
			}
		}
	}
  #endif /* defined(_32_BIT_LDOUBLE) */

 #elif _DLONG == 1
short _LDscale(long double *px, long lexp)
	{	/* scale *px by 2^lexp with checking -- 80-bit */
	unsigned short *ps = (unsigned short *)(char *)px;
	short xchar = ps[_L0] & _LMASK;

	if (xchar == _LMAX)
		return ((ps[_L1] & 0x7fff) != 0 || ps[_L2] != 0
			|| ps[_L3] != 0 || ps[_L4] != 0 ? _NANCODE : _INFCODE);
	else if (xchar == 0 && ps[_L1] == 0 && ps[_L2] == 0
		&& ps[_L3] == 0 && ps[_L4] == 0)
		return (0);
	lexp += xchar + _LDnorm(ps);
	if (_LMAX <= lexp)
		{	/* overflow, return +/-INF */
		*px = ps[_L0] & _LSIGN ? -_LInf._Long_double
			: _LInf._Long_double;
		return (_INFCODE);
		}
	else if (0 <= lexp)
		{	/* finite result, repack */
		ps[_L0] = ps[_L0] & _LSIGN | (short)lexp;
		return (_FINITE);
		}
	else
		{	/* denormalized, scale */
		ps[_L0] &= _LSIGN;
		if (lexp <= -64)
			{	/* underflow, return +/-0 */
			ps[_L1] = 0, ps[_L2] = 0;
			ps[_L3] = 0, ps[_L4] = 0;
			return (0);
			}
		else
			{	/* nonzero, align fraction */
			short xexp;
			for (xexp = lexp; xexp <= -16; xexp += 16)
				{	/* scale by words */
				ps[_L4] = ps[_L3], ps[_L3] = ps[_L2];
				ps[_L2] = ps[_L1], ps[_L1] = 0;
				}
			if ((xexp = -xexp) != 0)
				{	/* scale by bits */
				ps[_L4] = ps[_L4] >> xexp
					| ps[_L3] << 16 - xexp;
				ps[_L3] = ps[_L3] >> xexp
					| ps[_L2] << 16 - xexp;
				ps[_L2] = ps[_L2] >> xexp
					| ps[_L1] << 16 - xexp;
				ps[_L1] >>= xexp;
				}
			return (_FINITE);
			}
		}
	}

 #else	/* 1 < _DLONG */
short _LDscale(long double *px, long lexp)
	{	/* scale *px by 2^lexp with checking -- 128-bit SPARC */
	unsigned short *ps = (unsigned short *)(char *)px;
	short xchar = ps[_L0] & _LMASK;

	if (xchar == _LMAX)
		return (ps[_L1] != 0 || ps[_L2] != 0 || ps[_L3] != 0
			|| ps[_L4] != 0 || ps[_L5] != 0 || ps[_L6] != 0
			|| ps[_L7] != 0 ? _NANCODE : _INFCODE);
	else if (xchar == 0 && 0 < (xchar = _LDnorm(ps)))
		return (0);
	lexp += xchar;
	if (_LMAX <= lexp)
		{	/* overflow, return +/-INF */
		*px = ps[_L0] & _LSIGN ? -_LInf._Long_double
			: _LInf._Long_double;
		return (_INFCODE);
		}
	else if (0 <= lexp)
		{	/* finite result, repack */
		ps[_L0] = ps[_L0] & _LSIGN | (short)lexp;
		return (_FINITE);
		}
	else
		{	/* denormalized, scale */
		unsigned short sign = ps[_L0] & _LSIGN;

		ps[_L0] = 1;
		if (--lexp <= -112)
			{	/* underflow, return +/-0 */
			ps[_L1] = 0, ps[_L2] = 0, ps[_L3] = 0, ps[_L4] = 0;
			ps[_L5] = 0, ps[_L6] = 0, ps[_L7] = 0;
			return (0);
			}
		else
			{	/* nonzero, align fraction */
			short xexp;
			for (xexp = lexp; xexp <= -16; xexp += 16)
				{	/* scale by words */
				ps[_L7] = ps[_L6], ps[_L6] = ps[_L5];
				ps[_L5] = ps[_L4], ps[_L4] = ps[_L3];
				ps[_L3] = ps[_L2], ps[_L2] = ps[_L1];
				ps[_L1] = ps[_L0], ps[_L0] = 0;
				}
			if ((xexp = -xexp) != 0)
				{	/* scale by bits */
				ps[_L7] = ps[_L7] >> xexp
					| ps[_L6] << 16 - xexp;
				ps[_L6] = ps[_L6] >> xexp
					| ps[_L5] << 16 - xexp;
				ps[_L5] = ps[_L5] >> xexp
					| ps[_L4] << 16 - xexp;
				ps[_L4] = ps[_L4] >> xexp
					| ps[_L3] << 16 - xexp;
				ps[_L3] = ps[_L3] >> xexp
					| ps[_L2] << 16 - xexp;
				ps[_L2] = ps[_L2] >> xexp
					| ps[_L1] << 16 - xexp;
				ps[_L1] = ps[_L1] >> xexp
					| ps[_L0] << 16 - xexp;
				}
			ps[_L0] = sign;
			return (_FINITE);
			}
		}
	}
 #endif /* _DLONG */

_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
