;******************************************************************************
;* remi  v7.4.13 (Tesla)                                                      *
;*                                                                            *
;* Copyright (c) 2009-2015 Texas Instruments Incorporated                     *
;* http://www.ti.com/                                                         *
;*                                                                            *
;*  Redistribution and  use in source  and binary forms, with  or without     *
;*  modification,  are permitted provided  that the  following conditions     *
;*  are met:                                                                  *
;*                                                                            *
;*     Redistributions  of source  code must  retain the  above copyright     *
;*     notice, this list of conditions and the following disclaimer.          *
;*                                                                            *
;*     Redistributions in binary form  must reproduce the above copyright     *
;*     notice, this  list of conditions  and the following  disclaimer in     *
;*     the  documentation  and/or   other  materials  provided  with  the     *
;*     distribution.                                                          *
;*                                                                            *
;*     Neither the  name of Texas Instruments Incorporated  nor the names     *
;*     of its  contributors may  be used to  endorse or  promote products     *
;*     derived  from   this  software  without   specific  prior  written     *
;*     permission.                                                            *
;*                                                                            *
;*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS     *
;*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT     *
;*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR     *
;*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT     *
;*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
;*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT     *
;*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
;*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
;*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT     *
;*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
;*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
;*                                                                            *
;******************************************************************************
;
; Generated assembly based on the following algorithm:
;
; int _remi(int dividend, int divisor)
; {
;     int shift;
;     unsigned remainder;
;     unsigned u_dividend = dividend;
;     unsigned u_divisor  = divisor;
;
;     if (dividend < 0) u_dividend = -u_dividend;
;     if (divisor < 0)  u_divisor  = -u_divisor;
;
;    shift = _lmbd(1, u_divisor) - _lmbd(1, u_dividend);
;
;     if (u_dividend < u_divisor) remainder = u_dividend;
;     else if (u_dividend == 0)   remainder = 0;
;     else if (u_divisor == 0)    remainder = UINT_MAX;
;     else
;     {
;         int i;
;         unsigned num, den, num32;
;         unsigned first_div = 0;
;
;         num = u_dividend;
;         den = u_divisor << shift;
;
;         num32 = (_lmbd(1, u_dividend) == 0);
;
;         first_div = num32 << shift;
;
;         if (den > num) first_div >>= 1;
;
;         if (num32)
;         {
;             if(den > num) { den >>= 1; num -= den; }
;             else          { num -= den; den >>= 1; }
;         }
;         else shift++;
;
;         for (i = 0; i < shift; i++)
;             num = _subc(num, den);
;
;         remainder = num >> shift;
;     }
;
;     return ((dividend < 0) ? -remainder : remainder);
; }
;

        .sect	".text:__remi"
	.clink
	.global	__remi, __c6xabi_remi

;******************************************************************************
;* FUNCTION NAME: _remi                                                       *
;*                                                                            *
;*   Regs Used         : A0,A1,A2,A4,B0,B1,B3,B4,A3,A5,A6                     *
;*   Regs Killed       : A0,A1,A2,A3,A4,A5,A6,B0,B1,B4                        *
;******************************************************************************
__c6xabi_remi:
__remi: .asmfunc
;** --------------------------------------------------------------------------*

           MV      .S      B4,A0
||         CMPLT   .L      B4,0,A1
||         MV      .D      A4,B0

   [ A1]   NEG     .S      A0,A0
||         CMPLT   .L      A4,0,A1

   [ A1]   NEG     .S      A4,B0
||         LMBD    .L      1,A0,B4

           CMPLTU  .L      B0,A0,B1
||         MV      .S      B0,A6

   [ B1]   B       .S      $C$L5
||         LMBD    .L      1,B0,A1
|| [ B1]   MVK     .D      1,B0

   [!B0]   BNOP            $C$L5,4
|| [!B1]   ZERO    .L      A6
||         SUB     .D      B4,A1,A5

           ; BRANCHCC OCCURS {$C$L5}
;** --------------------------------------------------------------------------*
           NOP             1
           ; BRANCHCC OCCURS {$C$L5}
;** --------------------------------------------------------------------------*

   [!A0]   B       .S      $C$L5
||         MV      .L      B0,B4
||         MV      .D      A0,A2

           SHL     .S      A0,A5,A3
|| [ A1]   ADD     .L      1,A5,A5
||         MVK     .D      -1,A6

           CMPGTU  .L      A3,B4,A0
   [ A1]   MVK     .L      1,A0

   [!A0]   SHRU    .S      A3,1,A3
|| [!A0]   SUB     .L      B4,A3,B4
|| [ A1]   ZERO    .D      A0

   [ A2]   CMPGT   .L      A5,0,A1
           ; BRANCHCC OCCURS {$C$L5}
;** --------------------------------------------------------------------------*
   [!A1]   BNOP            $C$L4,2
   [ A0]   SHRU    .S      A3,1,A3
   [ A0]   SUB     .L      B4,A3,B4
   [ A1]   SUB     .L      A5,1,A0
           ; BRANCHCC OCCURS {$C$L4}
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop source line                 : 49
;*      Loop opening brace source line   : 50
;*      Loop closing brace source line   : 50
;*      Known Minimum Trip Count         : 1
;*      Known Max Trip Count Factor      : 1
;*      Loop Carried Dependency Bound(^) : 0
;*      Unpartitioned Resource Bound     : 1
;*      Partitioned Resource Bound(*)    : 1
;*      Searching for software pipeline schedule at ...
;*         ii = 1  Schedule found with 6 iterations in parallel
;*      Done
;*
;*      Collapsed epilog stages       : 5
;*      Collapsed prolog stages       : 0
;*      Minimum required memory pad   : 0 bytes
;*
;*      Minimum safe trip count       : 1
;*----------------------------------------------------------------------------*
$C$L1:    ; PIPED LOOP PROLOG
   [ A0]   BDEC    .S      $C$L2,A0
   [ A0]   BDEC    .S      $C$L2,A0
   [ A0]   BDEC    .S      $C$L2,A0
   [ A0]   BDEC    .S      $C$L2,A0
   [ A0]   BDEC    .S      $C$L2,A0
;** --------------------------------------------------------------------------*
$C$L2:    ; PIPED LOOP KERNEL

           SUBC    .L      B4,A3,B4
|| [ A0]   BDEC    .S      $C$L2,A0

;** --------------------------------------------------------------------------*
$C$L3:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
$C$L4:
           SHRU    .S      B4,A5,A6
;** --------------------------------------------------------------------------*
$C$L5:
           RETNOP          B3,3

           CMPLT   .L      A4,0,A0
||         NEG     .S      A6,A4

   [!A0]   MV      .L      A6,A4
           ; BRANCH OCCURS {B3}
           .endasmfunc
