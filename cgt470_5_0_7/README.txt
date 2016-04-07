TI ARM C/C++ CODE GENERATION TOOLS
Release Notes
5.0.7
October 2013     

Features
===============================================================================
1.  Performance improvements
2.  Compile time improvements
3.  Floating point enhancements
4.  GCC packed attribute without hardware support
5.  Cortex-M0
6.  Hex utility boot format
7.  Hex utility load image
8.  Thumb-2 interrupts
9.  Intrinsics
10. Pragma LOCATION
11. Compiler name change
12. Default options
13. Execute only code for Cortex devices
14. Workaround for Stellaris ARM cache silicon errata

===============================================================================
1. Performance improvements
===============================================================================

The --opt_for_cache option is intended to work with the -mf option to 
better optimize for instruction cache. The best performance for cache devices
has been observed at the -mf1 and -mf2 levels with the --opt_for_cache option.
The --opt_for_cache option performs the following changes:
 - Sets the --vectorize=off option to prevent code size growth. This can
   be overridden if the --vectorize=on option is set after --opt_for_cache
   on the command line.
 - Enables more aggressive instruction scheduling.
 - Limits inlining to only very small functions.

In addition to cache optimizations we also made the following improvements

- Better utilization of Cortex bitfield instructions (SBFX, UBFX, BFI, ...)
- Improved use of VFP multiple accumulate instructions
- Better instruction scheduling for both VFP and non-VFP instructions
- General code improvements in the presence of 16x16 multiplication
- Perofrmance improvements for --opt_level=4 in the presence of DATA_SECTION
  pragmas.

===============================================================================
2. Compile time improvements
===============================================================================
Several compile time improvements have been implemented in this release. 
Improvements were made in the following areas:

1. Applications consisting of large functions
2. Functions using 64-bit types (long long or double)
3. Compilation on Windows 7.

===============================================================================
3. Floating point improvements
===============================================================================

-------------------------------------------------------------------------------
--fp_mode=[strict | relaxed]
-------------------------------------------------------------------------------
The --fp_mode option has been revised. The changes include:

- The relaxed mode is no longer the default for EABI.
- Calls to sqrt, sqrtf, and sqrtl will be be converted directly to the VSQRT
  instruction. In this case errno will not be set for negative inputs.
- Calls to double precision routines declared in math.h will be converted
  to their single precision counterparts if all arguments are single precision
  and the result is used in a single precision context. The math.h header file
  must be included for this optimization to work.
- Division by a constant will be converted to inverse multiplication.
- Enhancements have been made to convert more expression types to single
  precision if the result is immediately used in a single precision context.


-------------------------------------------------------------------------------
--float_operations_allowed=[none | all | 32 | 64]
-------------------------------------------------------------------------------
This option allows the user to restrict the type of floating point operations
allowed in their application. The default is all. The option checks for 
operations that will be performed at runtime. So, for example, declared
variables that are not used will not cause a diagnostic. The checks are
performed after the relaxed mode optimizations have been performed, so
if the illegal operations are completely removed no diagnostics will be 
issued.

-------------------------------------------------------------------------------
Interlinking of VFP and non-VFP object files
-------------------------------------------------------------------------------
Compiling a file with VFP enabled changes the calling convention for functions
which take floating point arguments. This can make files compiled with and
without VFP support enabled incompatible. In the past the linker required
all object files to either have VFP enabled or disabled. Any mismatch would
result in a fatal error. 

The tools now support detecting files where the calling convention does not
change based on the VFP option and marking them as such. The linker can then
use this information to avoid spurious diagnostics. This allows creating
libraries that do not use floating point that can be linked into projects
which use VFP and which do not use VFP. Object files built with older tools
are all recognized as having VFP support affect the calling convention.

===============================================================================
4. GCC packed attribute without hardware support
===============================================================================

The GCC type attribute "packed" is now supported on structs and unions when
the --gcc language option is used for all ARM targets. This attribute minimizes 
the data requirement for structures by eliminating padding after unaligned 
members. This support was previously supported only for targets that had
hardware support for unaligned accesses (which can be enabled in the compiler
by using the --unaligned_access=on option). The 5.0 release now supports
the packed attribute when unaligned accesses are not supported by hardware.

For more information, see: 

    http://processors.wiki.ti.com/index.php/GCC_Extensions_in_TI_Compilers
    http://gcc.gnu.org/onlinedocs/gcc/Type-Attributes.html


===============================================================================
5. Cortex-M0
===============================================================================

This release adds support for the Cortex-M0 architecture. This target can be
enabled with the --silicon_version=6M0 option. More information on the 
architecture can be found at:

http://www.arm.com/products/processors/cortex-m/cortex-m0.php

===============================================================================
6. Hex utility boot format
===============================================================================

The hex utility now supports the GPIO8, GPIO16, SPI8, and I2C8 boot formats
for the C2000 Concerto cores.

===============================================================================
7. Hex utility load image enhancements
===============================================================================

The hex utility supports the --load_image option which creates what is called
a load image object file. A load image object file contains the loadable image
of an executable and represents it as data. More information can be found at:

http://processors.wiki.ti.com/index.php/Combining_executable_files

In previous releases, the compatibility of the executable files were checked
before combining them in the hex utility. The resulting file would contain
the combined attributes and would be used by the linker to enforce compatibility
if the file was relinked into another executable. 

