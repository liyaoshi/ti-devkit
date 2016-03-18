/*****************************************************************************/
/*  TRGMSG.C v7.4.13                                                         */
/*                                                                           */
/* Copyright (c) 1995-2015 Texas Instruments Incorporated                    */
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

/*****************************************************************************/
/* Bottom level data transfer routines for host communication with the       */
/* target.                                                                   */
/*                                                                           */
/* Functions:                                                                */
/*  writemsg()  -  Sends the passed data and parameters on to the host.      */
/*  readmsg()   -  Reads the data and parameters passed from the host.       */
/*                                                                           */
/* IMPORTANT!                                                                */
/*                                                                           */
/*  For multi-threaded applications, calls to writemsg() and readmsg()       */
/*  should be enclosed in a __TI_LOCK_HOST_CIO critical region. While the    */
/*  parm argument in both functions points to a shared resource (parmbuf[]   */
/*  in lowlev.c), it makes more sense to synchronize it in the function that */
/*  calls writemsg() or readmsg(). With regards to _CIOBUF_ (another shared  */
/*  resource), it is only accessed in this file, so it makes more sense to   */
/*  synchronize it here even though the critical region that protects access */
/*  to it is defined around the call site.                                   */
/*                                                                           */
/*****************************************************************************/
#include "stdio.h"
#include "trgcio.h"
#include <_data_synch.h>


#if BSSCIOBUF
#define DEFCIO(size) unsigned char _CIOBUF_[size]

#elif defined(_MVP_PP) || defined(_MVP_MP)
#pragma SHARED   (_CIOBUF_);
#pragma DATA_SECTION (_CIOBUF_, ".cio");
#pragma DATA_ALIGN   (_CIOBUF_, 4);
#define DEFCIO(size) volatile unsigned char _CIOBUF_[size]

#else

#ifdef __TI_EABI__
#define _CIOBUF_ __CIOBUF_
#endif

#pragma DATA_SECTION (_CIOBUF_, ".cio");
#pragma DATA_ALIGN   (_CIOBUF_, 4);
#define DEFCIO(size) _DATA_ACCESS volatile unsigned char _CIOBUF_[size]

#endif

DEFCIO(CIOBUFSIZ);


/***************************************************************************/
/*                                                                         */
/*  WRITEMSG()  -  Sends the passed data and parameters on to the host.    */
/*                                                                         */
/***************************************************************************/
_CODE_ACCESS void writemsg(               unsigned char  command,
                           register const unsigned char *parm,
                           register const          char *data,
                                          unsigned int   length)
{
#if defined(_MVP_PP)
    extern unsigned char *_gen_addr(unsigned char *p);
    register unsigned char *p = _gen_addr(_CIOBUF_);
#else
    register unsigned volatile char * p = (volatile unsigned char *) _CIOBUF_;
#endif

    register unsigned int i;

    /***********************************************************************/
    /* THE LENGTH IS WRITTEN AS A TARGET INT                               */
    /***********************************************************************/ 
    *(unsigned int *)p = length; 
    p += sizeof(unsigned int);

    /***********************************************************************/ 
    /* THE COMMAND IS WRITTEN AS A TARGET BYTE                             */
    /***********************************************************************/ 
    *p++ = command;

    /***********************************************************************/ 
    /* PACK THE PARAMETERS AND DATA SO THE HOST READS IT AS BYTE STREAM    */
    /***********************************************************************/ 
    for (i = 0; i < 8; i++)      PACKCHAR(*parm++, p, i);
    for (i = 0; i < length; i++) PACKCHAR(*data++, p, i+8);

    /***********************************************************************/ 
    /* SINCE _CIOBUF_ IS A SHARED RESOURCE, THE CURRENT THREAD IN A        */
    /* MULTI-THREADED APPLICATION MUST SYNCH ITS LOCAL COPY OF _CIOBUF_    */
    /* WITH SHARED MEMORY SINCE WE EXPECT THE HOST TO READ FROM SHARED     */
    /* MEMORY WHEN IT REACHES THE C$$IO$$ BREAKPOINT.                      */
    /***********************************************************************/ 
    /* See file header comments for more details.                          */
    /***********************************************************************/ 
    __TI_data_synch_WBINV(&_CIOBUF_, CIOBUFSIZ);


#pragma diag_suppress 1119
#ifndef __VIRTUAL_ENCODING__
    /***********************************************************************/
    /* THE BREAKPOINT THAT SIGNALS THE HOST TO DO DATA TRANSFER            */
    /***********************************************************************/
#if defined(_MVP_PP) || defined(_MVP_MP)
    __asm("	.system	C$$IO$$");
#else
    __asm("	.global	C$$IO$$");
#endif
    __asm("	nop");
    __asm("C$$IO$$:nop");
#else
    /*---------------------------------------------------------------------*/
    /* GENERATE THE C$$IO INSTRUCTION                                      */
    /*---------------------------------------------------------------------*/
    __asm("       .vinstr   C$$IO");
    __asm("C$$IO: .encode \"C$$IO\", $ENC_OPNDS, 0");
#endif
#pragma diag_default 1119
}


/***************************************************************************/
/*                                                                         */
/*  READMSG()   -  Reads the data and parameters passed from the host.     */
/*                                                                         */
/***************************************************************************/
_CODE_ACCESS void readmsg(register unsigned char *parm,
                          register char          *data)
{
#if defined(_MVP_PP)
    extern unsigned char *_gen_addr(unsigned char *);
    register unsigned char *p = _gen_addr(_CIOBUF_);
#else
    register unsigned volatile char * p = (volatile unsigned char *) _CIOBUF_;
#endif

    register unsigned int i;
    unsigned int length;

    /***********************************************************************/
    /* THE LENGTH IS READ AS A TARGET INT                                  */
    /***********************************************************************/
    length = *(unsigned int *)p;
    p += sizeof(unsigned int);
    
    /***********************************************************************/
    /* UNPACK THE PARAMETERS AND DATA                                      */
    /***********************************************************************/
    for (i = 0; i < 8; i++) *parm++ = UNPACKCHAR(p, i);
    if (data != NULL) 
       for (i = 0; i < length; i++) *data++ = UNPACKCHAR(p, i+8);

    /***********************************************************************/ 
    /* THE CURRENT THREAD IN A MULTI-THREADED APPLICATION MUST SYNCH ITS   */
    /* LOCAL COPY OF _CIOBUF_ WITH SHARED MEMORY SINCE _CIOBUF_ IS A       */
    /* SHARED RESOURCE.                                                    */
    /***********************************************************************/ 
    /* See file header comments for more details.                          */
    /***********************************************************************/ 
    __TI_data_synch_WBINV(&_CIOBUF_, CIOBUFSIZ);
}
