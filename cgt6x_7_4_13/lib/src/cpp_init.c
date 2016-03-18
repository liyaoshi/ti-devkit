/*****************************************************************************/
/* CPP_INIT()   v7.4.13 - Initialization of C++ globals, callable from       */
/*                       outside RTS.                                        */
/*                                                                           */
/* Copyright (c) 2012-2015 Texas Instruments Incorporated                    */
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
#include <string.h>

typedef void (*PTRFUNC)();

#ifndef __TI_EABI__

   extern far const PTRFUNC __pinit__[];

#else

#pragma WEAK(__TI_INITARRAY_Limit);
#pragma WEAK(__TI_INITARRAY_Base);

extern far const PTRFUNC __TI_INITARRAY_Base[];
extern far const PTRFUNC __TI_INITARRAY_Limit[];

#endif

void __TI_cpp_init(void)
{
#ifndef __TI_EABI__
   /*------------------------------------------------------------------------*/
   /* Process Pinit table.                                                   */
   /* consists of pointers to init functions.                                */
   /* section is NULL terminated                                             */
   /* pointer is = -1 if section does not exist.                             */
   /*------------------------------------------------------------------------*/
   if ((int)__pinit__ != -1)
   {
      int i = 0;
      while (__pinit__[i] != NULL )
         __pinit__[i++]();
   }

#else
   /*------------------------------------------------------------------------*/
   /* Process Pinit table for ELF.                                           */
   /* The section is not NULL terminated, but can be accessed by pointers    */
   /* which point to the beginning and end of the section.                   */
   /*------------------------------------------------------------------------*/
   if (__TI_INITARRAY_Base != __TI_INITARRAY_Limit)
   {
      int i = 0;
      while (&(__TI_INITARRAY_Base[i]) != __TI_INITARRAY_Limit)
         __TI_INITARRAY_Base[i++]();
   }
#endif

}

