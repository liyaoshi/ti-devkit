/* div function */
#include <stdlib.h>
#include <yvals.h>
_STD_BEGIN

div_t (div)(int numer, int denom)
	{	/* compute int quotient and remainder */
	div_t val;
        #define fixneg (-1/2)
	val.quot = numer / denom;
	val.rem = numer - denom * val.quot;
	if (fixneg < 0 && val.quot < 0 && val.rem != 0)
		{	/* fix incorrect truncation */
		val.quot += 1;
		val.rem -= denom;
		}
	return (val);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
