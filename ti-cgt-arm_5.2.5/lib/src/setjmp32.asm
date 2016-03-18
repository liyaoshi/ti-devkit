;******************************************************************************
;* SETJMP - 32 BIT STATE -  v15.4.0I15142                                     *
;*                                                                            *
;* Copyright (c) 1996-2015 Texas Instruments Incorporated                     *
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

;****************************************************************************
;*   setjmp
;*
;*     C syntax  : int setjmp(jmp_buf env)
;*
;*     Function  : Save callers current environment for a subsequent
;*                 call to longjmp.  Return 0.
;*
;*     The context save area is organized as follows:
;*
;*       env -->  .long  V1
;*                .long  V2
;*                .long  V3
;*                .long  V4
;*                .long  V5
;*                .long  V6
;*                .long  V7
;*                .long  V8
;*                .long  SP
;*                .long  LR
;*
;****************************************************************************
;*
;*  NOTE : ANSI specifies that "setjmp.h" declare "setjmp" as a macro. 
;*
;*         In the TIABI implementation, the setjmp macro calls a function
;*         "_setjmp".  However, since the user may not include "setjmp.h",
;*         we provide two entry-points to this function.
;*
;*         In the EABI implementation, the setjmp macro calls a function
;*         "setjmp".  No alternate entry point is provided.
;*
;*         (Note: Due to the incorrect definition of the "setjmp" macro
;*         introduced in 4.4.x [CQ24877], object files generated by the TI
;*         compiler for modules which call setjmp in EABI mode refer to a
;*         symbol named "_setjmp".  For this reason, we must leave in the
;*         alternate entry point for EABI mode.  The alternate entry point
;*         should be removed in 5.x)
;*
;****************************************************************************

	.arm

	.if __TI_EABI_ASSEMBLER
	    .asg setjmp, __TI_SETJMP
	    .asg _setjmp, __TI__SETJMP
	.else
	    .clink
	    .asg _setjmp, __TI_SETJMP
	    .asg __setjmp, __TI__SETJMP
	.endif

	.if __TI_ARM9ABI_ASSEMBLER  | __TI_EABI_ASSEMBLER
	    .armfunc __TI_SETJMP, __TI__SETJMP
	.else
	    .global $setjmp
	    .global $_setjmp

	.thumb
$setjmp:
$_setjmp:
	BX PC
	NOP
	.arm
	.endif

	.global __TI_SETJMP, __TI__SETJMP
__TI_SETJMP: .asmfunc stack_usage(0)
__TI__SETJMP:
	STMIA	A1!, {V1 - V8, SP, LR}
	.if __TI_NEON_SUPPORT__
	VSTMIA  {D8 - D15}, A1!
	.elseif __TI_VFP_SUPPORT__
	FSTMIAD	A1!, {D8 - D15}
	.endif
	MOV     A1,#0
	BX	LR
	.endasmfunc


;****************************************************************************
;*   longjmp
;*
;*     C syntax  : void longjmp(jmp_buf env, int val)
;*
;*     Function  : Restore the context contained in the jump buffer.
;*                 This causes an apparent "2nd return" from the
;*                 setjmp invocation which built the "env" buffer.
;*                 This return appears to return "returnvalue".
;*                 NOTE: This function may not return 0.
;****************************************************************************

	.if __TI_EABI_ASSEMBLER
	    .asg longjmp, __TI_LONGJMP
	.else
	    .clink
	    .asg _longjmp, __TI_LONGJMP
	.endif

	.if __TI_ARM9ABI_ASSEMBLER  | __TI_EABI_ASSEMBLER
	    .armfunc __TI_LONGJMP
	.else
	    .global $longjmp
	    .thumb

$longjmp:
	BX 	PC
	NOP
	    .arm
	.endif

	.global __TI_LONGJMP
__TI_LONGJMP: .asmfunc stack_usage(0)
	LDMIA	A1!, {V1 - V8, SP, LR}
	.if __TI_NEON_SUPPORT__
	VLDMIA  {D8 - D15}, A1!
	.elseif __TI_VFP_SUPPORT__
	FLDMIAD	A1!, {D8 - D15}
	.endif
	CMP	A2, #0
	MOVEQ	A1, #1
	MOVNE	A1, A2
	BX	LR

	.endasmfunc

	.end
