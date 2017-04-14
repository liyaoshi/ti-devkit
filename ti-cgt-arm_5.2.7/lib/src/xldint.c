/* _LDint function -- IEEE 754 version */
#include "xmath.h"
_STD_BEGIN

 #if _DLONG == 0
  #if defined(_32_BIT_LDOUBLE)
short _LDint(long double *px, short xexp)
	{	/* test and drop (scaled) fraction bits -- 32-bit */
	return _FDint((float *)px, xexp);
	}
  #elif !defined(_32_BIT_DOUBLE)
short _LDint(long double *px, short xexp)
	{	/* test and drop (scaled) fraction bits -- 64-bit */
	return _Dint((double *)px, xexp);
	}
  #else
short _LDint(long double *px, short xexp)
	{	/* test and drop (scaled) fraction bits -- 64-bit */
	unsigned short *ps = (unsigned short *)(char *)px;
	unsigned short frac;
	short xchar = (ps[_D0] & _DMASK) >> _DOFF;

	if (xchar == _DMAX)
		return ((ps[_D0] & _DFRAC) == 0 && ps[_D1] == 0
			&& ps[_D2] == 0 && ps[_D3] == 0
			? _INFCODE : _NANCODE);
	else if ((ps[_D0] & ~_DSIGN) == 0 && ps[_D1] == 0
		&& ps[_D2] == 0 && ps[_D3] == 0)
		return (0);
	xchar = (_DBIAS + 48 + _DOFF + 1) - xchar - xexp;
	if (xchar <= 0)
		return (0);	/* no frac bits to drop */
	else if ((48 + _DOFF + 1) <= xchar)
		{	/* all frac bits */
		ps[_D0] &= _DSIGN;
		ps[_D1] = 0;
		ps[_D2] = 0;
		ps[_D3] = 0;
		return (_FINITE);	/* report on frac, not result */
		}
	else
		{	/* strip out frac bits */
		static const _DATA_ACCESS unsigned short mask[] = {
			0x0000, 0x0001, 0x0003, 0x0007,
			0x000f, 0x001f, 0x003f, 0x007f,
			0x00ff, 0x01ff, 0x03ff, 0x07ff,
			0x0fff, 0x1fff, 0x3fff, 0x7fff};
		static const _DATA_ACCESS size_t sub[] = {_D3, _D2, _D1, _D0};
		frac = mask[xchar & 0xf];
		xchar >>= 4;
		frac &= ps[sub[xchar]];
		ps[sub[xchar]] ^= frac;
		switch (xchar)
			{	/* cascade through! */
		case 3:
			frac |= ps[_D1], ps[_D1] = 0;
		case 2:
			frac |= ps[_D2], ps[_D2] = 0;
		case 1:
			frac |= ps[_D3], ps[_D3] = 0;
			}
		return (frac != 0 ? _FINITE : 0);
		}
	 }
  #endif /* defined(_32_BIT_LDOUBLE) */

 #elif _DLONG == 1