This behavior has changed in the 5.0 release. The build attributes are no
longer considered when combining files in the hex utility. The resulting output
file does not contain build attributes. Only basic compatibility checks are
performed, which include object file format, machine type, and endianess.

The motivation of this change is to allow greater flexibility when combining
files. Since the files do not interact across ABI interfaces, it is the users
responsibility that any interactions are correct.

===============================================================================
8. Thumb-2 interrupts
===============================================================================

In the past, interrupts were only supported in ARM mode by the hardware. 
Using this information, if an interrupt function was compiled in Thumb mode,
the compiler would generate a veneer entrypoint in ARM mode that would 
change state to Thumb mode and call the function. The entrypoint routine would
be named with an underscore in EABI and without an underscore in TI_ARM9_ABI or
TIABI. The Thumb routine would be named according to the normal rules of the 
ABI. 

Newer devices are beginning to support interrupts in Thumb-2 mode. To support
these devices, the compiler will no longer generate a state change veneer for
interrupts in Thumb-2. It will compile the interrupts directly into Thumb-2
mode. Interrupts that are compiled in 16-bit Thumb mode are not supported and
the compile will issue an error if this case is detected.

If the old behavior is being used, the user will need to compile their 
interrupts in ARM mode if the target device does not support Thumb-2 interrupts.
If the interrupts still needs to be built in Thumb mode for code size reasons
the user will need to refactor their code manually.

#pragma CODE_STATE(my_interrupt, 32)
#pragma INTERRUPT(my_interrupt)
void my_interrupt()
{
   interrupt_body();
}

#pragma CODE_STATE(interrupt_body,16)
void interrupt_body()
{
  // interrupt code
}

===============================================================================
9. Intrinsics
===============================================================================

Support for the following intrinsics have been added:

   int                __clz(int)
   int                __rev(int)
   int                __rev16(int)
   int                __revsh(int)
   int                __rbit(int)
   unsigned int       __ldrexb(void*)
   unsigned int       __ldrexh(void*)
   unsigned int       __ldrex(void*)
   unsigned long long __ldrexd(void*)
   int                __strexb(unsigned char, void*)
   int                __strexh(unsigned short, void*)
   int                __strex(unsigned int, void*)
   int                __strexd(unsigned long long, void*)
   int                __ror(int, int)
 

These correspond directly to ARM instructions.

===============================================================================
10. Pragma LOCATION
===============================================================================

The compiler supports the ability to specify the runtime address of a variable
at the source level.  This can be accomplished with the new location pragma or
attribute.  Location support is only available in EABI.

Syntax:

    TI C style pragma:
    #pragma LOCATION(x, address)
    int x;

    TI C++ style pragma:
    #pragma LOCATION(address)
    int x;

    GCC attribute:
    int x __attribute__((location(address)));

===============================================================================
11. Compiler name change
===============================================================================

The TMS470 C/C++ Compiler is being renamed to the TI ARM C/C++ Compiler.
The motivation for this change is to highlight the fact that the compiler
is a general ARM compiler that supports all architectures used in TI 
microcontrollers. The summary of the changes are:

- The tool names have all be changed from the <tool>470 format to arm<tool>
  format. So for instance cl470 now becomes armcl.
- All predefined macros with TMS470 in the name have been duplicated with ARM. 
  For instance __TI_TMS470_V7__ has been duplicated with __TI_ARM_V7__. The 
  old macro names are still present and can continue to be used.
- The environment variable, TMS470_C_DIR has been duplicated to TI_ARM_C_DIR.
  If the TI_ARM_C_DIR variable is set it takes precedence over TMS470_C_DIR.
  If only TMS470_C_DIR is set it will continue to be used.

===============================================================================
12. Default option changes.
===============================================================================
There have been several option changes aimed at improving ease of use.

- EABI is now the default ABI. The older TI_ARM9_ABI can still be enabled by
  using the --abi=ti_arm9_abi option. The TIABI has been deprecated and it
  is recommended that users still using this ABI move to TI_ARM9_ABI.
- The DWARF version now defaults to 3 when EABI is used. The older DWARF
  version can be enabled by using the --symdebug:dwarf_version=2 option.
- The optimization options have been changed. If no debug option is used,
  the compiler will now default to --opt_level=3. Users can use --opt_level=off
  to revert to no optimization. If debugging is enabled the compiler will
  default to --opt_level=off. If optimization level of 2 or higher is used,
  the compiler will default to --optimize_with_debug=on. The user can
  use --optimize_with_debug=off to revert to the old behavior.

===============================================================================
13. Execute only code for Cortex devices
===============================================================================

The MPU on some Cortex devices can be configured to mark memory regions as
execute only. This means that no data reads can be performed on this region.
By default the compiler will use literal pools embedded in the code to load
literals. This violates the no data reads requirement. The compiler supports
the --embedded_constants=[on | off] option to disable embedding constants
in the code section. This option was introduced in version 4.9 of the compiler,
but only supported Cortex-M cores. The 5.0 release extends this support to all
v7 Cortex cores in both ARM and Thumb2 modes.

===============================================================================
14. Workaround for Stellaris ARM cache silicon errata
===============================================================================

Added a workaround for the silicon cache errata as described in the
document "Stellaris LM4FS1AH5BB Rev A1/A2". This workaround is enabled
through the --stellaris_cache_si_workaround compiler switch. For details
see the DefectHistory.txt file under ClearQuest issue SDSCM00045246.
