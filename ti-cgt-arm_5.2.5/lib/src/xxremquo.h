/* xxmremquo.h -- common remquo[fl] functionality */
#include <limits.h>
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(remquo))(FTYPE x, FTYPE y, int *pquo)
	{	/* compute remainder of x/y, quotient to *pquo */
	const short errx = FNAME(Dtest)(&x);
	const short erry = FNAME(Dtest)(&y);

	if (pquo != 0)
		*pquo = 0;
	if (0 <= errx || 0 <= erry)
		{	/* x or y is 0, INF, or NAN */
		if (errx == _NANCODE)
			return (x);
		else if (erry == _NANCODE)
			return (y);
		else if (errx == _INFCODE || erry == 0)
			{	/* INF/y or x/0 */
			_Feraise(_FE_INVALID);
			return (FCONST(Nan));
			}
		else
			return (x);	/* 0/nonzero or finite/INF */
		}
	else
		{	/* finite/finite */
		FTYPE t;
		short n, neg, ychar;
		unsigned long intpart;

		if (y < FLIT(0.0))
			y = -y;
		if (x < FLIT(0.0))
			x = -x, neg = 1;
		else
			neg = 0;
		for (t = y, FNAME(Dunscale)(&ychar, &t), n = 0, intpart = 0; ; )
			{	/* subtract |y| until |x|<|y| */
			short xchar;

			t = x;
			if (n < 0 || FNAME(Dunscale)(&xchar, &t) == 0
				|| (n = xchar - ychar) < 0)
				break;
			for (; 0 <= n; --n)

				{	/* try to subtract |y|*2^n */
				t = y, FNAME(Dscale)(&t, n);
				if (t <= x)
					{
					x -= t;
					intpart += 1 << n;
					break;
					}
				}
			}
		if (FLIT(0.0) < x)
			{	/* correct for |y| <= 2*|x| */
			t = FLIT(0.5) * y;
			if (t < x && FLIT(0.0) < t || t == x && (intpart & 1) != 0)
				x -= y, ++intpart;
			}
		if (pquo != 0)
			{	/* store integer part */
			int ans = (int)(intpart & INT_MAX);

			*pquo = neg ? -ans : ans;
			}
		return (neg ? -x : x);
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
