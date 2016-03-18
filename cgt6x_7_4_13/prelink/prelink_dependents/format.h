/*****************************************************************************/
/*  FORMAT.H v#####                                                          */
/*  Copyright (c) 1995@%%%% Texas Instruments Incorporated                   */
/*****************************************************************************/

/*****************************************************************************/
/* Structures and macros used in printf and scanf                            */
/*****************************************************************************/
#ifndef __FORMAT_H
#define __FORMAT_H
#include <stdarg.h>


#if defined (MINIMAL)
#define FORMAT_CONVERSION_BUFSIZE 32
#elif defined (__MSP430__)
#define FORMAT_CONVERSION_BUFSIZE 100
#define F_CONVERSION_BUFSIZE      100
#define FLOAT_VALUE_BUFSIZE       32
#else
#define FORMAT_CONVERSION_BUFSIZE 400
#define F_CONVERSION_BUFSIZE      400
#define FLOAT_VALUE_BUFSIZE       100
#endif

#ifdef __cplusplus
extern "C" namespace std {
#else 
extern
#endif

  int _scanfi(void *inp, const char *_format, va_list _ap,
	      int (*_chkmbc)(void **inp, char **_format, int *num_read),
	      int (*_inpchar)(void **inp),
	      void (*_uninpchar)(void **inp, int outchar));
 
  /**************************************************************************/
  /* _FIELD STRUCTURE AND MACROS USED FOR PRINTF AND SCANF                  */
  /**************************************************************************/
  typedef struct {
    unsigned int flags;         /* Format flags */
    int          fwidth;        /* Field width */
    int          precision;     /* Field precision */
    char         conv;          /* Conversion specifier */
  } _PFIELD;
  
  typedef struct {
    unsigned int flags;         /* Format flags */
    int          fwidth;        /* Field width */
    int          precision;     /* Field precision */
    char         scanset[96];   /* Scanset used for '[' conversion */
    char         conv;          /* Conversion specifier */
  } _SFIELD;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/****************/
/* PRINTF FLAGS */
/****************/

#define _PFMINUS  0x01
#define _PFPLUS   0x02
#define _PFSPACE  0x04
#define _PFPOUND  0x08
#define _PFZERO   0x10
 
/***************/
/* SCANF FLAGS */
/***************/

#define _SFSTAR   0x01
#define _SFCIRC   0x02

/****************/
/* MUTUAL FLAGS */
/****************/

#define _MFH      0x20
#define _MFL      0x40
#define _MFLD     0x80
#define _MFLL     0x100
#define _MFHH     0x200

#endif
