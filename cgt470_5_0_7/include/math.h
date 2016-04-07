/****************************************************************************/
/*  math.h          v5.0.7                                                  */
/*                                                                          */
/* Copyright (c) 2010-2013 Texas Instruments Incorporated                   */
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
/* math.h standard header */
#ifndef _MATH
#define _MATH
#ifndef _YMATH
 #include <ymath.h>
#endif /* _YMATH */

/*---------------------------------------------------------------------------*/
/* A header file conforming to ARM CLIB ABI (GENC-003539), should            */
/* define _AEABI_PORTABLE when _AEABI_PORTABILITY_LEVEL is defined.          */
/*---------------------------------------------------------------------------*/
#if defined(_AEABI_PORTABILITY_LEVEL) && !defined(_AEABI_PORTABLE)
#define _AEABI_PORTABLE
#endif

/*---------------------------------------------------------------------------*/
/* The macro definition that guards CLIB ABI (GENC-003539) requirements.     */
/*---------------------------------------------------------------------------*/
#if defined(__TMS470__) && defined(__TI_EABI_SUPPORT__)
#define _AEABI_PORTABILITY_CHECK (defined(__TMS470__) && \
	                          defined(__TI_EABI_SUPPORT__) && \
	                          _AEABI_PORTABILITY_LEVEL != 0)
#else
#define _AEABI_PORTABILITY_CHECK 0
#endif

_C_STD_BEGIN

		/* CODES FOR is* FUNCTIONS */
#define _FP_LT	1
#define _FP_EQ	2
#define _FP_GT	4

		/* CODES FOR ilogb FUNCTIONS */

 #if _ILONG
  #define _FP_ILOGB0	(-0x7fffffff - _C2)
  #define _FP_ILOGBNAN	0x7fffffff

 #else /* _ILONG */
  #define _FP_ILOGB0	(-0x7fff - _C2)
  #define _FP_ILOGBNAN	0x7fff
 #endif /* _ILONG */

 #if _HAS_C9X || defined(_C99_MATH)
		/* TYPES */

 #if defined(_FEVAL)
  #if _FEVAL == 1
typedef double float_t;
typedef double double_t;

  #elif _FEVAL == 2
typedef long double float_t;
typedef long double double_t;

  #else /* _FEVAL */
typedef float float_t;
typedef double double_t;
  #endif /* _FEVAL */
 #else /* defined(_FEVAL) */
typedef float float_t;
typedef double double_t;
 #endif /* defined(_FEVAL) */

		/* MACROS */

 #if 245 < __EDG_VERSION__ && !defined(__cplusplus)
  #define HUGE_VAL	((double)__INFINITY__)
  #define HUGE_VALF	__INFINITY__
  #define HUGE_VALL	((long double)__INFINITY__)
  #define INFINITY	__INFINITY__
  #define NAN		__NAN__

 #elif defined(__EDG__) || 0 < _MSC_VER
  #if _AEABI_PORTABILITY_CHECK
  _EXTERN_C
    extern const double      __aeabi_HUGE_VAL;
    extern const long double __aeabi_HUGE_VALL;
    extern const float       __aeabi_HUGE_VALF;
    extern const float       __aeabi_INFINITY;
    extern const float       __aeabi_NAN;
  _END_EXTERN_C
    #define HUGE_VAL  (__aeabi_HUGE_VAL)
    #define HUGE_VALL (__aeabi_HUGE_VALL)
    #define HUGE_VALF (__aeabi_HUGE_VALF)
    #define INFINITY  (__aeabi_INFINITY)
    #define NAN       (__aeabi_NAN)
  #else
   #define HUGE_VAL	_CSTD _Inf._Double
   #define HUGE_VALF	_CSTD _FInf._Float
   #define HUGE_VALL	_CSTD _LInf._Long_double
   #define INFINITY	_CSTD _FInf._Float
   #define NAN		_CSTD _FNan._Float
  #endif

 #else /* !defined(__EDG__) */
  #ifndef _HUGE_ENUF
   #define _HUGE_ENUF	1e+30F	/* _HUGE_ENUF*_HUGE_ENUF must overflow */
  #endif /* _HUGE_ENUF */

  #define HUGE_VAL	((double)INFINITY)
  #define HUGE_VALF	((float)INFINITY)
  #define HUGE_VALL	((long double)INFINITY)
  #define INFINITY	((float)(_HUGE_ENUF * _HUGE_ENUF))
  #define NAN		((float)(INFINITY * 0.0F))
 #endif /* 245 < __EDG_VERSION__ */

