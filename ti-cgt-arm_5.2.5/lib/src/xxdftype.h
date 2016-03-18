/****************************************************************************/
/*  xxdftype.h           v15.4.0I15142                                      */
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
/* xxdftype.h -- parameters for double floating-point type */
#include <xmath.h>


#define FTYPE	double
#define FCOMP	double
#define FCTYPE	_Dcomplex
#define FBITS	_TI_FBITS_DOUBLE
#define FMAXEXP	_TI_FMAXEXP_DOUBLE
#define FFUN(fun)	fun
#define FMACRO(x)	x
#define FNAME(fun)	_##fun
#define FCONST(obj)	_##obj._Double
#define FLIT(lit)	lit
#define FISNEG(exp)	DSIGN(exp)

 #if _IS_EMBEDDED
#define FCPTYPE	double_complex

 #else /* _IS_EMBEDDED */
#define FCPTYPE	complex<double>
 #endif /* _IS_EMBEDDED */


/*---------------------------------------------------------------------------*/
/* This code requires the target to support type-punning intrinsics.  These  */
/* intrinsics treat the bits of a floating-point value as if it were an      */
/* integer, to allow fast access to the sign, exponent, and fractional bits. */
/* We need to know whether the target has an intrinsic that can represent    */
/* the entire floating-point type with one integral type.                    */
/*---------------------------------------------------------------------------*/

#define FBIAS _TI_FBIAS_DOUBLE
#define __DOUBLE_SIZE _TI_DOUBLE_SIZE
#define __CHUNK_SIZE _TI_CHUNK_SIZE_DOUBLE
#define BIT_MASK _TI_BIT_MASK_DOUBLE
#define __SIGN_BIT_CHSZ _TI_SIGN_BIT_CHSZ_DOUBLE
#define FTOU _TI_FTOU_DOUBLE
#define UTOF _TI_UTOF_DOUBLE
#define EXP_BITS_MASK _TI_EXP_BITS_MASK_DOUBLE

#define SIGN_BIT_ZERO _TI_SIGN_BIT_ZERO_DOUBLE
#define BIASED_EXP _TI_BIASED_EXP_DOUBLE
#define FRAC_PART_IS_ZERO _TI_FRAC_PART_IS_ZERO_DOUBLE
#define DISCARD_N_FRAC_BITS _TI_DISCARD_N_FRAC_BITS_DOUBLE
#define DISCARD_EXP_AND_FRAC_PARTS _TI_DISCARD_EXP_AND_FRAC_PARTS_DOUBLE
#define UNBIASED_EXP _TI_UNBIASED_EXP_DOUBLE
#define BIASED_EXP_PART_IS_ZERO _TI_BIASED_EXP_PART_IS_ZERO_DOUBLE

 #define FRAC_PART_HI _TI_FRAC_PART_HI_DOUBLE
 #define FRAC_PART_LO _TI_FRAC_PART_LO_DOUBLE
 
/*---------------------------------------------------------------------------*/
/* Some TMS470 hardware has hardware for sqrt                                */
/*---------------------------------------------------------------------------*/
#define HAS_BF_SQRT _TI_HAS_BF_SQRT_DOUBLE
#define TYPED_SQRT _TI_TYPED_SQRT_DOUBLE

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
