/* errno.h standard header */
#ifndef _ERRNO
#define _ERRNO
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
    extern const    int __aeabi_EDOM;
    extern const    int __aeabi_ERANGE;
    extern const    int __aeabi_EILSEQ;
    extern volatile int *__aeabi_errno_addr(void);
    #define EDOM (__aeabi_EDOM)
    #define ERANGE (__aeabi_ERANGE)
    #define EILSEQ (__aeabi_EILSEQ)
    #define errno (*__aeabi_errno_addr())
_END_EXTERN_C
#else  /* _AEABI_PORTABILITY_CHECK */
		/* ERROR CODES */
#define EDOM           0x0021
#define EFAULT         0x000E
#define EFBIG          0x001B
#define EFPOS          0x0098
#define EMLINK         0x001F
#define ENFILE         0x0017
#define ENOENT         0x0002
#define ENOSPC         0x001C
#define ENOTTY         0x0019
#define EPIPE          0x0020
#define ERANGE         0x0022
#define EROFS          0x001E
#define ESPIPE         0x001D

  #define E2BIG         0x0007  
  #define EACCES        0x000D  
  #define EAGAIN        0x000B  
  #define EBADF         0x0009  
  #define EBUSY         0x0010  
  #define ECHILD        0x000A  
  #define EEXIST        0x0011  
  #define EINTR         0x0004  
  #define EINVAL        0x0016  
  #define EIO           0x0005  
  #define EISDIR        0x0015  
  #define EMFILE        0x0018  
  #define ENODEV        0x0013  
  #define ENOEXEC       0x0008  
  #define ENOMEM        0x000C  
  #define ENOTDIR       0x0014  
  #define ENXIO         0x0006  
  #define EPERM         0x0001  
  #define ESRCH         0x0003  
  #define EXDEV         0x0012  

 #if defined(_LINUX_C_LIB)
  #define EBADMSG       0x004A
  #define ECANCELED     0x007D
  #define EDEADLK       0x0023
  #define EILSEQ        0x0054
  #define EINPROGRESS   0x0073
  #define EMSGSIZE      0x005A
  #define ENAMETOOLONG  0x0024
  #define ENOLCK        0x0025
  #define ENOSYS        0x0026
  #define ENOTEMPTY     0x0027
  #define ENOTSUP       0x005F
  #define ETIMEDOUT     0x006E

 #else /* library type */
  #define EBADMSG       0x004D  
  #define ECANCELED     0x002F  
  #define EDEADLK       0x002D  
  #define EILSEQ        0x0058
  #define EINPROGRESS   0x0096  
  #define EMSGSIZE      0x0061  
  #define ENAMETOOLONG  0x004E  
  #define ENOLCK        0x002E  
  #define ENOSYS        0x0059  
  #define ENOTEMPTY     0x005D  
  #define ENOTSUP       0x0030  
  #define ETIMEDOUT     0x0091  
 #endif /* library type */

#endif /* _AEABI_PORTABILITY_CHECK */
		/* DECLARATIONS */
_C_LIB_DECL

 #if !_MULTI_THREAD || _COMPILER_TLS && !_GLOBAL_LOCALE

#if defined(__TI_COMPILER_VERSION__)
extern _DATA_ACCESS int _TLS_QUAL _Errno;
#else
extern int _TLS_QUAL _Errno;
#endif /* defined(__TI_COMPILER_VERSION__) */

 #if !(_AEABI_PORTABILITY_CHECK)
  #define errno	(_CSTD _Errno)
 #endif

 #else /* !_MULTI_THREAD || _COMPILER_TLS && !_GLOBAL_LOCALE */
int *_Geterrno(void);

 #if !(_AEABI_PORTABILITY_CHECK)
  #define errno	(*_CSTD _Geterrno())
 #endif
 #endif /* !_MULTI_THREAD || _COMPILER_TLS && !_GLOBAL_LOCALE */

_END_C_LIB_DECL
_C_STD_END

 #if defined(_STD_USING)
  #if _AEABI_PORTABILITY_CHECK 
using _CSTD __aeabi_EDOM;
using _CSTD __aeabi_ERANGE;
using _CSTD __aeabi_EILSEQ;
using _CSTD __aeabi_errno_addr;
  #endif
 #endif /* defined(_STD_USING) */

#endif /* _ERRNO */
/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