#define FP_INFINITE		_INFCODE
#define FP_NAN			_NANCODE
#define FP_NORMAL		_FINITE
#define FP_SUBNORMAL	_DENORM
#define FP_ZERO			0

 #if defined(_HAS_C9X_FAST_FMA)
  #define FP_FAST_FMA	1
  #define FP_FAST_FMAF	1
  #define FP_FAST_FMAL	1
 #elif defined(_HAS_C9X_FAST_FMAF)
  #define FP_FAST_FMAF	1
 #endif /* defined(_HAS_C9X_FAST_FMAF) */

 #define FP_ILOGB0		_FP_ILOGB0
 #define FP_ILOGBNAN	_FP_ILOGBNAN

#define MATH_ERRNO			1
#define MATH_ERREXCEPT		2
#define math_errhandling	(MATH_ERRNO | MATH_ERREXCEPT)	/* do both */

_C_LIB_DECL
int _FFpcomp(float, float);
int _Fpcomp(double, double);
int _LFpcomp(long double, long double);

int _FDclass(float);
int _Dclass(double);
int _LDclass(long double);

int _FDsign(float);
int _Dsign(double);
int _LDsign(long double);
_END_C_LIB_DECL

#if defined(__cplusplus)
 #if defined(__embedded_cplusplus) && !__embedded_cplusplus     /* DON'T SIMPLIFY! */
  #define _FPCOMP_template      1
 #else  /* !__embedded_cplusplus */
  #define _FPCOMP_template      0
 #endif /* !__embedded_cplusplus */
#else /* defined(__cplusplus) */
#define _FPCOMP_template      0
#endif /* defined(__cplusplus) */

 #if _FPCOMP_template
 /* Contents of #if _FPCOMP_template moved to mathcpp.h to avoid C++ constructs in C*/
 #else /* _FPCOMP_template */

  #if __EDG__ && !__TI_COMPILER_VERSION__
   #define _CARGI(x, fd, ff, fl) \
	__generic(x,,, fd, ff, fl,,,)(x)
   #define _CARG2I(x, y, fd, ff, fl) \
	__generic(x, y,, fd, ff, fl,,,)(x, y)

  #else /* compiler type */
   #define _ARG(x)	(sizeof ((x) + (float)0) == sizeof (float) ? 'f' \
	: sizeof ((x) + (double)0) == sizeof (double) ? 'd' \
	: 'l')
   #define _CARGI(x, fd, ff, fl)	\
	(_ARG(x) == 'f' ? ff((float)(x)) \
	: _ARG(x) == 'd' ? fd((double)(x)) \
	: fl((long double)(x)))
   #define _CARG2I(x, y, fd, ff, fl)	\
	(_ARG((x) + (y)) == 'f' ? ff((float)(x), (float)(y)) \
	: _ARG((x) + (y)) == 'd' ? fd((double)(x), (double)(y)) \
	: fl((long double)(x), (long double)(y)))
  #endif /* compiler type */

  #define _FPCOMP(x, y) \
	_CARG2I(x, y, _CSTD _Fpcomp, _CSTD _FFpcomp, _CSTD _LFpcomp)
  #define fpclassify(x) \
	_CARGI(x, _CSTD _Dclass, _CSTD _FDclass, _CSTD _LDclass)
  #define signbit(x) \
	_CARGI(x, _CSTD _Dsign, _CSTD _FDsign, _CSTD _LDsign)

