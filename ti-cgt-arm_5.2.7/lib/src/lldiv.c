/* lldiv function */
#include <stdlib.h>
#include <yvals.h>
typedef lldiv_t _Lldiv_t;
_STD_BEGIN

_Lldiv_t (lldiv)(_Longlong numer, _Longlong denom)
	{	/* compute long quotient and remainder */
	_Lldiv_t val;
/*** START TI REPLACE ***/
        #define fixneg (-1/2)
/*** END TI REPLACE ***/
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