short _LDint(long double *px, short xexp)
	{	/* test and drop (scaled) fraction bits -- 80-bit */
	unsigned short *ps = (unsigned short *)(char *)px;
	short xchar = ps[_L0] & _LMASK;

	if (xchar == _LMAX)
		return ((ps[_L1] & 0x7fff) == 0
			&& ps[_L2] == 0 && ps[_L3] == 0 && ps[_L4] == 0
			? _INFCODE : _NANCODE);
	else if (ps[_L1] == 0 && ps[_L2] == 0
		&& ps[_L3] == 0 && ps[_L4] == 0)
		return (0);
	xchar = (_LBIAS + 64) - xchar - xexp;
	if (xchar <= 0)
		return (0);	/* no frac bits to drop */
	else if (64 <= xchar)
		{	/* all frac bits */
		ps[_L0] &= _LSIGN;
		ps[_L1] = 0;
		ps[_L2] = 0;
		ps[_L3] = 0;
		ps[_L4] = 0;
		return (_FINITE);	/* report on frac, not result */
		}
	else
		{	/* strip out frac bits */
		static const _DATA_ACCESS unsigned short mask[] = {
			0x0000, 0x0001, 0x0003, 0x0007,
			0x000f, 0x001f, 0x003f, 0x007f,
			0x00ff, 0x01ff, 0x03ff, 0x07ff,
			0x0fff, 0x1fff, 0x3fff, 0x7fff};
		static const _DATA_ACCESS size_t sub[] = {_L4, _L3, _L2, _L1};
		unsigned short frac = mask[xchar & 0xf];

		xchar >>= 4;
		frac &= ps[sub[xchar]];
		ps[sub[xchar]] ^= frac;
		switch (xchar)
			{	/* cascade through! */
		case 3:
			frac |= ps[_L2], ps[_L2] = 0;
		case 2:
			frac |= ps[_L3], ps[_L3] = 0;
		case 1:
			frac |= ps[_L4], ps[_L4] = 0;
			}
		return (frac != 0 ? _FINITE : 0);
		}
		}

 #else /* 1 < _DLONG */
short _LDint(long double *px, short xexp)
	{	/* test and drop (scaled) fraction bits -- 128-bit SPARC */
	unsigned short *ps = (unsigned short *)(char *)px;
	short xchar = ps[_L0] & _LMASK;

	if (xchar == _LMAX)
		return (ps[_L1] == 0 && ps[_L2] == 0 && ps[_L3] == 0
			&& ps[_L4] == 0 && ps[_L5] == 0 && ps[_L6] == 0 && ps[_L7] == 0
			? _INFCODE : _NANCODE);
	else if (xchar == 0 && ps[_L1] == 0 && ps[_L2] == 0
		&& ps[_L3] == 0 && ps[_L4] == 0 && ps[_L5] == 0
		&& ps[_L6] == 0 && ps[_L7] == 0)
		return (0);
	xchar = (_LBIAS + 112 + 1) - xchar - xexp;
	if (xchar <= 0)
		return (0);	/* no frac bits to drop */
	else if ((112 + 1) <= xchar)
		{	/* all frac bits */
		ps[_L0] &= _LSIGN;
		ps[_L1] = 0;
		ps[_L2] = 0;
		ps[_L3] = 0;
		ps[_L4] = 0;
		ps[_L5] = 0;
		ps[_L6] = 0;
		ps[_L7] = 0;
		return (_FINITE);	/* report on frac, not result */
		}
	else
		{	/* strip out frac bits */
		static const _DATA_ACCESS unsigned short mask[] = {
			0x0000, 0x0001, 0x0003, 0x0007,
			0x000f, 0x001f, 0x003f, 0x007f,
			0x00ff, 0x01ff, 0x03ff, 0x07ff,
			0x0fff, 0x1fff, 0x3fff, 0x7fff};
		static const _DATA_ACCESS size_t sub[] =
			{_L7, _L6, _L5, _L4, _L3, _L2, _L1, _L0};
		unsigned short frac = mask[xchar & 0xf];

		xchar >>= 4;
		frac &= ps[sub[xchar]];
		ps[sub[xchar]] ^= frac;
		switch (xchar)
			{	/* cascade through! */
		case 7:
			frac |= ps[_L1], ps[_L1] = 0;
		case 6:
			frac |= ps[_L2], ps[_L2] = 0;
		case 5:
			frac |= ps[_L3], ps[_L3] = 0;
		case 4:
			frac |= ps[_L4], ps[_L4] = 0;
		case 3:
			frac |= ps[_L5], ps[_L5] = 0;
		case 2:
			frac |= ps[_L6], ps[_L6] = 0;
		case 1:
			frac |= ps[_L7], ps[_L7] = 0;
			}
		return (frac != 0 ? _FINITE : 0);
			}
		}
 #endif /* _DLONG */

_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
