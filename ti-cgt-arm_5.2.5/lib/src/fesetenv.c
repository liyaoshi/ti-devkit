/* fesetenv function */
#include <fenv.h>
#include <float.h>


 #if 199901L <= __STDC_VERSION__ && !defined(__APPLE__)
/* Some targets have 32 bit doubles, so the original number is out of range */
 #if DBL_DIG >= 15
  #define DBL_BIG	1e+300	/* may raise inexact too */
 #else
  #define DBL_BIG       1e+30   /* violates the C99 standard */
 #endif

 #elif DBL_MANT_DIG == 24
  #define DBL_BIG       DBL_MAX
  
 #else /* 199901L <= __STDC_VERSION__ */
/* Some targets have 32 bit doubles, so the original number is out of range */
 #if DBL_DIG >= 15
  #define DBL_BIG	1e+300	/* may raise inexact too */
 #else
  #define DBL_BIG       1e+30   /* violates the C99 standard */
 #endif
 #endif /* 199901L <= __STDC_VERSION__ */

_STD_BEGIN
static struct {
	int except;
	double num, denom;
	} table[] = {	/* raise except by evaluating num / denom */
	{FE_INVALID, 0.0, 0.0},
	{FE_DIVBYZERO, 1.0, 0.0},
#if DBL_MANT_DIG == 24
	{FE_OVERFLOW,  DBL_BIG, DBL_MIN },
	{FE_UNDERFLOW, DBL_MIN, DBL_BIG},
#else
	{FE_OVERFLOW, DBL_BIG, 1.0 / DBL_BIG},
	{FE_UNDERFLOW, 1.0 / DBL_BIG, DBL_BIG},
#endif
	{FE_INEXACT, 2.0, 3.0}};

double _Force_raise(int except)
	{	/* trigger one or more exceptions */
	double ans = 0.0;
	int i;

	for (i = 0; i < sizeof (table) / sizeof (table[0]); ++i)
		if ((except & table[i].except) != 0)
			ans = table[i].num / table[i].denom;
	return (ans);	/* use it, to quell warnings */
	}
_STD_END

 #if _FPP_TYPE == _FPP_NONE
  #include "xtls.h"
_STD_BEGIN

_TLS_DATA_DECL(fenv_t, _Fenv);

int (fesetenv)(const fenv_t *penv)
	{	/* load floating-point environment */
	*_TLS_DATA_PTR(_Fenv) = *penv;
	return (0);
	}
_STD_END

 #else /* _FPP_TYPE == _FPP_NONE */
_STD_BEGIN

int (fesetenv)(const fenv_t *penv)
	{	/* load floating-point environment */


  #if _FPP_TYPE == _FPP_X86

	asm("movl	8(%ebp),%eax");	/* gcc/PC */
	asm("fldenv	(%eax)");

  #elif _FPP_TYPE == _FPP_SPARC
	asm("ld		[%fp+68],%o0");
	asm("ld		[%o0],%fsr");

  #elif _FPP_TYPE == _FPP_MIPS

	__asm__("ctcl	%0,$31" : : "r" (*penv));

  #elif _FPP_TYPE == _FPP_S390
	asm("l		2,96(11)");
	asm("l		3,0(2)");
	asm("sfpc	3,0");

  #elif _FPP_TYPE == _FPP_PPC
	union {
		double dbl;
		fenv_t csr[2];
		} status;

	status.csr[0] = (fenv_t)-1;
	status.csr[1] = *penv;
	__asm__("mtfsf	0xff,%0" : : "f" (status));

  #elif _FPP_TYPE == _FPP_HPPA
	__asm__(	/* HP PA-Risc */
		"fldd,mb	-8(%2),%%fr3\n"
		"fldd,mb	-8(%2),%%fr2\n"
		"fldd,mb	-8(%2),%%fr1\n"
		"fldd		-8(%2),%%fr0\n"
			: "=m" (*penv), "=r" (penv) : "1" (penv));

  #elif _FPP_TYPE == _FPP_ALPHA
	__asm__(
		"excb\n"
		"mt_fpcr	%0\n"
		"excb"
			: : "f" (*penv));

  #elif _FPP_TYPE == _FPP_ARM
	__asm__("wfs	%0" : : "r" (*penv));

  #elif _FPP_TYPE == _FPP_M68K
	__asm__("fmovem%.l	%0,%/fpcr/%/fpsr/%/fpiar" : : "m" (*penv));

  #elif _FPP_TYPE == _FPP_SH4
	fenv_t env = *penv;

	__asm__("lds	%0,fpcsr" : : "r" (env));

  #elif _FPP_TYPE == _FPP_IA64
	__asm__("mov.m	ar.fpsr=%0" : : "r" (*penv));

  #elif _FPP_TYPE == _FPP_WCE
	_controlfp(penv->_Fe_ctl, _FE_RND_MASK << _FE_RND_OFF);
    _clearfp();
	if ((penv->_Fe_stat & (FE_ALL_EXCEPT << _FE_EXCEPT_OFF)) != 0)
		_Force_raise(penv->_Fe_stat);

  #else /* _FPP_TYPE */
   #error unknown FPP type
  #endif /* _FPP_TYPE */

	return (0);
	}

_STD_END
 #endif /* _FPP_TYPE == _FPP_NONE */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
