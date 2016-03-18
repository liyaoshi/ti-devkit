/****************************************************************************/
/*  float.h          v15.4.0I15142                                          */
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
/* float.h standard header -- IEEE 754 version */
#ifndef _FLOAT
#define _FLOAT
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

#pragma diag_push
#pragma CHECK_MISRA("-18.4") /* union required for implementation */
#pragma CHECK_MISRA("-20.1") /* standard headers must define standard names */

_C_STD_BEGIN

		/* TYPE DEFINITIONS */
 #ifndef _DVALS
  #define _DVALS
typedef struct
	{	/* parameters for a floating-point type */
	int _Ddig, _Dmdig, _Dmax10e, _Dmaxe, _Dmin10e, _Dmine;
	union
		{	/* union of short array and all floats */
		unsigned short _Us[8];
		float _Float;
		double _Double;
		long double _Long_double;
		} _Deps, _Dmax, _Dmin;
	} _Dvals;
 #endif /* _DVALS */

		/* DECLARATIONS */
_C_LIB_DECL
extern /* const */ _DATA_ACCESS _Dvals _Dbl, _Flt, _Ldbl;
_END_C_LIB_DECL

		/* COMMON PROPERTIES */
#define FLT_RADIX		2

 #ifdef _FRND
  #define FLT_ROUNDS		(_FRND)

 #else /* _FRND */
  #define FLT_ROUNDS	(-1)	/* indeterminable */
 #endif /* _FRND */

#if _HAS_C9X || defined(_C99_MATH)

 #ifdef _FEVAL
  #define FLT_EVAL_METHOD	(_FEVAL)

 #else /* _FEVAL */
  #define FLT_EVAL_METHOD	(-1)	/* indeterminable */
 #endif /* _FEVAL */

 #if _DLONG == 0
  #define DECIMAL_DIG	16	/* 64-bit long double */

 #elif _DLONG == 1
  #define DECIMAL_DIG	21	/* 80-bit long double */

 #else /* 1 < _DLONG */
  #define DECIMAL_DIG	35	/* 128-bit SPARC long double */
 #endif /* _DLONG */

#endif /*_HAS_C9X || defined(_C99_MATH) */

/* ---------------------------------------------------------------*/
/* NOTE: Float, Double and Long properties have been modified for */
/* EABI compatibility.                                            */
/* ---------------------------------------------------------------*/

		/* float PROPERTIES */

#define FLT_DIG           (               6)   /* DECIMAL PRECISION         */
#define FLT_MANT_DIG      (              24)   /* BITS IN MANTISSA          */
#define FLT_MIN_EXP       (            -125)   /* SMALLEST EXPONENT         */
#define FLT_MAX_EXP       (             128)   /* LARGEST EXPONENT          */
#define FLT_MIN_10_EXP    (             -37)   /* MIN POWER OF 10           */
#define FLT_MAX_10_EXP    (              38)   /* MAX POWER OF 10           */
#define FLT_EPSILON       (1.192092896E-07F)   /* SMALLEST X WHERE 1+X != 1 */
#define FLT_MIN           (1.175494351E-38F)   /* SMALLEST POSITIVE VALUE   */
#define FLT_MAX           (3.402823466E+38F)   /* LARGEST POSITIVE VALUE    */

		/* double PROPERTIES */

#if defined(_32_BIT_DOUBLE)

#define DBL_EPSILON	  (1.192092896E-07)
#define DBL_MAX	          (1.175494351E-38)
#define DBL_MIN	          (3.402823466E+38)
#define DBL_DIG		(FLT_DIG)	/* double same as float */
#define DBL_MANT_DIG	(FLT_MANT_DIG)
#define DBL_MAX_10_EXP	(FLT_MAX_10_EXP) 
#define DBL_MAX_EXP	(FLT_MAX_EXP)
#define DBL_MIN_10_EXP	(FLT_MIN_10_EXP)
#define DBL_MIN_EXP	(FLT_MIN_EXP)

#else /* defined(_32_BIT_DOUBLE) */

#define DBL_DIG                      (   15)   /* DECIMAL PRECISION         */
#define DBL_MANT_DIG                 (   53)   /* BITS IN MANTISSA          */
#define DBL_MIN_EXP                  (-1021)   /* SMALLEST EXPONENT         */
#define DBL_MAX_EXP                  ( 1024)   /* LARGEST EXPONENT          */
#define DBL_MIN_10_EXP               ( -307)   /* MIN POWER OF 10           */
#define DBL_MAX_10_EXP               (  308)   /* MAX POWER OF 10           */
#define DBL_EPSILON (2.2204460492503131E-16)   /* SMALLEST X WHERE 1+X != 1 */
#define DBL_MIN    (2.2250738585072014E-308)   /* SMALLEST POSITIVE VALUE   */
#define DBL_MAX    (1.7976931348623157E+308)   /* LARGEST POSITIVE VALUE    */

#endif /* defined(_32_BIT_DOUBLE) */
		/* long double PROPERTIES */

 #if _DLONG == 0

