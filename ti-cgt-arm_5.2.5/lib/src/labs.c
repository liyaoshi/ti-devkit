/* labs function */
#include <stdlib.h>
#include <yvals.h>
_STD_BEGIN

long (labs)(long i)
	{	/* compute absolute value of long argument */
	return (i < 0 ? -i : i);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
