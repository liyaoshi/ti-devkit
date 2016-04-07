/*****************************************************************************/
/* ctype.h    v5.0.7                                                         */
/*                                                                           */
/* Copyright (c) 1993-2013 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

/************************************************************************/
/*                                                                      */
/*  CHARACTER TYPING FUNCTIONS AND MACROS                               */
/*                                                                      */
/*  Note that in this implementation, either macros or functions may    */
/*  be used.  Macros are prefixed with an underscore.                   */
/*                                                                      */
/************************************************************************/
#ifndef _CTYPE
#define _CTYPE

#include <linkage.h>


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
	                          _AEABI_PORTABILITY_LEVEL != 0)
#else
#define _AEABI_PORTABILITY_CHECK 0
#endif

#ifdef __cplusplus
//----------------------------------------------------------------------------
// <cctype> IS RECOMMENDED OVER <ctype.h>.  <ctype.h> IS PROVIDED FOR
// COMPATIBILITY WITH C AND THIS USAGE IS DEPRECATED IN C++
//----------------------------------------------------------------------------
extern "C" namespace std
{
#endif /* __cplusplus */

extern const _DATA_ACCESS unsigned char _ctypes_[];

/************************************************************************/
/*   FUNCTION DECLARATIONS                                              */
/************************************************************************/
#include "_isfuncdcl.h"

_IDECL int toupper(int _c);
_IDECL int tolower(int _c);

#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

#if _AEABI_PORTABILITY_CHECK
extern unsigned char const __aeabi_ctype_table_C[257];  /* "C" locale */
extern unsigned char const __aeabi_ctype_table_[257];    /* default locale */
         
  #ifdef _AEABI_LC_CTYPE
     #define _AEABI_CTYPE_TABLE(_X) __aeabi_ctype_table_ ## _X
     #define _AEABI_CTYPE(_X) _AEABI_CTYPE_TABLE(_X)
     #define __aeabi_ctype_table _AEABI_CTYPE(_AEABI_LC_CTYPE)
  #else
     #define __aeabi_ctype_table __aeabi_ctype_table_
  #endif

/* AEABI portable ctype flag bits */
#define _ABI_A    1       /* alphabetic        */
#define _ABI_X    2       /* A-F, a-f and 0-9  */
#define _ABI_P    4       /* punctuation       */
#define _ABI_B    8       /* blank             */
#define _ABI_S   16       /* white space       */
#define _ABI_L   32       /* lower case letter */
#define _ABI_U   64       /* upper case letter */
#define _ABI_C  128       /* control chars     */

#define _isspace(x)  ((__aeabi_ctype_table+1)[(x)] & _ABI_S)
#define _isalpha(x)  ((__aeabi_ctype_table+1)[(x)] & _ABI_A)
#define _isalnum(x)  ((__aeabi_ctype_table+1)[(x)] << 30) /* test for _ABI_A and _ABI_X */
#define _isprint(x)  ((__aeabi_ctype_table+1)[(x)] << 28) /* test for _ABI_A, _ABI_X, _ABI_P and _ABI_B */
#define _isupper(x)  ((__aeabi_ctype_table+1)[(x)] & _ABI_U)
#define _islower(x)  ((__aeabi_ctype_table+1)[(x)] & _ABI_L)
#define _isxdigit(x) ((__aeabi_ctype_table+1)[(x)] & _ABI_X)
/* no isblank() here as we do not support C99 in TI RTS */
#define _isgraph(x)  ((__aeabi_ctype_table+1)[(x)] << 29) /* test for _ABI_A, _ABI_X and _ABI_P */
#define _iscntrl(x)  ((__aeabi_ctype_table+1)[(x)] & _ABI_C)
#define _ispunct(x)  ((__aeabi_ctype_table+1)[(x)] & _ABI_P)
#define _isdigit(c)  (((unsigned)(c) - '0') < 10)

#else

/************************************************************************/
/*  On this ELSE path, all the TI ctype table and ctype bit flags are   */
/*  defined.                                                            */
/************************************************************************/
/************************************************************************/
/*  MACRO DEFINITIONS                                                   */
/************************************************************************/
#define _U_   0x01       /* control chars     */
#define _L_   0x02       /* lower case letter */
#define _N_   0x04       /* digit             */
#define _S_   0x08       /* white space       */
#define _P_   0x10       /* punctuation       */
#define _C_   0x20       /* control chars     */
#define _H_   0x40       /* A-F, a-f and 0-9  */
#define _B_   0x80       /* blank             */

#define _isalnum(a)  (_ctypes_[(a)+1] & (_U_ | _L_ | _N_))
#define _isalpha(a)  (_ctypes_[(a)+1] & (_U_ | _L_))
#define _iscntrl(a)  (_ctypes_[(a)+1] & _C_)
#define _isdigit(a)  (_ctypes_[(a)+1] & _N_)
#define _isgraph(a)  (_ctypes_[(a)+1] & (_U_ | _L_ | _N_ | _P_))
#define _islower(a)  (_ctypes_[(a)+1] & _L_)
#define _isprint(a)  (_ctypes_[(a)+1] & (_B_ | _U_ | _L_ | _N_ | _P_))
#define _ispunct(a)  (_ctypes_[(a)+1] & _P_)
#define _isspace(a)  (_ctypes_[(a)+1] & _S_)
#define _isupper(a)  (_ctypes_[(a)+1] & _U_)
#define _isxdigit(a) (_ctypes_[(a)+1] & _H_)

#endif /* _AEABI_PORTABILITY_CHECK */

#define _isascii(a)  (((a) & ~0x7F) == 0)
#define _toupper(b)  ((_islower(b)) ? (b) - ('a' - 'A') : (b))
#define _tolower(b)  ((_isupper(b)) ? (b) + ('a' - 'A') : (b))
#define _toascii(a)  ((a) & 0x7F)

#ifdef _INLINE

#ifdef __cplusplus
using std::_ctypes_;
namespace std {
#endif /* __cplusplus */

#include "_isfuncdef.h"

/****************************************************************************/
/*  tolower                                                                 */
/****************************************************************************/
static __inline int tolower(int ch)
{
   /*
    This code depends on two assumptions: (1) all of the letters of the
    alphabet of a given case are contiguous, and (2) the lower and upper
    case forms of each letter are displaced from each other by the same
    constant value.
   */

   if ( (unsigned int)(ch - 'A') <= (unsigned int)('Z' - 'A')) ch += 'a' - 'A';
   return ch;
}

/****************************************************************************/
/*  toupper                                                                 */
/****************************************************************************/
static __inline int toupper(int ch)
{
   /*
    This code depends on two assumptions: (1) all of the letters of the
    alphabet of a given case are contiguous, and (2) the lower and upper
    case forms of each letter are displaced from each other by the same
    constant value.
   */

   if ( (unsigned int)(ch - 'a') <= (unsigned int)('z' - 'a')) ch -= 'a' - 'A';
   return ch;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _INLINE */

#endif /* ! _CTYPE */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::_ctypes_;
using std::isalnum;
using std::isalpha;
using std::iscntrl;
using std::isdigit;
using std::isgraph;
using std::islower;
using std::isprint;
using std::ispunct;
using std::isspace;
using std::isupper;
using std::isxdigit;
using std::isascii;
using std::toupper;
using std::tolower;
using std::toascii;
#endif /* ! _CPP_STYLE_HEADER */

