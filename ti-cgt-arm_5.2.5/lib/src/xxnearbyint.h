/* xxnearbyint.h -- common nnearbyint[fl] functionality */
#include <fenv.h>
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(nearbyint))(FTYPE x)
	{	/* round x according to current mode, don't raise inexact */
	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
	case _INFCODE:
	case 0:
		return (x);
	default:
		 {	/* finite fraction */
		fenv_t env;

		feholdexcept(&env);
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
		feclearexcept(FE_INEXACT);
		feupdateenv(&env);
		return (x);
		 }
		}
		}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
