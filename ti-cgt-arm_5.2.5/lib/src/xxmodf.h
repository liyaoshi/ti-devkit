/****************************************************************************/
/*  xxmodf.h           v15.4.0I15142                                        */
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
/* xxmodf.h -- common modf[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(modf))(FTYPE x, FTYPE *pint)
	{	/* compute modf(x, &intpart) */
	FTYPE value=x;

	int signIsZero = SIGN_BIT_ZERO(value);  /* pos value */

	int exp = UNBIASED_EXP(value);

	if ((exp > -1) && (exp < (FBITS-1)))
        {
                /*-----------------------------------------------------------*/
                /* abs(x) >= 1 and x is finite.                              */
                /*-----------------------------------------------------------*/
                value = DISCARD_N_FRAC_BITS(value, FBITS - 1 - exp);

		*pint = value;

		if (FRAC_PART_IS_ZERO(x))
			return (signIsZero ? FLIT(0.0) : -FNAME(Zero));
		else
			return x - value;
	}
	else if ((exp >= (FBITS-1)) && (exp < FMAXEXP))
	{
                /*-----------------------------------------------------------*/
                /* This is a whole finite number.                            */
                /*-----------------------------------------------------------*/
		*pint = x;
		return (signIsZero ? FLIT(0.0) : -FNAME(Zero));
	}
	else if (exp <= -1)
	{
                /*-----------------------------------------------------------*/
                /* Test for positive or negative zero                        */
                /*-----------------------------------------------------------*/
		if (BIASED_EXP_PART_IS_ZERO(value) && FRAC_PART_IS_ZERO(value))
		{
			*pint = x;
			return (signIsZero ? FLIT(0.0) : -FNAME(Zero));
		}

                /*-----------------------------------------------------------*/
                /* abs(x) < 1; discard all fraction AND exponent bits to     */
                /* create a zero (denormals handled here)                    */
                /*-----------------------------------------------------------*/
		value = DISCARD_EXP_AND_FRAC_PARTS(value);
		*pint = value;
		return x - value;
	}
	else /* (exp == FMAXEXP) */
	{
                /*-----------------------------------------------------------*/
                /* Special cases: Infinity or NaN                            */
                /*-----------------------------------------------------------*/
		*pint = x;

		if (FRAC_PART_IS_ZERO(value))
		{
                        /*---------------------------------------------------*/
                        /* INFINITIES                                        */
                        /*---------------------------------------------------*/
			return (signIsZero ? FLIT(0.0) : -FNAME(Zero));
		}
		else
		{
                        /*---------------------------------------------------*/
                        /* NAN                                               */
                        /*---------------------------------------------------*/
			return x;
		}
	}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
