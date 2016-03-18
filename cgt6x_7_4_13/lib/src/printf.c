/*****************************************************************************/
/*  PRINTF.C v7.4.13                                                         */
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
/* Functions:                                                                */
/*    PRINTF   -  Print formatted output to stdio                            */
/*    _OUTC    -  Put a character in a stream                                */
/*    _OUTS    -  Put a string in a stream                                   */
/*****************************************************************************/
#include <stdio.h>
#include <_mutex.h>
#include <_data_synch.h>
#include "format.h"
#include <stdarg.h>
#include <string.h>
 
extern _CODE_ACCESS int _printfi(char **_format, va_list _ap, void *_op, 
                                 int (*_outc)(char, void *), 
				 int (*_outs)(char *, void *, int));
 
static int _outc(char c, void *_op);
static int _outs(char *s, void *_op, int len);
 

/*****************************************************************************/
/* PRINTF   -  Print formatted output to stdio                               */
/*                                                                           */
/*    This function passes a the format string and an argument list to       */
/*    _PRINTFI, and writes the result string to the stream stdio.            */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int printf(const char *_format, ...)
{
   va_list _ap;
   int rval;
   char *fptr = (char *)_format;
 
   /*------------------------------------------------------------------------*/
   /* The current thread in a multi-threaded application must protect access */
   /* to __TI_LOCK_FILE_TBL shared resources (_ftable[], _ft_end, and        */
   /* _tmpnams[]). In this case, _ftable[] may be updated, so we must ensure */
   /* that the local copy of _ftable[] is flushed to shared memory before    */
   /* leaving the critical section (invalidated if it is not modified).      */
   /*------------------------------------------------------------------------*/
   __TI_resource_lock(__TI_LOCK_FILE_TBL);

   /*------------------------------------------------------------------------*/
   /* If the current stream is not associated with a file, return an error.  */
   /*------------------------------------------------------------------------*/
   if (stdout->fd == -1) 
   { 
      __TI_data_synch_INV(&_ftable, sizeof(_ftable));
      __TI_resource_unlock(__TI_LOCK_FILE_TBL);
      return (-1);
   }

   va_start(_ap, _format);
   rval = _printfi(&fptr, _ap, (void *)stdout, _outc, _outs);
   va_end(_ap);

   __TI_data_synch_WBINV(&_ftable, sizeof(_ftable));
   __TI_resource_unlock(__TI_LOCK_FILE_TBL);
   return (rval);
}
 

/*****************************************************************************/
/* _OUTC -  Put a character in a stream                                      */
/*****************************************************************************/
static int _outc(char c, void *_op) { return (fputc(c, (FILE *)_op)); }
 

/*****************************************************************************/
/* _OUTS -  Put a string in a stream                                         */
/*****************************************************************************/
static int _outs(char *s, void *_op, int len) { return (fputs(s, (FILE *)_op)); }