#define isfinite(x)	(fpclassify(x) <= 0)
#define isinf(x)	(fpclassify(x) == FP_INFINITE)
#define isnan(x)	(fpclassify(x) == FP_NAN)
#define isnormal(x)	(fpclassify(x) == FP_NORMAL)

#define isgreater(x, y)	((_FPCOMP(x, y) & _FP_GT) != 0)
#define isgreaterequal(x, y)	\
	((_FPCOMP(x, y) & (_FP_EQ | _FP_GT)) != 0)
#define isless(x, y)	((_FPCOMP(x, y) & _FP_LT) != 0)
#define islessequal(x, y)	((_FPCOMP(x, y) & (_FP_LT | _FP_EQ)) != 0)
#define islessgreater(x, y)	\
	((_FPCOMP(x, y) & (_FP_LT | _FP_GT)) != 0)
#define isunordered(x, y)	(_FPCOMP(x, y) == 0)
 #endif /* _FPCOMP_template */

 #else /* _HAS_C9X || _C99_MATH */
		/* MACROS */
 #define HUGE_VAL	_CSTD _Hugeval._Double
 #endif /* _HAS_C9X || _C99_MATH */

_C_LIB_DECL

#ifdef __TI_COMPILER_VERSION__
/*---------------------------------------------------------------------------*/
/* If --fp_mode=relaxed is used and VFP is enabled, use the hardware square  */
/* root directly instead of calling the sqrtx routine. This will not set     */
/* errno if the argument is negative.                                        */
/*                                                                           */
/* This is done by defining sqrt to _relaxed_sqrt to allow other translation */
/* units to use the normal sqrt routine under strict mode.                   */
/*---------------------------------------------------------------------------*/
#if defined(__TI_VFP_SUPPORT__)  && !__TI_STRICT_FP_MODE__
#define sqrtf __relaxed_sqrtf
inline float __relaxed_sqrtf(float x)       
{ 
    return __sqrtf(x); 
}

/*---------------------------------------------------------------------------*/
/* The FPv4SP supported on Cortex-M4 does not have double precision hardware */
/* so avoid using the intrinsic.                                             */
/*---------------------------------------------------------------------------*/
#if !defined(__TI_FPv4SPD16_SUPPORT__)
#define sqrt  __relaxed_sqrt
inline double __relaxed_sqrt(double x)
{ 
    return __sqrt(x);  
}

#define sqrtl __relaxed_sqrtl
inline long double __relaxed_sqrtl(long double x) 
{ 
    return __sqrt(x);  
}
#endif /* !defined(__TI_FPv4SPD16_SUPPORT__) */
#endif /* defined(__TI_VFP_SUPPORT__)  && !__TI_STRICT_FP_MODE__ */
#endif /* __TI_COMPILER_VERSION__ */
		/* double declarations */
double acos(double);
double asin(double);
double atan(double);
double atan2(double, double);
double ceil(double);
double exp(double);
double fabs(double);
double floor(double);
double fmod(double, double);
double frexp(double, int *);
double ldexp(double, int);
double modf(double, double *);
double pow(double, double);
double sqrt(double);
double tan(double);
double tanh(double);

 #if _HAS_C9X || defined(_C99_MATH)
double acosh(double);
double asinh(double);
double atanh(double);
double cbrt(double);
double copysign(double, double);
double erf(double);
double erfc(double);
double exp2(double);
double expm1(double);
double fdim(double, double);
double fma(double, double, double);
double fmax(double, double);
double fmin(double, double);
double hypot(double, double);
int ilogb(double);
double lgamma(double);
_Longlong llrint(double);
_Longlong llround(double);
double log1p(double);
double logb(double);
long lrint(double);
long lround(double);
double nan(const char *);
double nearbyint(double);
double nextafter(double, double);
double nexttoward(double, long double);
double remainder(double, double);
double remquo(double, double, int *);
double rint(double);
double round(double);
double scalbn(double, int);
double scalbln(double, long);
double tgamma(double);
double trunc(double);
 #endif /* _HAS_C9X || _C99_MATH */

		/* float declarations */
