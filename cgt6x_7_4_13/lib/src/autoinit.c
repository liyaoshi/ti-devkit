/*****************************************************************************/
/* _AUTO_INIT()   v7.4.13 - Perform initialization of C variables.           */
/*                                                                           */
/* Copyright (c) 1993-2015 Texas Instruments Incorporated                    */
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
#include <cpy_tbl.h>

#define ALIGN_MASK 0x7
#define ALIGN_PTR(ptr) \
   ((unsigned *)(((unsigned)ptr + ALIGN_MASK) & ~ALIGN_MASK))

typedef void (*PTRFUNC)();
#ifdef __TI_EABI__

typedef void (*handler_fptr)(const unsigned char* in, unsigned char* out);

#define HANDLER_TABLE __TI_Handler_Table_Base
#pragma WEAK(HANDLER_TABLE);

extern far unsigned int HANDLER_TABLE;

#pragma WEAK(__TI_Handler_Table_Limit);
extern far unsigned int __TI_Handler_Table_Limit;

#pragma WEAK(__TI_CINIT_Base);
#pragma WEAK(__TI_CINIT_Limit);

extern far unsigned char* __TI_CINIT_Base;
extern far unsigned char* __TI_CINIT_Limit;

extern void  __TI_tls_init(void * TLS_block_addr);

#endif

#define BINIT ((COPY_TABLE*)&__binit__)
extern far const COPY_TABLE *__binit__;

extern void __TI_cpp_init(void);

#ifndef __TI_EABI__
void _auto_init(const void *cinit)
{
   const unsigned int *recptr = cinit;
   int length;

   /*------------------------------------------------------------------------*/
   /* Process Binit table                                                    */
   /*                                                                        */
   /* -1 indicates no table, otherwise just call copy_in(), which handles    */
   /* all the copying even if in compressed format.                          */
   /*------------------------------------------------------------------------*/
   if ((int)BINIT != -1) copy_in(BINIT);

   /*------------------------------------------------------------------------*/
   /* Process Cinit table.                                                   */
   /*------------------------------------------------------------------------*/
   if ((int)recptr != -1)
      while ((length = *recptr++) != 0)
      {
	 char *to   = (void*) *recptr++; 
	 char *from = (void*) recptr; 

	 memcpy(to, from, length); 

	 from   += length;
	 recptr  = ALIGN_PTR(from);
      }

   /*------------------------------------------------------------------------*/
   /* Initialize C++ global objects.                                         */
   /*------------------------------------------------------------------------*/
   __TI_cpp_init();
}
      
#else

void _auto_init_elf(void)
{
   unsigned char** table_ptr;
   unsigned char** table_limit;

   /*------------------------------------------------------------------------*/
   /* Process Binit table                                                    */
   /*                                                                        */
   /* -1 indicates no table, otherwise just call copy_in(), which handles    */
   /* all the copying even if in compressed format.                          */
   /*------------------------------------------------------------------------*/
    if ((int)BINIT != -1) copy_in(BINIT);

   /*------------------------------------------------------------------------*/
   /* If elfabi, process the compressed cinit table. The format              */
   /* is as follows:                                                         */
   /* |4-byte load addr|4-byte run addr|                                     */
   /* |4-byte load addr|4-byte run addr|                                     */
   /*                                                                        */
   /* Processing steps:                                                      */
   /*   1. Read load and run address.                                        */
   /*   2. Read one byte at load address, say idx.                           */
   /*   3. Get pointer to handler at handler_start[idx]                      */
   /*   4. call handler(load_addr + 1, run_addr)                             */
   /*------------------------------------------------------------------------*/
   if (!(&__TI_Handler_Table_Base >= &__TI_Handler_Table_Limit))
   {
      table_ptr   = (unsigned char**) &__TI_CINIT_Base;
      table_limit = (unsigned char**) &__TI_CINIT_Limit;
      while (table_ptr < table_limit)
      {
        unsigned char* load_addr  = *table_ptr++;
        unsigned char* run_addr   = *table_ptr++;
        unsigned char handler_idx = *load_addr++;

        handler_fptr handler      = (handler_fptr)(&HANDLER_TABLE)[handler_idx];

        (*handler)((const unsigned char*)load_addr, run_addr);
      }
   }

   /*------------------------------------------------------------------------*/
   /* Initialize master thread's Thread-Local variables. The RTS library     */
   /* provides the function __TI_tls_init to initialize TLS block of a       */
   /* given thread.  The address of the newly allocated TLS Block of the     */
   /* thread is passed as input parameter to this routine. If NULL is passed */
   /* the master thread's TLS block allocated by the linker is initialized.  */
   /*------------------------------------------------------------------------*/
   __TI_tls_init(NULL);

   /*------------------------------------------------------------------------*/
   /* Initialize C++ global objects.                                         */
   /*------------------------------------------------------------------------*/
   __TI_cpp_init();
}

#endif
