/****************************************************************************/
/*  mathcpp.h          v5.2.7                                               */
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

#ifndef MATHCPP_H_
#define MATHCPP_H_


_C_STD_BEGIN

 #if _HAS_C9X || defined(_C99_MATH)

/* _FPCOMP_template defined in math.h */

#if _FPCOMP_template
		// TEMPLATE CLASS _Rc_type
template<class _Ty>
	struct _Rc_type
	{	// determine if type is real or complex
	typedef float _Type;	// default is real
	};

		// TEMPLATE CLASS _Rc_widened
template<class _Ty, class _T2>
	struct _Rc_widened
	{	// determine real/complex type
	typedef float _Type;	// (real, real) is real
	};

		// TEMPLATE CLASS _Real_type

template<class _Ty>
	struct _Real_type
	{	// determine equivalent real type
	typedef double _Type;	// default is double
	};

template<> struct _Real_type<float>
	{	// determine equivalent real type
	typedef float _Type;
	};

template<> struct _Real_type<long double>
	{	// determine equivalent real type
	typedef long double _Type;
	};

		// TEMPLATE CLASS _Real_widened
template<class _Ty, class _T2>
	struct _Real_widened
	{	// determine widened real type
	typedef long double _Type;	// default is long double
	};

template<> struct _Real_widened<float, float>
	{	// determine widened real type
	typedef float _Type;
	};

template<> struct _Real_widened<float, double>
	{	// determine widened real type
	typedef double _Type;
	};

template<> struct _Real_widened<double, float>
	{	// determine widened real type
	typedef double _Type;
	};

template<> struct _Real_widened<double, double>
	{	// determine widened real type
	typedef double _Type;
	};

		// TEMPLATE CLASS _Combined_type
template<class _Trc, class _Tre>
	struct _Combined_type
	{	// determine combined type
	typedef float _Type;	// (real, float) is float
	};

template<> struct _Combined_type<float, double>
	{	// determine combined type
	typedef double _Type;
	};

template<> struct _Combined_type<float, long double>
	{	// determine combined type
	typedef long double _Type;
	};

		// TEMPLATE FUNCTION _FPCOMP
inline int _FPCOMP(float _Left, float _Right)
	{	// compare _Left and _Right
	return (_FFpcomp(_Left, _Right));
	}

inline int _FPCOMP(double _Left, double _Right)
	{	// compare _Left and _Right
	return (_Fpcomp(_Left, _Right));
	}

inline int _FPCOMP(long double _Left, long double _Right)
	{	// compare _Left and _Right
	return (_LFpcomp(_Left, _Right));
	}

template<class _T1, class _T2> inline
	int _FPCOMP(_T1 _Left, _T2 _Right)
	{	// compare _Left and _Right
	typedef typename _Combined_type<float,
		typename _Real_widened<
			typename _Real_type<_T1>::_Type,
			typename _Real_type<_T2>::_Type>::_Type>::_Type _Tw;
	return (_FPCOMP((_Tw)_Left, (_Tw)_Right));
	}

		// FUNCTION fpclassify
inline int fpclassify(float _Left)
	{	// classify argument
	return (_FDtest(&_Left));
	}

inline int fpclassify(double _Left)
	{	// classify argument
	return (_Dtest(&_Left));
	}

inline int fpclassify(long double _Left)
	{	// classify argument
	return (_LDtest(&_Left));
	}

		// FUNCTION signbit
inline bool signbit(float _Left)
	{	// test sign bit
	return (_FDsign(_Left) != 0);
	}

inline bool signbit(double _Left)
	{	// test sign bit
	return (_Dsign(_Left) != 0);
	}

inline bool signbit(long double _Left)
	{	// test sign bit
	return (_LDsign(_Left) != 0);
	}

template<class _Ty> inline
	bool isfinite(_Ty _Left)
	{	// test for finite
	return (fpclassify(_Left) <= 0);
	}

template<class _Ty> inline
	bool isinf(_Ty _Left)
	{	// test for infinite
	return (fpclassify(_Left) == FP_INFINITE);
	}

template<class _Ty> inline
	bool isnan(_Ty _Left)
	{	// test for NaN
	return (fpclassify(_Left) == FP_NAN);
	}

template<class _Ty> inline
	bool isnormal(_Ty _Left)
	{	// test for normal
	return (fpclassify(_Left) == FP_NORMAL);
	}

