/* xxllrint.h -- common llrint[fl] functionality */
#include <fenv.h>
#include <limits.h>
#include "xmath.h"
_STD_BEGIN

#define MYMIN	(-_LLONG_MAX - _C2)	/* LLONG_MIN */
#define MYMAX	_LLONG_MAX	/* LLONG_MAX */

_Longlong (FFUN(llrint))(FTYPE x)
	{	/* round x according to current mode, raising inexact */
	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
	case _INFCODE:
		_Feraise(_FE_INVALID);
	case 0:
		return (0);
	default:	/* finite fraction */
		_Feraise(_FE_INEXACT);
		switch (fegetround())
			{	/* round according to current mode */
		case FE_DOWNWARD:
			if (x < FLIT(0.0))
				x -= FLIT(1.0);
			break;
		case FE_TONEAREST:
			if (x < FLIT(0.0))
				x -= FLIT(0.5);
			else
				x += FLIT(0.5);
			break;
		case FE_TOWARDZERO:
			break;
		case FE_UPWARD:
			if (FLIT(0.0) < x)
				x += FLIT(1.0);
			}
		FNAME(Dint)(&x, 0);
		if (x < (FTYPE)MYMIN || (FTYPE)MYMAX < x)
			_Feraise(_FE_INVALID);
		return ((_Longlong)x);
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
