/* xxatan.h -- common atan[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(atan))(FTYPE x)
	{	/* compute atan(x) */
	unsigned short hex;
	static const  _DATA_ACCESS FTYPE piby2 = FLIT(1.5707963267948966192313216916397515);

	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
	case 0:
		return (x);
	case _INFCODE:
		return (FISNEG(x) ? -piby2 : piby2);
	default:	/* finite */
		if (x < FLIT(0.0))
			x = -x, hex = 0x8;
		else
			hex = 0x0;
		if (FLIT(1.0) < x)
			x = FLIT(1.0) / x, hex ^= 0x2;
		return (FNAME(Atan)(x, hex));
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
