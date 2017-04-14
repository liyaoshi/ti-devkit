TI ARM C/C++ CODE GENERATION TOOLS
Release Notes
5.2.7
January 2016    

Features
===============================================================================
1.  Intrinsics
2.  Power advice
3.  NOINIT/PERSISENT pragmas
4.  GCC attributes
6.  MISRA-C compliant RTS header files

===============================================================================
1. Intrinsics
===============================================================================

The __delay_cycles intrinsic inserts code to consume precisely the number of 
specified cycles with no side effects.  The number of cycles delayed must be 
a compile-time constant.

NOTE: Cycle timing data is based on 0 wait states.  Results will vary with 
additional wait states. The implementation does not account for dynamic 
prediction.  Lower delay cycle counts may be less accurate given pipeline 
flush behaviors.

Added cmsis intrinsics:
  uint dst __get_PRIMASK (void)
                MRS dst,PRIMASK
  uint dst __set_PRIMASK (uint src)
                MRS dst,PRIMASK (optional)
                MSR PRIMASK,src
  uint dst __get_MSP (void)
                MRS dst,MSP
  void __set_MSP (uint src)
                MSR MSP,src

Updated Cortex-M0 implementation of below:
_enable_interrupts()/_disable_interrupts()/_restore_interrupts() 

For M0 we now have:
  _enable_interrupts()
                MRS dst,PRIMASK
                CPSIE i
  _disable_interrupts()
                MRS dst,PRIMASK
                CPSID i
  _restore_interrupts() 
                MSR PRIMASK

For M3/4 we have: 
  _enable_interrupts()
                MRS dst,FAULTMASK
                CPSIE f
  _disable_interrupts()
                MRS dst,FAULTMASK
                CPSID f
  _restore_interrupts() 
                MSR FAULTMASK

Extended _enable_IRQ()/_disable_IRQ() to Cortex-M
  _enable_IRQ
                MRS dst,PRIMASK
                CPSIE i
  _disable_IRQ
                MRS dst,PRIMASK
                CPSID i

===============================================================================
2. Power Advice
===============================================================================

The --advice:power option has been added to the ARM compiler. This enables
the ULP Advisor functionality for TI's ARM processors. The list of rules
are:

===============================================================================
3. NOININT and PERSISENT pragmas
===============================================================================

When using EABI, global and static variables will be zero-initialized. 
However, in applications using nonvolatile memory, it may be desirable to 
have variables that are not initialized. Noinit variables are global or
static variables that are not zero-initialized at startup or reset.
Persistent and noinit variables behave identically with the exception of 
whether or not they are initialized at load time. The NOINIT pragma may be 
used in conjunction with the LOCATION pragma to map variables to special
memory locations, like memory-mapped registers, without generating unwanted 
writes. The NOINIT pragma may only be used with uninitialized variables.
The PERSISTENT pragma is similar to the NOINIT pragma, except that it may 
only be used with statically-initialized variables. Persistent variables 
disable startup initialization; they are given an initial value when the code 
is loaded, but are never again initialized. If you are using non-volatile RAM, 
you can define a persistent variable with an initial value of zero loaded
into RAM. The program can increment that variable over time as a counter, 
and that count will not disappear if the device loses power and restarts, 
because the memory is non-volatile and the boot routines do not initialize it 
back to zero. For example:

#pragma PERSISTENT(x)
#pragma location = 0xC200 // memory address in RAM
int x = 0;
void main() {
   ...
   run_init();
   while (1) {
      run_actions(x);
   __delay_cycles(1000000);
   x++;
   }
}

===============================================================================
4. GCC attributes
===============================================================================

interrupt:

The compiler now supports the GCC style interrupt attribute. It functions
exactly like the existing INTERRUPT pragma and accepts the same arguments.

alias:

The compiler now supports the GCC alias attribute. The functionality is only
supported for functions. 
See https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html for details.


===============================================================================
5. MISRA Compliant RTS header files
===============================================================================

The header files that are allowed by MISRA-C:2004 have been modified so they
do not cause MISRA violations. In most cases the files were updated to 
be MISRA compliant, but some cases required disabling the diagnostics with
appropriate comments.

