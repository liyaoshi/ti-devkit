/* imaxabs function */
#include <inttypes.h>
#include <yvals.h>
_STD_BEGIN

intmax_t (imaxabs)(intmax_t i)
	{	/* compute absolute value of intmax_t argument */
	return (i < 0 ? -i : i);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
