/* signal.h standard header */
#ifndef _SIGNAL
#define _SIGNAL
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

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

#if _AEABI_PORTABILITY_CHECK
_EXTERN_C
extern void __aeabi_SIG_DFL(int);
extern void __aeabi_SIG_ERR(int);
extern void __aeabi_SIG_IGN(int);
#define SIG_DFL (__aeabi_SIG_DFL)
#define SIG_ERR (__aeabi_SIG_ERR)
#define SIG_IGN (__aeabi_SIG_IGN)

extern const int __aeabi_SIGABRT;
extern const int __aeabi_SIGFPE;
extern const int __aeabi_SIGILL;
extern const int __aeabi_SIGINT;
extern const int __aeabi_SIGSEGV;
extern const int __aeabi_SIGTERM;
#define SIGABRT (__aeabi_SIGABRT)
#define SIGFPE (__aeabi_SIGFPE)
#define SIGILL (__aeabi_SIGILL)
#define SIGINT (__aeabi_SIGINT)
#define SIGSEGV (__aeabi_SIGSEGV)
#define SIGTERM (__aeabi_SIGTERM)
_END_EXTERN_C
#else /* _AEABI_PORTABILITY_CHECK */

		/* SIGNAL CODES */
#define SIGABRT	_SIGABRT
#define SIGINT	2
#define SIGILL	4
#define SIGFPE	8
#define SIGSEGV	11
#define SIGTERM	15
#define _NSIG	_SIGMAX	/* one more than last code */

		/* SIGNAL RETURN VALUES */
#define SIG_DFL	((_CSTD _Sigfun *)0)
#define SIG_ERR	((_CSTD _Sigfun *)-1)
#define SIG_IGN	((_CSTD _Sigfun *)1)

#endif /* _AEABI_PORTABILITY_CHECK */
_EXTERN_C
		/* TYPE DEFINITIONS */

typedef int sig_atomic_t;


typedef void _Sigfun(int);

		/* LOW-LEVEL FUNCTIONS */
_Sigfun * signal(int, _Sigfun *);
_END_EXTERN_C

_C_LIB_DECL		/* DECLARATIONS */
int raise(int);
_END_C_LIB_DECL
_C_STD_END
#endif /* _SIGNAL */

#ifdef _STD_USING
using _CSTD sig_atomic_t; using _CSTD raise; using _CSTD signal;
  #if _AEABI_PORTABILITY_CHECK
using _CSTD __aeabi_SIG_DFL;
using _CSTD __aeabi_SIG_ERR;
using _CSTD __aeabi_SIG_IGN;
using _CSTD __aeabi_SIGFPE;
using _CSTD __aeabi_SIGILL;
using _CSTD __aeabi_SIGINT;
using _CSTD __aeabi_SIGSEGV;
using _CSTD __aeabi_SIGTERM;
  #endif
#endif /* _STD_USING */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