float acosf(float);
float asinf(float);
float atanf(float);
float atan2f(float, float);
float ceilf(float);
float expf(float);
float fabsf(float);
float floorf(float);
float fmodf(float, float);
float frexpf(float, int *);
float ldexpf(float, int);
float modff(float, float *);
float powf(float, float);
float sqrtf(float);
float tanf(float);
float tanhf(float);

 #if _HAS_C9X || defined(_C99_MATH)
float acoshf(float);
float asinhf(float);
float atanhf(float);
float cbrtf(float);
float copysignf(float, float);
float erff(float);
float erfcf(float);
float expm1f(float);
float exp2f(float);
float fdimf(float, float);
float fmaf(float, float, float);
float fmaxf(float, float);
float fminf(float, float);
float hypotf(float, float);
int ilogbf(float);
float lgammaf(float);
_Longlong llrintf(float);
_Longlong llroundf(float);
float log1pf(float);
float logbf(float);
long lrintf(float);
long lroundf(float);
float nanf(const char *);
float nearbyintf(float);
float nextafterf(float, float);
float nexttowardf(float, long double);
float remainderf(float, float);
float remquof(float, float, int *);
float rintf(float);
float roundf(float);
float scalbnf(float, int);
float scalblnf(float, long);
float tgammaf(float);
float truncf(float);
 #endif /* _HAS_C9X || _C99_MATH */

		/* long double declarations */
long double acosl(long double);
long double asinl(long double);
long double atanl(long double);
long double atan2l(long double, long double);
long double ceill(long double);
long double expl(long double);
long double fabsl(long double);
long double floorl(long double);
long double fmodl(long double, long double);
long double frexpl(long double, int *);
long double ldexpl(long double, int);
long double modfl(long double, long double *);
long double powl(long double, long double);
long double sqrtl(long double);
long double tanl(long double);
long double tanhl(long double);

 #if _HAS_C9X || defined(_C99_MATH)
long double acoshl(long double);
long double asinhl(long double);
long double atanhl(long double);
long double cbrtl(long double);
long double copysignl(long double, long double);
long double erfl(long double);
long double erfcl(long double);
long double exp2l(long double);
long double expm1l(long double);
long double fdiml(long double, long double);
long double fmal(long double, long double, long double);
long double fmaxl(long double, long double);
long double fminl(long double, long double);
long double hypotl(long double, long double);
int ilogbl(long double);
long double lgammal(long double);
_Longlong llrintl(long double);
_Longlong llroundl(long double);
long double log1pl(long double);
long double logbl(long double);
long lrintl(long double);
long lroundl(long double);
long double nanl(const char *);
long double nearbyintl(long double);
long double nextafterl(long double, long double);
long double nexttowardl(long double, long double);
long double remainderl(long double, long double);
long double remquol(long double, long double, int *);
long double rintl(long double);
long double roundl(long double);
long double scalbnl(long double, int);
long double scalblnl(long double, long);
long double tgammal(long double);
long double truncl(long double);
 #endif /* _HAS_C9X || _C99_MATH */

_END_C_LIB_DECL

_C_LIB_DECL

		/* double MACRO OVERRIDES, FOR C */
double cos(double);
double cosh(double);
double log(double);
double log10(double);
double sin(double);
double sinh(double);

#ifndef __TI_COMPILER_VERSION__
 #define cos(x)		_Sin(x, 1)
 #define cosh(x)	_Cosh(x, 1)
 #define log(x)		_Log(x, 0)
 #define log10(x)	_Log(x, 1)
 #define sin(x)		_Sin(x, 0)
 #define sinh(x)	_Sinh(x, 1)
