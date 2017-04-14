/****************************************************************************/
/*  xxfloor.h           v5.2.7                                              */
/*                                                                          */
/* Copyright (c) 2010-2016 Texas Instruments Incorporated                   */
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
/* xxfloor.h -- common floor[fl] functionality */
#include "xmath.h"
_STD_BEGIN

FTYPE (FFUN(floor))(FTYPE x)
	{	/* compute floor(x) */
	FTYPE value = x;
	
	int exp = UNBIASED_EXP(value);

	if (exp >= (FBITS-1))
        {
                /*-----------------------------------------------------------*/
                /* This is a whole number, infinity, or NaN.                 */
                /*-----------------------------------------------------------*/
		return x;
        }
	else if (exp > -1)
	{
                /*-----------------------------------------------------------*/
                /* abs(x) >= 1; discard (FBITS - 1 - exp) fraction bits      */
                /*-----------------------------------------------------------*/
                value = DISCARD_N_FRAC_BITS(value, FBITS - 1 - exp);

                /*-----------------------------------------------------------*/
                /* If this value was negative and not a whole number, round  */
                /* down.                                                     */
                /*-----------------------------------------------------------*/
		return ((!FRAC_PART_IS_ZERO(x) && (x < FLIT(0.0)) && (value != x)) ? 
                        value - FLIT(1.0) : value);
	}
	else /* exp <= -1 */
	{
                /*-----------------------------------------------------------*/
                /* Test if it is already positive or negative zero           */
                /*-----------------------------------------------------------*/
                if (BIASED_EXP_PART_IS_ZERO(value) && FRAC_PART_IS_ZERO(value))
		{
			return x;
		}

                /*-----------------------------------------------------------*/
                /* abs(x) < 1; discard all fraction AND exponent bits to     */
                /* create a zero (denormals handled here)                    */
                /*-----------------------------------------------------------*/
                value = DISCARD_EXP_AND_FRAC_PARTS(value);

                /*-----------------------------------------------------------*/
                /* If this value was negative and not a whole number, round  */
                /* down.                                                     */
                /*-----------------------------------------------------------*/
		return (x < FLIT(0.0) ? value - FLIT(1.0) : value);
	}


	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
