/* limits.h standard header -- 8-bit version */
#ifndef _LIMITS
#define _LIMITS
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

  #if _BITS_BYTE != 8
    #error <limits.h> assumes 8 bits per byte
  #endif /* _BITS_BYTE != 8 */
 #if defined(_LIMITS_H___)
  #undef MB_LEN_MAX
  #define MB_LEN_MAX	_MBMAX

 #else /* defined(_LIMITS_H___) */
  #define _LIMITS_H___
		/* CHAR PROPERTIES */
  #define CHAR_BIT	_BITS_BYTE

  #if _CSIGN
   #define CHAR_MAX	SCHAR_MAX
   #define CHAR_MIN	SCHAR_MIN

  #else /* _CSIGN */
   #define CHAR_MAX	UCHAR_MAX
   #define CHAR_MIN	0
  #endif /* _CSIGN */

		/* INT PROPERTIES */

  #if _ILONG
      #define INT_MAX		LONG_MAX
      #define INT_MIN		LONG_MIN
      #define UINT_MAX	ULONG_MAX
  #else /* _ILONG */
   #define INT_MAX		SHRT_MAX
   #define INT_MIN		SHRT_MIN
   #define UINT_MAX	USHRT_MAX
  #endif /* _ILONG */

		/* MULTIBYTE PROPERTIES */
#if _AEABI_PORTABILITY_CHECK
_C_STD_BEGIN
_EXTERN_C
  extern const int __aeabi_MB_LEN_MAX;
_END_EXTERN_C
_C_STD_END
  #define MB_LEN_MAX (__aeabi_MB_LEN_MAX)
#else
  #define MB_LEN_MAX	_MBMAX
#endif

		/* SIGNED CHAR PROPERTIES */
  #define SCHAR_MAX	0x7f
  #define SCHAR_MIN	(-SCHAR_MAX - _C2)

		/* SHORT PROPERTIES */
  #define SHRT_MAX	0x7fff
  #define SHRT_MIN	(-SHRT_MAX - _C2)

		/* LONG PROPERTIES */
  #define LONG_MAX	0x7fffffff
  #define LONG_MIN	(-LONG_MAX - _C2)

		/* UNSIGNED PROPERTIES */
  #define UCHAR_MAX	0xff
  #define USHRT_MAX	0xffff
    #define ULONG_MAX	  0xffffffffU
 #endif /* defined(_LIMITS_H___) */

 #if _HAS_C9X || defined(_C99_MATH) || defined(__TMS320C27X__)
#define LLONG_MAX	_LLONG_MAX
#define LLONG_MIN	(-_LLONG_MAX - _C2)
#define ULLONG_MAX	_ULLONG_MAX
#endif /* _HAS_C9X || _C99_MATH || __TMS320C27X__ */

 #if defined(_STD_USING)
  #if _AEABI_PORTABILITY_CHECK
using _CSTD __aeabi_MB_LEN_MAX;
  #endif
 #endif /* defined(_STD_USING) */

#endif /* _LIMITS */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
