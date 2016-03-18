/*****************************************************************************/
/* copy_decompress_rle.c    v7.4.13                                          */
/*                                                                           */
/* Copyright (c) 2006-2015 Texas Instruments Incorporated                    */
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
/*                                                                           */
/* Decompress routine for the Run-length encoding compression. Given an      */
/* input buffer with data compressed using run-length encoding and an        */
/* output buffer, this routine decompresses the data in the output buffer.   */
/*                                                                           */
/* NOTE:                                                                     */
/* 1. This routine could be used to copy uninitialized or initialized global */
/*    data space of a program. Hence this routine cannot define any global   */
/*    variable.                                                              */
/* 2. This routine will never be used to initialize stack space and hence    */
/*    all the variables are allocated to stack.                              */
/* 3. The calling application should ensure the output buffer is big         */
/*    enough to hold the uncompressed data.                                  */
/*                                                                           */
/*****************************************************************************/
#include <string.h>

static __inline void *optimized_mem_set(void *mem, int ch, size_t n);

/*****************************************************************************/
/*                                                                           */
/* __TI_DECOMPRESS_RLE() - Decompress the run length encoding.               */
/*                                                                           */
/* NOTE: More recent versions of the linker (circa 10/2010) will generate a  */
/*       call to __TI_decompress_rle24() (or _TI_decompress_rle24() for      */
/*       TMS470 non-EABI applications). We are keeping the old version of    */
/*       the RLE decompression around so that newer libraries will work with */
/*       older tools.                                                        */
/*                                                                           */
/*****************************************************************************/
#define RLE_FUNCTION __TI_decompress_rle
#define RLE24_FUNCTION __TI_decompress_rle24

/*****************************************************************************/
/* MSP copy tables can handle moving functions even in small data model +    */
/* large code model, where data pointers are not big enough to represent     */
/* function pointers.  This requires the EABI decompression functions        */
/* (SHARED/copy_*.c) to be changed to accept "far" pointers.  For this       */
/* memory model combination, the decompression functions are changed to use  */
/* "unsigned long" to represent function pointers, so function pointers      */
/* through which we call these functions also needs to have a prototype      */
/* accepting "unsigned long" instead of pointer types.  All other memory     */
/* model combinations use the same prototype that all the other targets use: */
/* two data pointer arguments.  Ultimately we use MSP peek/poke intrinsics   */
/* to read/write the "far" memory.                                           */
/*****************************************************************************/
typedef       unsigned char *pointer_t;
typedef const unsigned char *pointer_to_const_t;
#define READ8_ADV(x)    (*x++)
#define WRITE8_ADV(x,c) (*x++ = (c))

static void __TI_decompress_rle_core(pointer_to_const_t inbuf, 
                                     pointer_t          outbuf, 
                                     int                is_rle24);

#pragma CODE_SECTION(RLE_FUNCTION, ".text:decompress:rle")

void RLE_FUNCTION(const pointer_t inbuf, pointer_t outbuf)
{
   __TI_decompress_rle_core(inbuf, outbuf, 0);
}

#pragma CODE_SECTION(RLE24_FUNCTION, ".text:decompress:rle24")

void RLE24_FUNCTION(const pointer_t inbuf, pointer_t outbuf)
{
   __TI_decompress_rle_core(inbuf, outbuf, 1);
}

static void __TI_decompress_rle_core(pointer_to_const_t inbuf, 
                                     pointer_t          outbuf, int is_rle24)
{
   /*------------------------------------------------------------------------*/
   /* The first byte is the delimiter. Save it to 'delim'.                   */
   /*------------------------------------------------------------------------*/
   unsigned char  delim = READ8_ADV(inbuf);
   unsigned char  ch;
   unsigned int   run_len;

   while(1)
   {
      /*---------------------------------------------------------------------*/
      /* Read the next byte.                                                 */
      /*---------------------------------------------------------------------*/
      ch = READ8_ADV(inbuf);

      /*---------------------------------------------------------------------*/
      /* If this byte is not delimiter, we have no-repeat byte. Just write i */
      /* to output and continue.                                             */
      /*---------------------------------------------------------------------*/
      if (ch != delim)
      {
         WRITE8_ADV(outbuf, ch);
         continue;
      }

      /*---------------------------------------------------------------------*/
      /* The current byte is the delimiter. We could have one of the         */
      /* following sequences:                                                */
      /* 1. zero, 16-bit run length, repeated char.                          */
      /* 2. zero, zero, 24-bit run length, repeated char.                    */
      /* 3. 8-bit length with value less then 4. This means delimiter is     */
      /*    repeated by the run length times.                                */
      /* 4. 8-bit run length followed by repeat char.                        */
      /*---------------------------------------------------------------------*/
      run_len = READ8_ADV(inbuf);
      if (run_len == 0)
      {
         run_len = ((unsigned int)(READ8_ADV(inbuf)))<<8;
         run_len += READ8_ADV(inbuf);

         /*------------------------------------------------------------------*/
         /* Exit if we reached the end of data. The sequence 'delim, 0, 0, 0'*/
         /* marks the end of data.                                           */
         /*------------------------------------------------------------------*/
         if (run_len == 0) break;

         /*------------------------------------------------------------------*/
	 /* At this point, if the run length is <= 255, then we have read    */
	 /* sequence: 'delim, 0, 0, msb of 24-bit length', so now we need to */
	 /* read in the remaining 2 bytes of the 24-bit run length field.    */
         /*------------------------------------------------------------------*/
	 if (is_rle24 && (run_len <= 0xff))
	 {
	    int i;
	    for (i = 1; i < 3; i++)
	       run_len = ((run_len << 8) | READ8_ADV(inbuf));
	 }

         ch = READ8_ADV(inbuf);
      }
      else if (run_len < 4)
         ch = delim;
      else
         ch = READ8_ADV(inbuf);

      outbuf = optimized_mem_set(outbuf, ch, run_len);
   }

   return;
}