template<class _Ty1, class _Ty2> inline
	bool isgreater(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left > _Right
	return ((_FPCOMP(_Left, _Right) & _FP_GT) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool isgreaterequal(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left >= _Right
	return ((_FPCOMP(_Left, _Right) & (_FP_EQ | _FP_GT)) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool isless(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left < _Right
	return ((_FPCOMP(_Left, _Right) & _FP_LT) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool islessequal(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left <= _Right
	return ((_FPCOMP(_Left, _Right) & (_FP_LT | _FP_EQ)) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool islessgreater(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left != _Right
	return ((_FPCOMP(_Left, _Right) & (_FP_LT | _FP_GT)) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool isunordered(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left unorderd w.r.t. _Right
	return (_FPCOMP(_Left, _Right) == 0);
	}

  #define fpclassify(x) 		(_CSTD fpclassify(x))
  #define signbit(x)			(_CSTD signbit(x))
  #define isfinite(x)			(_CSTD isfinite(x))
  #define isinf(x)				(_CSTD isinf(x))
  #define isnan(x)				(_CSTD isnan(x))
  #define isnormal(x)			(_CSTD isnormal(x))
  #define isgreater(x, y)		(_CSTD isgreater(x, y))
  #define isgreaterequal(x, y)	(_CSTD isgreaterequal(x, y))
  #define isless(x, y)			(_CSTD isless(x, y))
  #define islessequal(x, y)		(_CSTD islessequal(x, y))
  #define islessgreater(x, y)	(_CSTD islessgreater(x, y))
  #define isunordered(x, y)		(_CSTD isunordered(x, y))

 /* #else _FPCOMP_template included in math.h */

 #endif/* _FPCOMP_template */

#endif /* _HAS_C9X || _C99_MATH */

#if defined(__cplusplus) && !defined(_NO_CPP_INLINES)

#if _IS_EMBEDDED

#else /* _IS_EMBEDDED */
		// TEMPLATE FUNCTION _Pow_int
template<class _Ty> inline
	_Ty _Pow_int(_Ty _Left, int _Right)
	{	// raise to integer power
	unsigned int _Num = _Right;
	if (_Right < 0)
		_Num = 0 - _Num;

	for (_Ty _Ans = 1; ; _Left *= _Left)
		{	// scale and fold in factors
		if ((_Num & 1) != 0)
			_Ans *= _Left;
		if ((_Num >>= 1) == 0)
			return (0 <= _Right ? _Ans
				: _Ans == _Ty(0) ? HUGE_VAL : _Ty(1) / _Ans);
		}
	}
#endif /* _IS_EMBEDDED */

		// double INLINES, FOR C++
/* Non-overload inlines are in math.h */
// OVERLOADS

inline double abs(double _Left)
{	// return absolute value
return (fabs(_Left));
}

#if _IS_EMBEDDED
inline double pow(double _Left, int _Right)
{	// raise to integer power
unsigned int _Num = _Right;
if (_Right < 0)
_Num = 0 - _Num;

for (double _Ans = 1; ; _Left *= _Left)
{if ((_Num & 1) != 0)
	_Ans *= _Left;
if ((_Num >>= 1) == 0)
	return (_Right < 0 ? (double)(1) / _Ans : _Ans);
}
}

#else /* _IS_EMBEDDED */
inline double pow(double _Left, int _Right)
{	// raise to integer power
return (_Pow_int(_Left, _Right));
}
#endif /* _IS_EMBEDDED */

		// float INLINES, FOR C++
/* Non-overload inlines are in math.h */
// OVERLOADS
inline float abs(float _Left)
	{	// return absolute value
	return (fabsf(_Left));
	}

inline float acos(float _Left)
	{	// return arccosine
	return (acosf(_Left));
	}

inline float asin(float _Left)
	{	// return arcsine
	return (asinf(_Left));
	}

inline float atan(float _Left)
	{	// return arctangent
	return (atanf(_Left));
	}

inline float atan2(float _Left, float _Right)
	{	// return arctangent
	return (atan2f(_Left, _Right));
	}

inline float ceil(float _Left)
	{	// return ceiling
	return (ceilf(_Left));
	}

inline float cos(float _Left)
	{	// return cosine
	return (_FSin(_Left, 1));
	}

inline float cosh(float _Left)
	{	// return hyperbolic cosine
	return (_FCosh(_Left, 1));
	}

inline float exp(float _Left)
	{	// return exponential
	return (expf(_Left));
	}

inline float fabs(float _Left)
	{	// return absolute value
	return (fabsf(_Left));
	}

inline float floor(float _Left)
	{	// return floor
	return (floorf(_Left));
	}

inline float fmod(float _Left, float _Right)
	{	// return modulus
	return (fmodf(_Left, _Right));
	}

inline float frexp(float _Left, int *_Right)
	{	// unpack exponent
	return (frexpf(_Left, _Right));
	}

inline float ldexp(float _Left, int _Right)
	{	// pack exponent
	return (ldexpf(_Left, _Right));
	}

inline float log(float _Left)
	{	// return natural logarithm
	return (_FLog(_Left, 0));
	}

inline float log10(float _Left)
	{	// return base-10 logarithm
	return (_FLog(_Left, 1));
	}

inline float modf(float _Left, float *_Right)
	{	// unpack fraction
	return (modff(_Left, _Right));
	}

inline float pow(float _Left, float _Right)
	{	// raise to power
	return (powf(_Left, _Right));
	}

#if _IS_EMBEDDED
inline float pow(float _Left, int _Right)
	{	// raise to integer power
	unsigned int _Num = _Right;
	if (_Right < 0)
		_Num = 0 - _Num;

	for (float _Ans = 1; ; _Left *= _Left)
		{if ((_Num & 1) != 0)
			_Ans *= _Left;
		if ((_Num >>= 1) == 0)
			return (_Right < 0 ? (float)(1) / _Ans : _Ans);
		}
	}

#else /* _IS_EMBEDDED */
inline float pow(float _Left, int _Right)
	{	// raise to integer power
	return (_Pow_int(_Left, _Right));
	}
#endif /* _IS_EMBEDDED */

inline float sin(float _Left)
	{	// return sine
	return (_FSin(_Left, 0));
	}

inline float sinh(float _Left)
	{	// return hyperbolic sine
	return (_FSinh(_Left, 1));
	}

inline float sqrt(float _Left)
	{	// return square root
	return (sqrtf(_Left));
	}

inline float tan(float _Left)
	{	// return tangent
	return (tanf(_Left));
	}

inline float tanh(float _Left)
	{	// return hyperbolic tangent
	return (tanhf(_Left));
	}

 #if _HAS_C9X || defined(_C99_MATH)
inline float acosh(float _Left)
	{	// return hyperbolic arccosine
	return (acoshf(_Left));
	}

inline float asinh(float _Left)
	{	// return hyperbolic arcsine
	return (asinhf(_Left));
	}

inline float atanh(float _Left)
	{	// return hyperbolic arctangent
	return (atanhf(_Left));
	}

inline float cbrt(float _Left)
	{	// return cube root
	return (cbrtf(_Left));
	}

inline float copysign(float _Left, float _Right)
	{	// return copysign
	return (copysignf(_Left, _Right));
	}

inline float erf(float _Left)
	{	// return erf
	return (erff(_Left)); }

inline float erfc(float _Left)
	{	// return erfc
	return (erfcf(_Left));
	}

inline float exp2(float _Left)
	{	// return exp2
	return (exp2f(_Left));
	}

inline float expm1(float _Left)
	{	// return expml
	return (expm1f(_Left));
	}

inline float fdim(float _Left, float _Right)
	{	// return fdim
	return (fdimf(_Left, _Right));
	}

inline float fma(float _Left, float _Right, float _Addend)
	{	// return fma
	return (fmaf(_Left, _Right, _Addend));
	}

inline float fmax(float _Left, float _Right)
	{	// return fmax
	return (fmaxf(_Left, _Right));
	}

inline float fmin(float _Left, float _Right)
	{	// return fmin
	return (fminf(_Left, _Right));
	}

inline float hypot(float _Left, float _Right)
	{	// return hypot
	return (hypotf(_Left, _Right));
	}

inline int ilogb(float _Left)
	{	// return ilogb
	return (ilogbf(_Left));
	}

inline float lgamma(float _Left)
	{	// return lgamma
	return (lgammaf(_Left));
	}

inline _Longlong llrint(float _Left)
	{	// return llrint
	return (llrintf(_Left));
	}

inline _Longlong llround(float _Left)
	{	// return llround
	return (llroundf(_Left));
	}

inline float log1p(float _Left)
	{	// return loglp
	return (log1pf(_Left));
	}

inline float log2(float _Left)
	{	// return log2
	return (_FLog(_Left, -1));
	}

inline float logb(float _Left)
	{	// return logb
	return (logbf(_Left));
	}

inline long lrint(float _Left)
	{	// return lrint
	return (lrintf(_Left));
	}

inline long lround(float _Left)
	{	// return lround
	return (lroundf(_Left));
	}

inline float nearbyint(float _Left)
	{	// return nearbyint
	return (nearbyintf(_Left));
	}

inline float nextafter(float _Left, float _Right)
	{	// return nextafter
	return (nextafterf(_Left, _Right));
	}

inline float nexttoward(float _Left, long double _Right)
	{	// return nexttoward
	return (nexttowardf(_Left, _Right));
	}

inline float remainder(float _Left, float _Right)
	{	// return remainder
	return (remainderf(_Left, _Right));
	}

inline float remquo(float _Left, float _Right, int *_Pval)
	{	// return remquo
	return (remquof(_Left, _Right, _Pval));
	}

inline float rint(float _Left)
	{	// return rint
	return (rintf(_Left));
	}

inline float round(float _Left)
	{	// return round
	return (roundf(_Left));
	}

inline float scalbn(float _Left, int _Right)
	{	// return scalbn
	return (scalbnf(_Left, _Right));
	}

inline float scalbln(float _Left, long _Right)
	{	// return scalbln
	return (scalblnf(_Left, _Right));
	}

inline float tgamma(float _Left)
	{	// return tgamma
	return (tgammaf(_Left));
	}

inline float trunc(float _Left)
	{	// return trunc
	return (truncf(_Left));
	}
 #endif /* _HAS_C9X || defined(_C99_MATH) */

		// long double INLINES, FOR C++
/* Non-overload inlines are in math.h */
// OVERLOADS

inline long double abs(long double _Left)
	{	// return absolute value
	return (fabsl(_Left));
	}

inline long double acos(long double _Left)
	{	// return arccosine
	return (acosl(_Left));
	}

inline long double asin(long double _Left)
	{	// return arcsine
	return (asinl(_Left));
	}

inline long double atan(long double _Left)
	{	// return arctangent
	return (atanl(_Left));
	}

inline long double atan2(long double _Left, long double _Right)
	{	// return arctangent
	return (atan2l(_Left, _Right));
	}

inline long double ceil(long double _Left)
	{	// return ceiling
	return (ceill(_Left));
	}

inline long double cos(long double _Left)
	{	// return cosine
	return (_LSin(_Left, 1));
	}

inline long double cosh(long double _Left)
	{	// return hyperbolic cosine
	return (_LCosh(_Left, 1));
	}

inline long double exp(long double _Left)
	{	// return exponential
	return (expl(_Left));
	}

inline long double fabs(long double _Left)
	{	// return absolute value
	return (fabsl(_Left));
	}

inline long double floor(long double _Left)
	{	// return floor
	return (floorl(_Left));
	}

inline long double fmod(long double _Left, long double _Right)
	{	// return modulus
	return (fmodl(_Left, _Right));
	}

inline long double frexp(long double _Left, int *_Right)
	{	// unpack exponent
	return (frexpl(_Left, _Right));
	}

inline long double ldexp(long double _Left, int _Right)
	{	// pack exponent
	return (ldexpl(_Left, _Right));
	}

inline long double log(long double _Left)
	{	// return natural logarithm
	return (_LLog(_Left, 0));
	}

inline long double log10(long double _Left)
	{	// return base-10 logarithm
	return (_LLog(_Left, 1));
	}

inline long double modf(long double _Left, long double *_Right)
	{	// unpack fraction
	return (modfl(_Left, _Right));
	}

inline long double pow(long double _Left, long double _Right)
	{	// raise to power
	return (powl(_Left, _Right));
	}

#if _IS_EMBEDDED
inline long double pow(long double _Left, int _Right)
	{	// raise to integer power
	unsigned int _Num = _Right;
	if (_Right < 0)
		_Num = 0 - _Num;

	for (long double _Ans = 1; ; _Left *= _Left)
		{if ((_Num & 1) != 0)
			_Ans *= _Left;
		if ((_Num >>= 1) == 0)
			return (_Right < 0 ? (long double)(1) / _Ans : _Ans);
		}
	}

#else /* _IS_EMBEDDED */
inline long double pow(long double _Left, int _Right)
	{	// raise to integer power
	return (_Pow_int(_Left, _Right));
	}
#endif /* _IS_EMBEDDED */

inline long double sin(long double _Left)
	{	// return sine
	return (_LSin(_Left, 0));
	}

inline long double sinh(long double _Left)
	{	// return hyperbolic sine
	return (_LSinh(_Left, 1));
	}

inline long double sqrt(long double _Left)
	{	// return square root
	return (sqrtl(_Left));
	}

inline long double tan(long double _Left)
	{	// return tangent
	return (tanl(_Left));
	}

inline long double tanh(long double _Left)
	{	// return hyperbolic tangent
	return (tanhl(_Left));
	}

 #if _HAS_C9X || defined(_C99_MATH)
inline long double acosh(long double _Left)
	{	// return acosh
	return (acoshl(_Left));
	}

inline long double asinh(long double _Left)
	{	// return asinh
	return (asinhl(_Left));
	}

inline long double atanh(long double _Left)
	{	// return atanh
	return (atanhl(_Left));
	}

inline long double cbrt(long double _Left)
	{	// return cbrt
	return (cbrtl(_Left));
	}

inline long double copysign(long double _Left, long double _Right)
	{	// return copysign
	return (copysignl(_Left, _Right));
	}

inline long double erf(long double _Left)
	{	// return erf
	return (erfl(_Left));
	}

inline long double erfc(long double _Left)
	{	// return erfc
	return (erfcl(_Left));
	}

inline long double exp2(long double _Left)
	{	// return exp2
	return (exp2l(_Left));
	}

inline long double expm1(long double _Left)
	{	// return expml
	return (expm1l(_Left));
	}

inline long double fdim(long double _Left, long double _Right)
	{	// return fdim
	return (fdiml(_Left, _Right));
	}

inline long double fma(long double _Left, long double _Right,
	long double _Addend)
	{	// return fma
	return (fmal(_Left, _Right, _Addend));
	}

inline long double fmax(long double _Left, long double _Right)
	{	// return fmax
	return (fmaxl(_Left, _Right));
	}

inline long double fmin(long double _Left, long double _Right)
	{	// return fmin
	return (fminl(_Left, _Right));
	}

inline long double hypot(long double _Left, long double _Right)
	{	// return hypot
	return (hypotl(_Left, _Right));
	}

inline int ilogb(long double _Left)
	{	// return ilogb
	return (ilogbl(_Left));
	}

inline long double lgamma(long double _Left)
	{	// return lgamma
	return (lgammal(_Left));
	}

inline _Longlong llrint(long double _Left)
	{	// return llrint
	return (llrintl(_Left));
	}

inline _Longlong llround(long double _Left)
	{	// return llround
	return (llroundl(_Left));
	}

inline long double log1p(long double _Left)
	{	// return loglp
	return (log1pl(_Left));
	}

inline long double log2(long double _Left)
	{	// return log2
	return (_LLog(_Left, -1));
	}

inline long double logb(long double _Left)
	{	// return logb
	return (logbl(_Left));
	}

inline long lrint(long double _Left)
	{	// return lrint
	return (lrintl(_Left));
	}

inline long lround(long double _Left)
	{	// return lround
	return (lroundl(_Left));
	}

inline long double nearbyint(long double _Left)
	{	// return nearbyint
	return (nearbyintl(_Left));
	}

inline long double nextafter(long double _Left, long double _Right)
	{	// return nextafter
	return (nextafterl(_Left, _Right));
	}

inline long double nexttoward(long double _Left, long double _Right)
	{	// return nexttoward
	return (nexttowardl(_Left, _Right));
	}

inline long double remainder(long double _Left, long double _Right)
	{	// return remainder
	return (remainderl(_Left, _Right));
	}

inline long double remquo(long double _Left, long double _Right,
	int *_Pval)
	{	// return remquo
	return (remquol(_Left, _Right, _Pval));
	}

inline long double rint(long double _Left)
	{	// return rint
	return (rintl(_Left));
	}

inline long double round(long double _Left)
	{	// return round
	return (roundl(_Left));
	}

inline long double scalbn(long double _Left, int _Right)
	{	// return scalbn
	return (scalbnl(_Left, _Right));
	}

inline long double scalbln(long double _Left, long _Right)
	{	// return scalbln
	return (scalblnl(_Left, _Right));
	}

inline long double tgamma(long double _Left)
	{	// return tgamma
	return (tgammal(_Left));
	}

inline long double trunc(long double _Left)
	{	// return trunc
	return (truncl(_Left));
	}
 #endif /* _HAS_C9X || _C99_MATH */

#endif /* defined(__cplusplus) && !defined(_NO_CPP_INLINES) */

_C_STD_END

#endif /* MATHCPP_H_ */

#if defined(_STD_USING)

 #if _HAS_C9X || defined(_C99_MATH)

#if _FPCOMP_template
using _CSTD _Rc_type; using _CSTD _Rc_widened;
using _CSTD _Real_type; using _CSTD _Real_widened;
using _CSTD _Combined_type;

using _CSTD _FPCOMP; using _CSTD fpclassify;
using _CSTD signbit; using _CSTD isfinite; using _CSTD isinf;
using _CSTD isnan; using _CSTD isnormal;
using _CSTD isgreater; using _CSTD isgreaterequal;
using _CSTD isless; using _CSTD islessequal; using _CSTD islessgreater;
using _CSTD isunordered;
#endif	/* _FPCOMP_template */

 #endif /* _HAS_C9X || _C99_MATH */

#endif /* defined(_STD_USING) */


/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