#endif /* __TI_COMPILER_VERSION__ */

 #if _HAS_C9X || defined(_C99_MATH)
double log2(double);
 #endif /* _HAS_C9X || _C99 MATH*/

#ifndef __TI_COMPILER_VERSION__
 #define log2(x)	_Log(x, -1)
#endif /* __TI_COMPILER_VERSION__ */

		/* float MACRO OVERRIDES, FOR C */
float cosf(float);
float coshf(float);
float logf(float);
float log10f(float);
float sinf(float);
float sinhf(float);

#ifndef __TI_COMPILER_VERSION__
 #define cosf(x)	_FSin(x, 1)
 #define coshf(x)	_FCosh(x, 1)
 #define logf(x)	_FLog(x, 0)
 #define log10f(x)	_FLog(x, 1)
 #define sinf(x)	_FSin(x, 0)
 #define sinhf(x)	_FSinh(x, 1)
#endif /* __TI_COMPILER_VERSION__ */

 #if _HAS_C9X || defined(_C99_MATH)
float log2f(float);
 #endif /* _HAS_C9X || _C99 MATH*/

#ifndef __TI_COMPILER_VERSION__
 #define log2f(x)	_FLog(x, -1)
#endif /* __TI_COMPILER_VERSION__ */

		/* long double MACRO OVERRIDES, FOR C */
long double cosl(long double);
long double coshl(long double);
long double logl(long double);
long double log10l(long double);
long double sinl(long double);
long double sinhl(long double);

#ifndef __TI_COMPILER_VERSION__
 #define cosl(x)	_LSin(x, 1)
 #define coshl(x)	_LCosh(x, 1)
 #define logl(x)	_LLog(x, 0)
 #define log10l(x)	_LLog(x, 1)
 #define sinl(x)	_LSin(x, 0)
 #define sinhl(x)	_LSinh(x, 1)
#endif /* __TI_COMPILER_VERSION__ */

 #if _HAS_C9X || defined(_C99_MATH)
long double log2l(long double);
 #endif /* _HAS_C9X || _C99 MATH*/

#ifndef __TI_COMPILER_VERSION__
 #define log2l(x)	_LLog(x, -1)
#endif /* __TI_COMPILER_VERSION__ */

_END_C_LIB_DECL

_C_STD_END
#endif /* _MATH */

 #if defined(_STD_USING)
using _CSTD abs;
using _CSTD acos; using _CSTD asin;
using _CSTD atan; using _CSTD atan2; using _CSTD ceil;
using _CSTD cos; using _CSTD cosh; using _CSTD exp;
using _CSTD fabs; using _CSTD floor; using _CSTD fmod;
using _CSTD frexp; using _CSTD ldexp; using _CSTD log;
using _CSTD log10; using _CSTD modf; using _CSTD pow;
using _CSTD sin; using _CSTD sinh; using _CSTD sqrt;
using _CSTD tan; using _CSTD tanh;

using _CSTD acosf; using _CSTD asinf;
using _CSTD atanf; using _CSTD atan2f; using _CSTD ceilf;
using _CSTD cosf; using _CSTD coshf; using _CSTD expf;
using _CSTD fabsf; using _CSTD floorf; using _CSTD fmodf;
using _CSTD frexpf; using _CSTD ldexpf; using _CSTD logf;
using _CSTD log10f; using _CSTD modff; using _CSTD powf;
using _CSTD sinf; using _CSTD sinhf; using _CSTD sqrtf;
using _CSTD tanf; using _CSTD tanhf;

