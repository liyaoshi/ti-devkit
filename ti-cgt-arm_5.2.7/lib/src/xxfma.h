/* xxfma.h -- common fma[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(fma))(FTYPE x, FTYPE y, FTYPE z)
	{	/* compute x*y+z */
	FTYPE xp = x, yp = y, zp = z;
	short errx, erry, errz;
	short expx, expy, expz;

	if ((errx = FNAME(Dunscale)(&expx, &xp)) == _NANCODE)
		return (x);
	else if ((erry = FNAME(Dunscale)(&expy, &yp)) == _NANCODE)
		return (y);
	else if ((errz = FNAME(Dunscale)(&expz, &zp)) == _NANCODE)
		return (z);
	else if (errx == _INFCODE || erry == _INFCODE)
		if (errx != 0 && erry != 0
			&& (errz != _INFCODE || (FISNEG(x) ^ FISNEG(y)) == FISNEG(z)))
			return (x * y + z);
		else
			{	/* 0*INF, INF*0, INF-INF are invalid */
			_Feraise(_FE_INVALID);
			return (FCONST(Nan));
			}
	else if (errz == _INFCODE || errx == 0 || erry == 0 || errz == 0)
		return (x * y + z);	/* z==INF or at least one zero */
	else
		{	/* all finite */
		long expw = (long)expx + expy;

		if (2 * FBITS < expw - expz)
			return (x * y);	/* |x*y| >> |z| */
		else if (expw - expz < -2 * FBITS)
			return (z);	/* |x*y| << |z| */
		else if ((FISNEG(x) ^ FISNEG(y) ^ FISNEG(z)) == 0)
			return (x * y + z);	/* x*y same sign as z */
		else
			{	/* compute (x0+x1)*(y0+y1)+z */
			x = xp;
			FNAME(Dint)(&x, FBITS / 2);
			xp -= x;
			y = yp;
			FNAME(Dint)(&y, FBITS / 2);
			yp -= y;
			FNAME(Dscale)(&zp, expz - expw);
			zp += x * y;
			zp += x * yp;
			zp += xp * y;
			zp += xp * yp;
			FNAME(Dscale)(&zp, expw);
			return (zp);
			}
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
