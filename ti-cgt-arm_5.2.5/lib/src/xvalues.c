/* values used by math functions -- IEEE 754 version */
#include "xmath.h"
_STD_BEGIN

#if defined(_32_BIT_DOUBLE)

		/* macros */
 #define NBITS 23

 #if _D0 == 0 /* big-endian */
  #define INIT(w0)		{w0, 0}
  #define INIT2(w0, w1)	        {w0, w1}

 #else
  #define INIT(w0)		{0, w0}
  #define INIT2(w0, w1)	        {w1, w0}
 #endif /* _D0 == 0 */

		/* static data */
/* extern const */ _Dconst _Denorm = {INIT2(0, 1)};

/* extern const */ _Dconst _Eps = {
	INIT((_FBIAS - NBITS - 1) << _FOFF)};
/* extern const */ _Dconst _Hugeval = {INIT(_FMAX << _FOFF)};
/* extern const */ _Dconst _Inf = {INIT(_FMAX << _FOFF)};
/* extern const */ _Dconst _Nan = {INIT((_FMAX << _FOFF)
	| (1 << (_FOFF - 1)))};
/* extern const */ _Dconst _Snan = {INIT2(_FMAX << _FOFF, 1)};
/* extern const */ _Dconst _Rteps = { /* sqrt(EPSILON)/2 */
	INIT((_FBIAS - NBITS / 2) << _FOFF)};

#else /* !defined(_32_BIT_DOUBLE) */

		/* macros */
 #define NBITS	(48 + _DOFF)

 #if _D0 == 0
  #define INIT(w0)		{w0, 0, 0, 0}
  #define INIT2(w0, w1)		{w0, 0, 0, w1}

 #elif defined(__TMS470__) && defined(__TI_FPALIB_SUPPORT__)
  #define INIT(w0)	        {0, w0, 0, 0}
  #define INIT2(w0, w1)	        {0, w0, w1,0}        

 #else /* _D0 == 0 */
  #define INIT(w0)		{0, 0, 0, w0}
  #define INIT2(w0, w1) 	{w1, 0, 0, w0}
 #endif /* _D0 == 0 */

		/* static data */
/* extern const */ _Dconst _Denorm = {INIT2(0, 1)};
/* extern const */ _Dconst _Eps = {
	INIT((_DBIAS - NBITS - 1) << _DOFF)};
/* extern const */ _Dconst _Hugeval = {INIT(_DMAX << _DOFF)};
/* extern const */ _Dconst _Inf = {INIT(_DMAX << _DOFF)};
/* extern const */ _Dconst _Nan = {INIT((_DMAX << _DOFF)
	| (1 << (_DOFF - 1)))};
/* extern const */ _Dconst _Snan = {INIT2(_DMAX << _DOFF, 1)};
/* extern const */ _Dconst _Rteps = {
	INIT((_DBIAS - NBITS / 2) << _DOFF)};

#endif /* !defined(_32_BIT_DOUBLE) */

/*** START TI REPLACE ***/
/* extern const */ _DATA_ACCESS double _Xbig = (NBITS + 1) * 347L / 1000;
/* extern const */ _DATA_ACCESS double _Zero = 0.0;
/*** END TI REPLACE ***/
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
