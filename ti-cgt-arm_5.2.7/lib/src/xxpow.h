/* xxpow.h -- common pow[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(log))(FTYPE);	/* quash macro rescan */

FTYPE (FFUN(pow))(FTYPE x, FTYPE y)
	{	/* compute x^y */
	FTYPE yi = y;
	FTYPE yx, z;
	short n, xexp, zexp;
	short neg;
	short errx = FNAME(Dunscale)(&xexp, &x);
	const short erry = FNAME(Dint)(&yi, 0);
	static const _DATA_ACCESS short shuge = FMACRO(HUGE_EXP);
	static const _DATA_ACCESS FTYPE dhuge = FMACRO(HUGE_EXP);
	static const _DATA_ACCESS FTYPE ln2 = FLIT(0.69314718055994530941723212145817658);
	static const _DATA_ACCESS FTYPE rthalf = FLIT(0.70710678118654752440084436210484905);

	if (erry == 0 && y == FLIT(0.0)
		|| errx < 0 && xexp == 1
			&& (x == FLIT(0.5) || erry == _INFCODE && x == FLIT(-0.5)))
		return (FLIT(1.0));	/* x^0, 1^y, (-1)^-INF, (-1)^INF */
	else if (0 <= errx || 0 < erry)
		{	/* x == 0, INF, NAN; y == INF, NAN */
		if (errx == _NANCODE)
			return (x);	/* NAN^y */
		else if (erry == _NANCODE)
			return (y);	/* x^NAN */
		else if (errx == _INFCODE)
			if (!FISNEG(x))
				return (FISNEG(y) ? FLIT(0.0) : FCONST(Inf));	/* INF^y */
			else if (!FISNEG(y))
				return (erry == 0 && FNAME(Dint)(&yi, -1) < 0
					? -FCONST(Inf)
					: FCONST(Inf));	/* (-INF)^y, 0 < y */
			else
				return (erry == 0 && FNAME(Dint)(&yi, -1) < 0
					? FNAME(Zero) : FLIT(0.0));	/* (-INF)^y, y < 0 */
		else if (erry == _INFCODE)
			if (!FISNEG(y))
				return (xexp <= 0 ? FLIT(0.0) : FCONST(Inf));	/* x^INF */
			else
				return (xexp <= 0 ? FCONST(Inf) : FLIT(0.0));	/* x^-INF */
		else	/* x == 0 */
			if (!FISNEG(y))
				return (erry == 0 && FNAME(Dint)(&yi, -1) < 0 && FISNEG(x)
					? -FNAME(Zero) : FLIT(0.0));	/* 0^y, 0 < y */
			else
				{	/* 0^y, y < 0: report zero divide */
				_Feraise(_FE_DIVBYZERO);
				return (erry == 0 && FNAME(Dint)(&yi, -1) < 0 && FISNEG(x)
					? -FCONST(Inf) : FCONST(Inf));	/* 0^y, y < 0 */
				}
		}
	else if (FISNEG(x) && erry < 0)
		{	/* x^y, x < 0 && y not integer: report invalid */
		_Feraise(_FE_INVALID);
		return (FCONST(Nan));	/* x^y, x < 0 && y not integer */
		}

	if (FLIT(0.0) < x)
		neg = 0;
	else
		{	/* x < 0 */
		x = -x;
		neg = FNAME(Dint)(&yi, -1);	/* negate result for y negative integer */
		}

	if (x < rthalf)
		x *= FLIT(2.0), --xexp;	/* sqrt(.5) <= x <= sqrt(2) */
	n = 0, yx = FLIT(0.0);
	if (y <= -dhuge)
		zexp = xexp < 0 ? shuge : xexp == 0 ? 0 : -shuge;
	else if (dhuge <= y)
		zexp = xexp < 0 ? -shuge : xexp == 0 ? 0 : shuge;
	else
		{	/* y*log2(x) may be reasonable */
		FTYPE dexp = xexp;
		long zl = (long)(yx = y * dexp);

		if (zl != 0)
			{	/* form yx = y*xexp-zl carefully */
			yx = y, FNAME(Dint)(&yx, 16);
			yx = (yx * dexp - zl) + (y - yx) * dexp;
			}
		yx *= ln2;
		zexp = zl <= -shuge ? -shuge : zl < shuge ? zl : shuge;
		if ((n = (short)y) < -FMACRO(SAFE_EXP) || FMACRO(SAFE_EXP) < n)
			n = 0;
		}

	z = FLIT(1.0);	/* compute xfrac^n * 2^yx * 2^zexp */
	if (x != FLIT(1.0))
		{	/* z *= xfrac^n */
		if ((yi = y - n) != FLIT(0.0))
			yx += FFUN(log)(x) * yi;
		if (n < 0)
			n = -n;
		for (yi = x; ; yi *= yi)
			{	/* scale by x^2^n */
			if ((n & 1) != 0)
				z *= yi;
			if ((n >>= 1) == 0)
				break;
			}
		if (y < FLIT(0.0))
			z = FLIT(1.0) / z;
		}

	if (FNAME(Exp)(&yx, z, zexp) < 0)
		;	/* finite result */
	else if (y < FLIT(0.0))
		{	/* _Exp overflow, y < 0: report underflow */
		_Feraise(_FE_UNDERFLOW);
		yx = FLIT(0.0);
		}
	else
		{	/* _Exp overflow, 0 < y: report overlfow */
		_Feraise(_FE_OVERFLOW);
		yx = FCONST(Inf);
		}
	return (neg != 0 ? -yx : yx);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