using _CSTD acosl; using _CSTD asinl;
using _CSTD atanl; using _CSTD atan2l; using _CSTD ceill;
using _CSTD cosl; using _CSTD coshl; using _CSTD expl;
using _CSTD fabsl; using _CSTD floorl; using _CSTD fmodl;
using _CSTD frexpl; using _CSTD ldexpl; using _CSTD logl;
using _CSTD log10l; using _CSTD modfl; using _CSTD powl;
using _CSTD sinl; using _CSTD sinhl; using _CSTD sqrtl;
using _CSTD tanl; using _CSTD tanhl;

 #if _HAS_C9X || defined(_C99_MATH)

 /* #if _FPCOMP_template moved to mathcpp.h */

using _CSTD float_t; using _CSTD double_t;

using _CSTD acosh; using _CSTD asinh; using _CSTD atanh;
using _CSTD cbrt; using _CSTD erf; using _CSTD erfc;
using _CSTD expm1; using _CSTD exp2;
using _CSTD hypot; using _CSTD ilogb; using _CSTD lgamma;
using _CSTD log1p; using _CSTD log2; using _CSTD logb;
using _CSTD llrint; using _CSTD lrint; using _CSTD nearbyint;
using _CSTD rint; using _CSTD llround; using _CSTD lround;
using _CSTD fdim; using _CSTD fma; using _CSTD fmax; using _CSTD fmin;
using _CSTD round; using _CSTD trunc;
using _CSTD remainder; using _CSTD remquo;
using _CSTD copysign; using _CSTD nan; using _CSTD nextafter;
using _CSTD scalbn; using _CSTD scalbln;
using _CSTD nexttoward; using _CSTD tgamma;

using _CSTD acoshf; using _CSTD asinhf; using _CSTD atanhf;
using _CSTD cbrtf; using _CSTD erff; using _CSTD erfcf;
using _CSTD expm1f; using _CSTD exp2f;
using _CSTD hypotf; using _CSTD ilogbf; using _CSTD lgammaf;
using _CSTD log1pf; using _CSTD log2f; using _CSTD logbf;
using _CSTD llrintf; using _CSTD lrintf; using _CSTD nearbyintf;
using _CSTD rintf; using _CSTD llroundf; using _CSTD lroundf;
using _CSTD fdimf; using _CSTD fmaf; using _CSTD fmaxf; using _CSTD fminf;
using _CSTD roundf; using _CSTD truncf;
using _CSTD remainderf; using _CSTD remquof;
using _CSTD copysignf; using _CSTD nanf;
using _CSTD nextafterf; using _CSTD scalbnf; using _CSTD scalblnf;
using _CSTD nexttowardf; using _CSTD tgammaf;

using _CSTD acoshl; using _CSTD asinhl; using _CSTD atanhl;
using _CSTD cbrtl; using _CSTD erfl; using _CSTD erfcl;
using _CSTD expm1l; using _CSTD exp2l;
using _CSTD hypotl; using _CSTD ilogbl; using _CSTD lgammal;
using _CSTD log1pl; using _CSTD log2l; using _CSTD logbl;
using _CSTD llrintl; using _CSTD lrintl; using _CSTD nearbyintl;
using _CSTD rintl; using _CSTD llroundl; using _CSTD lroundl;
using _CSTD fdiml; using _CSTD fmal; using _CSTD fmaxl; using _CSTD fminl;
using _CSTD roundl; using _CSTD truncl;
using _CSTD remainderl; using _CSTD remquol;
using _CSTD copysignl; using _CSTD nanl;
using _CSTD nextafterl; using _CSTD scalbnl; using _CSTD scalblnl;
using _CSTD nexttowardl; using _CSTD tgammal;
 #endif /* _HAS_C9X || _C99_MATH */

  #if _AEABI_PORTABILITY_CHECK
using _CSTD __aeabi_HUGE_VAL;
using _CSTD __aeabi_HUGE_VALL;
using _CSTD __aeabi_HUGE_VALF;
using _CSTD __aeabi_INFINITY;
using _CSTD __aeabi_NAN;
  #endif
 #endif /* defined(_STD_USING) */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