#if defined(_32_BIT_DOUBLE)
  #define LDBL_EPSILON	        (1.192092896E-07L)
  #define LDBL_MAX	        (1.175494351E-38L)
  #define LDBL_MIN	        (3.402823466E+38L)
  #define LDBL_DIG	        (FLT_DIG)	/* double same as float */
  #define LDBL_MANT_DIG		(FLT_MANT_DIG)
  #define LDBL_MAX_10_EXP	(FLT_MAX_10_EXP)
  #define LDBL_MAX_EXP		(FLT_MAX_EXP)
  #define LDBL_MIN_10_EXP	(FLT_MIN_10_EXP)
  #define LDBL_MIN_EXP		(FLT_MIN_EXP)

#else  /* defined(_32_BIT_DOUBLE) */

 #define LDBL_DIG                     (   15 )  /* DECIMAL PRECISION         */
 #define LDBL_MANT_DIG                (   53 )  /* BITS IN MANTISSA          */
 #define LDBL_MIN_EXP                 (-1021 )  /* SMALLEST EXPONENT         */
 #define LDBL_MAX_EXP                 ( 1024 )  /* LARGEST EXPONENT          */
 #define LDBL_MIN_10_EXP              ( -307 )  /* MIN POWER OF 10           */
 #define LDBL_MAX_10_EXP              (  308 )  /* MAX POWER OF 10           */
 #define LDBL_EPSILON (2.2204460492503131E-16L)  /* SMALLEST X WHERE 1+X != 1 */
 #define LDBL_MIN   (2.2250738585072014E-308L)  /* SMALLEST POSITIVE VALUE   */
 #define LDBL_MAX   (1.7976931348623157E+308L)  /* LARGEST POSITIVE VALUE    */

#endif /* defined(_32_BIT_DOUBLE) */

 #elif _DLONG == 1

  #define LDBL_EPSILON	(0x8p-66L)
  #define LDBL_MAX		(0xf.fffffffffffffffp+16380L)
  #define LDBL_MIN		(0x8p-16385L)
  #define LDBL_DIG			(18)	/* _CSTD _Ldbl._Ddig */
  #define LDBL_MANT_DIG		(64)	/* _CSTD _Ldbl._Dmdig */
  #define LDBL_MAX_10_EXP	(4932)	/* _CSTD _Ldbl._Dmax10e */
  #define LDBL_MAX_EXP		(16384)	/* _CSTD _Ldbl._Dmaxe */
  #define LDBL_MIN_10_EXP	(-4931)	/* _CSTD _Ldbl._Dmin10e */
  #define LDBL_MIN_EXP		(-16381)	/* _CSTD _Ldbl._Dmine */

 #else /* 1 < _DLONG */

 /* NOTE: This portion has not been modified for EABI compatibility.  */

#if 199901L <= __STDC_VERSION__
        /* IEEE 16 byte, hidden bit */

  #if defined(__cplusplus) || defined(__GNUC__) && __GNUC__ < 3
   #define LDBL_EPSILON (_CSTD _Ldbl._Deps._Long_double)
   #define LDBL_MAX             (_CSTD _Ldbl._Dmax._Long_double)
   #define LDBL_MIN             (_CSTD _Ldbl._Dmin._Long_double)

  #else /* defined(__cplusplus) || defined(__GNUC__) && __GNUC__ < 3 */
   #define LDBL_EPSILON (0x8p-115L)
   #define LDBL_MAX            (0xf.fffffffffffffffffffffffffff8p+16380L)

   #if !defined(__EDG__) || 245 < __EDG_VERSION__
    #define LDBL_MIN            (0x8p-16385L)

   #else /* !defined(__EDG__) || 245 < __EDG_VERSION__ */
    #define LDBL_MIN            (_CSTD _Ldbl._Dmin._Long_double)
   #endif /* !defined(__EDG__) || 245 < __EDG_VERSION__ */

  #endif /* defined(__cplusplus) || defined(__GNUC__) && __GNUC__ < 3 */

 #else /* 199901L <= __STDC_VERSION__ */
  #if defined(_32_BIT_DOUBLE)
     #define LDBL_EPSILON         (FLT_EPSILON)
     #define LDBL_MAX             (FLT_MAX)
     #define LDBL_MIN             (FLT_MIN)
   #else
     #define LDBL_EPSILON       (_CSTD _Ldbl._Deps._Long_double)
     #define LDBL_MAX           (_CSTD _Ldbl._Dmax._Long_double)
     #define LDBL_MIN           (_CSTD _Ldbl._Dmin._Long_double)
   #endif /* defined(_32_BIT_DOUBLE) */
 #endif /* 199901L <= __STDC_VERSION__ */

  #define LDBL_DIG             (   33 )  /* _CSTD _Ldbl._Ddig */
  #define LDBL_MANT_DIG        (  113 )  /* _CSTD _Ldbl._Dmdig */
  #define LDBL_MAX_10_EXP      ( 4932 )  /* _CSTD _Ldbl._Dmax10e */
  #define LDBL_MAX_EXP         ( 16384)  /* _CSTD _Ldbl._Dmaxe */
  #define LDBL_MIN_10_EXP      (-4931 )  /* _CSTD _Ldbl._Dmin10e */
  #define LDBL_MIN_EXP         (-16381)  /* _CSTD _Ldbl._Dmine */
 #endif /* _DLONG */


_C_STD_END

#pragma diag_pop

#endif /* _FLOAT */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
