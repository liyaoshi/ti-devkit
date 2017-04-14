/* wchar.h minimal header for C++ */
#ifndef _WCHAR
#define _WCHAR
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

#include <stddef.h>
#include <stdio.h>

_C_STD_BEGIN

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
#if defined(__TI_EABI_SUPPORT__)
#define _AEABI_PORTABILITY_CHECK (defined(__TMS470__) && \
                                  defined(__TI_EABI_SUPPORT__) && \
                                  defined(_AEABI_PORTABILITY_LEVEL) && \
                                  _AEABI_PORTABILITY_LEVEL != 0)
#else
#define _AEABI_PORTABILITY_CHECK 0
#endif

		/* MACROS */
#ifndef WEOF
 #define WEOF	((_CSTD wint_t)(-1))
#endif /* WEOF */

#ifndef WCHAR_MIN
 #define WCHAR_MIN 0
#endif

#ifndef WCHAR_MAX
#if !defined(__TI_WCHAR_T_BITS__) || __TI_WCHAR_T_BITS__ == 16
#define WCHAR_MAX 0xffffu
#else 
#define WCHAR_MAX 0xffffffffu
#endif
#endif

		/* TYPE DEFINITIONS */

 #ifndef _MBSTATET
  #define _MBSTATET
#if _AEABI_PORTABILITY_CHECK
    typedef struct _Mbstatet {
        unsigned int __state, __state2;
    } _Mbstatet;
#else
typedef int _Mbstatet;
#endif /* _AEABI_PORTABILITY_CHECK */
 #endif /* _MBSTATET */

typedef _Mbstatet mbstate_t;
struct tm;

#ifndef _WINTT
#define _WINTT
typedef int wint_t;
#endif

_C_LIB_DECL
		/* FUNCTIONS */
wint_t btowc(int);
wint_t fgetwc(FILE *);
wint_t fputwc(wchar_t, FILE *);
size_t mbrtowc(wchar_t *, const char *, size_t, mbstate_t *);
wint_t ungetwc(wint_t, FILE *);
size_t wcslen(const wchar_t *);
size_t wcrtomb(char *, wchar_t, mbstate_t *);
int wctob(wint_t);

int wmemcmp(const wchar_t *, const wchar_t *, size_t);
wchar_t *wmemcpy(wchar_t *, const wchar_t *, size_t);
wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t);
wchar_t *wmemset(wchar_t *, wchar_t, size_t);

int fwide(FILE *str, int mode);

wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);

_END_C_LIB_DECL

	/* inlines/macros */

_C_STD_END
#endif /* _WCHAR */

 #if defined(_STD_USING)
using _CSTD mbstate_t; using _CSTD tm; using _CSTD wint_t;

using _CSTD btowc; 
using _CSTD fgetwc; 
using _CSTD fputwc;
using _CSTD mbrtowc;
using _CSTD ungetwc;
using _CSTD wcslen;
using _CSTD wcrtomb; 
using _CSTD wctob;
using _CSTD wmemcmp; 
using _CSTD wmemcpy;
using _CSTD wmemmove; 
using _CSTD wmemset; 
using _CSTD wmemchr; 
using _CSTD fwide; 

 #endif /* defined(_STD_USING) */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
