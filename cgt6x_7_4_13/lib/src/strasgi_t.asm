;******************************************************************************
;* strasgi  v7.4.13 (Tesla)                                                   *
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
; Generated assembly compiled from strasgi_c.c
;

        .sect	".text:__strasgi"
	.clink
	.global	__strasgi, __c6xabi_strasgi

;******************************************************************************
;* FUNCTION NAME: _strasgi                                                    *
;*                                                                            *
;*   Regs Used       : A0,A1,A4,A6,A2,B3,B4,A3,A5,A7,A8                       *
;*   Regs Killed     : A0,A1,A2,A3,A5,A7,A8,B4                                *
;******************************************************************************
__c6xabi_strasgi:
__strasgi: .asmfunc
;** --------------------------------------------------------------------------*

           MV      .L      B4,A3
||         SUB     .D      A4,B4,B4
||         MVK     .S      132,A5

           CMPLT   .L      B4,A5,A8
||         SUB     .D      A3,A4,B4
||         SHRU    .S      A6,2,A0

           CMPLT   .L      B4,A5,A7
||         SHRU    .S      A6,2,A5
||         MV      .D      A4,B4

           AND     .L      A8,A7,A2

   [!A2]   BNOP            $C$L4,5
|| [!A2]   CMPGT   .L      A0,1,A2

           ; BRANCHCC OCCURS {$C$L4}
;** --------------------------------------------------------------------------*

           SUB     .L      A5,1,A0
||         DINT

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop source line                 : 19
;*      Loop opening brace source line   : 20
;*      Loop closing brace source line   : 20
;*      Known Minimum Trip Count         : 1
;*      Known Max Trip Count Factor      : 1
;*      Loop Carried Dependency Bound(^) : 6
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 2
;*      Searching for software pipeline schedule at ...
;*         ii = 6  Schedule found with 1 iterations in parallel
;*      Done
;*
;*      Collapsed epilog stages       : 0
;*      Collapsed prolog stages       : 0
;*
;*      Minimum safe trip count       : 1
;*----------------------------------------------------------------------------*
$C$L1:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L2:    ; PIPED LOOP KERNEL

   [ A0]   BDEC    .S      $C$L2,A0
||         LDW     .D      *A3++(4),A5

           NOP             4
           STW     .D      A5,*B4++(4)
;** --------------------------------------------------------------------------*
$C$L3:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
           BNOP            $C$L9,4
           RINT
           ; BRANCH OCCURS {$C$L9}
;** --------------------------------------------------------------------------*
$C$L4:

   [ A2]   BNOP            $C$L6,5
|| [!A2]   LDW     .D      *A3++(4),A5
|| [ A2]   SUB     .L      A0,2,A0

           ; BRANCHCC OCCURS {$C$L6} {0}
;** --------------------------------------------------------------------------*
;**   BEGIN LOOP $C$L5
;** --------------------------------------------------------------------------*
$C$L5:

           SUB     .L      A0,1,A0
||         STW     .D      A5,*B4++(4)

   [ A0]   B       .S      $C$L5
|| [ A0]   LDW     .D      *A3++(4),A5

   [!A0]   BNOP            $C$L10,4
           ; BRANCHCC OCCURS {$C$L5}
;** --------------------------------------------------------------------------*
           RET     .S      B3
           ; BRANCH OCCURS {$C$L10}
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop source line                 : 19
;*      Loop opening brace source line   : 20
;*      Loop closing brace source line   : 20
;*      Known Minimum Trip Count         : 1
;*      Known Max Trip Count Factor      : 1
;*      Loop Carried Dependency Bound(^) : 0
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 2
;*      Searching for software pipeline schedule at ...
;*         ii = 2  Schedule found with 3 iterations in parallel
;*      Done
;*
;*      Epilog not removed
;*      Collapsed epilog stages       : 0
;*
;*      Prolog not entirely removed
;*      Collapsed prolog stages       : 1
;*
;*      Minimum required memory pad   : 0 bytes
;*
;*      For further improvement on this loop, try option -mh8
;*
;*      Minimum safe trip count       : 2
;*----------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP PROLOG
   [ A0]   BDEC    .S      $C$L7,A0
           NOP             1

           LDW     .D      *A3++(4),A5
|| [ A0]   BDEC    .S      $C$L7,A0

           MVK     .L      1,A1
;** --------------------------------------------------------------------------*
$C$L7:    ; PIPED LOOP KERNEL

   [ A0]   BDEC    .S      $C$L7,A0
||         LDW     .D      *A3++(4),A5

   [ A1]   SUB     .L      A1,1,A1
|| [!A1]   STW     .D      A5,*B4++(4)

;** --------------------------------------------------------------------------*
$C$L8:    ; PIPED LOOP EPILOG
           NOP             1
           STW     .D      A5,*B4++(4)
;** --------------------------------------------------------------------------*
           NOP             1
           STW     .D      A5,*B4++(4)
;** --------------------------------------------------------------------------*
$C$L9:
           RET     .S      B3
;** --------------------------------------------------------------------------*
$C$L10:
           NOP             5
           ; BRANCH OCCURS {B3}
           .endasmfunc
