;******************************************************************************
;* remu  v7.4.13 (Tesla)                                                      *
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
; Generated assembly compiled from remu_c.c
;

        .sect	".text:__remu"
	.clink
	.global	__remu, __c6xabi_remu

;******************************************************************************
;* FUNCTION NAME: _remu                                                       *
;*                                                                            *
;*   Regs Used         : A0,A1,A2,A4,B0,B1,B3,B4,A3,A5                        *
;*   Regs Killed       : A0,A1,A2,A3,A4,A5,B0,B1,B4                           *
;******************************************************************************
__c6xabi_remu:
__remu: .asmfunc
;** --------------------------------------------------------------------------*

           CMPLTU  .L      A4,B4,B1
||         MV      .S      A4,B0
||         MV      .D      B4,A0

   [ B1]   B       .S      $C$L5
||         LMBD    .L      1,A0,B4
|| [!B1]   ZERO    .D      A4

           LMBD    .L      1,B0,A1
|| [ B1]   MVK     .S      1,B0

   [!B0]   BNOP            $C$L5,3
||         SUB     .L      B4,A1,A5

           ; BRANCHCC OCCURS {$C$L5}
;** --------------------------------------------------------------------------*

   [!B0]   MVK     .L      1,A0
|| [ B0]   SHL     .S      A0,A5,A3
|| [ B0]   MV      .D      B0,B4

   [!A0]   B       .S      $C$L5
|| [ B0]   MVK     .L      -1,A4

           ; BRANCHCC OCCURS {$C$L5}
;** --------------------------------------------------------------------------*

           MV      .S      A0,A2
||         CMPGTU  .L      A3,B4,A0
|| [ A1]   ADD     .D      1,A5,A5

   [ A1]   MVK     .L      1,A0

   [!A0]   SUB     .L      B4,A3,B4
|| [!A0]   SHRU    .S      A3,1,A3

   [ A1]   ZERO    .L      A0
           CMPGT   .L      A5,0,A1
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
;*      Loop source line                 : 41
;*      Loop opening brace source line   : 42
;*      Loop closing brace source line   : 42
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
           SHRU    .S      B4,A5,A4
;** --------------------------------------------------------------------------*
$C$L5:
           RETNOP          B3,5
           ; BRANCH OCCURS {B3}
           .endasmfunc