/*****************************************************************************/
/*                                                                           */
/* OPTIMIZED_MEM_SET() - Optimized memset for C6x.                           */
/*                                                                           */
/*        Equivalent to (memset(mem, ch, n) + n)                             */
/*                                                                           */
/*****************************************************************************/
#pragma FUNC_ALWAYS_INLINE(optimized_mem_set)
static __inline void *optimized_mem_set(void *mem, int ch, size_t n)
{
   char  * restrict dst1, * restrict dst2;
   int    pre_bytes, post_bytes, wfill, i;

   unsigned char *outbuf = mem;
   unsigned int count = n;

   dst1 = (char *)outbuf;

#if defined(_TMS320C6400) || defined(_TMS320C6740) || defined(_TMS320C6600) || \
    defined(_TI_C6X_TESLA)

   /*---------------------------------------------------------------------*/
   /* We do not use 'dwfill' on other variations of the C6x architecture, */
   /* so limit 'dwfill' references to the architectures that use it.      */
   /*---------------------------------------------------------------------*/
   {
      long long dwfill;

      /*------------------------------------------------------------------*/
      /* Set up 64-bit and 32-bit fill values.                            */
      /*------------------------------------------------------------------*/
      wfill  = _pack2 (ch, ch);
      wfill  = _packl4(wfill, wfill);
      dwfill = _itoll (wfill, wfill); 

      /*------------------------------------------------------------------*/
      /* Calculate # of bytes to pre-copy to get to an alignment of 8     */
      /*------------------------------------------------------------------*/
      pre_bytes = (8 - (int) dst1) & 7;
       
      if (count > pre_bytes)
      {
         count -= pre_bytes;
         if (pre_bytes & 1) { *dst1        = ch;    dst1 += 1; }
         if (pre_bytes & 2) { _amem2(dst1) = wfill; dst1 += 2; }
         if (pre_bytes & 4) { _amem4(dst1) = wfill; dst1 += 4; }
      } 
            
      /*------------------------------------------------------------------*/
      /* Double word fills                                                */
      /*------------------------------------------------------------------*/
      post_bytes = count > 0 ? count : 0;
      dst2       = dst1 + 8;
       
      if (count > 15)
         for (i = 0; i < count >> 4; i++)
         {
            _amem8(dst1) = dwfill; dst1 += 16;
            _amem8(dst2) = dwfill; dst2 += 16;
            post_bytes -= 16;
         }
       
      /*------------------------------------------------------------------*/
      /* Finish transfer with 8, 4, 2 and/or 1-byte writes                */
      /*------------------------------------------------------------------*/
      if (post_bytes & 8) { _mem8(dst1) = dwfill; dst1 += 8; }
      if (post_bytes & 4) { _mem4(dst1) = wfill;  dst1 += 4; }
      if (post_bytes & 2) {  dst1[0]    = ch;  
      dst1[1]    = ch;     dst1 += 2; }
      if (post_bytes & 1) { *dst1       = ch;     dst1 += 1; }
   }

#else

   /*--------------------------------------------------------------------*/
   /* Set up 32-bit fill value.                                          */
   /*--------------------------------------------------------------------*/
   wfill  = _mpy(0x101, (int)ch);
   wfill += (wfill << 16);

   /*--------------------------------------------------------------------*/
   /* Calculate number of bytes to pre-copy to get to an alignment of 4  */
   /*--------------------------------------------------------------------*/
   pre_bytes = (4 - (int) dst1) & 3;

   if (count > pre_bytes)
   {
      count -= pre_bytes;
      if (pre_bytes & 1) { *dst1        = ch;    dst1 += 1; }
      if (pre_bytes & 2) { _amem2(dst1) = wfill; dst1 += 2; }
   }

   /*--------------------------------------------------------------------*/
   /* Double word fills                                                  */
   /*--------------------------------------------------------------------*/
   post_bytes = count > 0 ? count : 0;
   dst2       = dst1 + 4;

   if (count > 7)
      for (i = 0; i < count >> 3; i++)
      {
         _amem4(dst1) = wfill; dst1 += 8;
         _amem4(dst2) = wfill; dst2 += 8;
         post_bytes -= 8;
      }

   /*--------------------------------------------------------------------*/
   /* Finish transfer with up to 7 single-byte writes.                   */
   /*--------------------------------------------------------------------*/
   if (post_bytes) { *dst1++ = ch; post_bytes--; }
   if (post_bytes) { *dst1++ = ch; post_bytes--; }
   if (post_bytes) { *dst1++ = ch; post_bytes--; }
   if (post_bytes) { *dst1++ = ch; post_bytes--; }
   if (post_bytes) { *dst1++ = ch; post_bytes--; }
   if (post_bytes) { *dst1++ = ch; post_bytes--; }
   if (post_bytes) { *dst1++ = ch; post_bytes--; }

#endif

   return dst1;
}
