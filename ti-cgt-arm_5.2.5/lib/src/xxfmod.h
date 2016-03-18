/****************************************************************************/
/*  xxfmod.h           v15.4.0I15142                                        */
/*                                                                          */
/* Copyright (c) 2010-2015 Texas Instruments Incorporated                   */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/****************************************************************************/
/* xxfmod.h -- common fmod[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(fmod))(FTYPE x, FTYPE y)
	{	/* compute fmod(x, y) */
	const short errx = FNAME(Dtest)(&x);
	const short erry = FNAME(Dtest)(&y);

	if (0 <= errx || 0 <= erry)
		{	/* x or y is 0, INF, or NAN */
		if (errx == _NANCODE)
			return (x);
		else if (erry == _NANCODE)
			return (y);
		else if (errx == _INFCODE || erry == 0)
			{	/* fmod(_INFCODE, y) or fmod(x, 0) */
			_Feraise(_FE_INVALID);
			return (FCONST(Nan));
			}
		else
			return (x);	/* fmod(0, nonzero) or fmod(finite, INF) */
		}
	else
		{	/* fmod(finite, finite) */
		FTYPE t;
		short n, neg, ychar, exp;

		if (y < FLIT(0.0))
			y = -y;
		if (x < FLIT(0.0))
			x = -x, neg = 1;
		else
			neg = 0;
		t = y;
		exp = BIASED_EXP(t);
		if (exp == EXP_BITS_MASK) ychar = 0;
		else if (0 < exp || (exp = FNAME(Dnorm)((unsigned short *)(char *)&t)) <= 0)
			ychar = exp - FBIAS; /* finite, reduce to [1/2, 1) */
		else ychar = 0; /* zero */

		n = 0;
		while (1)
		{	/* subtract |y| until |x|<|y| */
                        short xchar;
			t = x;
			if (n < 0) return (neg ? -x : x);

			exp = BIASED_EXP(t);
			if (exp == EXP_BITS_MASK) xchar = 0;
			else if (0 < exp || (exp = FNAME(Dnorm)((unsigned short *)(char *)&t)) <= 0)
				xchar = exp - FBIAS; /* finite, reduce to [1/2, 1) */
			else return (neg ? -x : x); /* zero */

			if( (n = xchar - ychar) < 0)
				return (neg ? -x : x);
			for (; 0 <= n; --n)
				{	/* try to subtract |y|*2^n */
				t = y, FNAME(Dscale)(&t, n);
				if (t <= x)
					{
					x -= t;
					break;
					}
				}
			}
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
