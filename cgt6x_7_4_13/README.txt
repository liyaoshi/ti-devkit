TMS320C6000 C/C++ CODE GENERATION TOOLS
7.4.13 Release Notes
February 2015 


===============================================================================
Contents
===============================================================================
1) Support Information
2) OpenMP Support
3) Thread-Safe RTS
4) Thread-Local Storage
5) Errno Interface Changes
6) Performance Advice
7) Auto Load Speculation Support
8) Pack Pragma Support
9) Typeinfo in subsections
10) Support for <complex.h> 

-------------------------------------------------------------------------------
1) Support Information
-------------------------------------------------------------------------------

1.1) Defect History
-------------------

The list of defects fixed in this release as well as known issues can
be found in the file DefectHistory.txt.

1.2) Compiler Wiki
------------------

A Wiki has been established to assist developers in using TI Embedded
Processor Software and Tools.  Developers are encouraged to read and
contribute to the articles.  Registered users can update missing or
incorrect information.  There is a large section of compiler-related
material.  Please visit:

http://tiexpressdsp.com/wiki/index.php?title=Category:CGT

1.3) Compiler Documentation Errata
----------------------------------

Errata for the "TMS320C6000 Optimizing Compiler User's Guide" and the
"TMS320C6000 Assembly Language User's Guide" is available online at the
Texas Instruments Embedded Processors CG Wiki:

http://tiexpressdsp.com/wiki/index.php?title=Category:CGT

under the 'Compiler Documentation Errata' link.

1.4) TI E2E Community
---------------------

Questions concerning TI Code Generation Tools can be posted to the TI E2E
Community forums.  The "Development Tools" forum can be found at:

http://e2e.ti.com/support/development_tools/f/default.aspx

1.5) Defect Tracking Database
-----------------------------

Compiler defect reports can be tracked at the Development Tools bug
database, SDOWP. The log in page for SDOWP, as well as a link to create
an account with the defect tracking database is found at:

https://cqweb.ext.ti.com/pages/SDO-Web.html

A my.ti.com account is required to access this page.  To find an issue
in SDOWP, enter your bug id in the "Find Record ID" box once logged in.
To find tables of all compiler issues click the queries under the folder:

"Public Queries" -> "Development Tools" -> "TI C-C++ Compiler"

With your SDOWP account you can save your own queries in your
"Personal Queries" folder.


-------------------------------------------------------------------------------
2) OpenMP Support
-------------------------------------------------------------------------------

This version of the C6000 compiler tools supports OpenMP v3.0 API in C 
applications by using the --openmp or --omp command-line option from the
compiler command-line. 

Please note that use of the OpenMP API in C++ applications is not fully 
supported at this time.

OpenMP applications depend on support from the underlying runtime operating
system (RTOS) for proper initialization of global data objects and for thread
creation and initialization of thread-local data objects. 

The OpenMP threadprivate implementation is built on Thread-Local Storage (TLS)
support (README.txt, Section 4). The current TLS specification limits the size 
of the total static storage to 32Kbytes. Subsequently, OpenMP programs can 
support a total of 32Kbytes of threadprivate data.

The Texas Instruments' MultiCore Software Development Kit (MCSDK) is a
platform which includes the runtime operating system support needed for
OpenMP applications that are built with the C6000 v7.4 Code Generation
Tools. For detailed information on Texas Instruments' MCSDK for C66x, 
C647x, and C645x processors, please visit:

  http://www.ti.com/tool/bioslinuxmcsdk

For further information on Texas Instruments' multicore DSPs, software, and
low-cost EVMs, please visit:

  http://www.ti.com/c66multicore


-------------------------------------------------------------------------------
3) Thread-Safe RTS
-------------------------------------------------------------------------------

To help ensure thread-safety of an OpenMP application, a thread-safe version
of the Run Time Support (RTS) library should also be used during the link
step. The 7.4.0 Code Generation Tools package provides thread-safe RTS
libraries for this purpose. 

Thread-safe versions of the RTS library will make use of critical sections
to ensure that RTS-owned shared data objects are only ever accessed by one
thread at a given time. In a multi-threaded application, the RTS library
relies on the underlying runtime operating system (RTOS) to register mutex
services during the boot sequence. These mutex services are accessed via
indirect calls from the RTS to create the needed critical sections.

To help with registration of these mutex services, the RTS provides an
externally callable function (see _reg_mutex_api.h in rtssrc.zip):

  void _register_mutex_api(void *(*create)   (void),
                           void  (*destroy)  (void *handle),
			   void  (*lock)     (void *handle),
			   void  (*unlock)   (void *handle),
			   int   (*thread_id)(void));

  where:

    create    - is the address of an RTOS function that creates a mutex and
                returns a pointer to (or handle of) the newly created mutex

    destroy   - is the address of an RTOS function that, given a mutex
                handle, will destroy the mutex (handle is not valid
	        after the mutex that it points to is destroyed)

    lock      - is the address of an RTOS function that, given a mutex 
                handle, will block until a lock on that mutex is acquired

    unlock    - is the address of an RTOS function that, given a mutex
                handle, will release a lock on the mutex

    thread_id - is the address of an RTOS function that returns a 
                unique integer identification for the currently 
		executing thread

Another aspect of multi-threaded applications that is taken into account
by the RTS library is data coherence. In a multi-core platform like C66x,
the RTS must ensure that the value of a shared data object remains 
consistent among all of the copies of that data that may exist in the 
system (L1D caches and global shared memory). Thread-safe versions of the
RTS library will make use of RTOS-provided cache coherence functions
that can perform write-back and invalidate operations on the local cache
of the core that is executing the current thread in a multi-threaded 
application. These cache coherence functions are accessed via indirect
calls from the RTS to perform the necessary cache operation.

To help with registration of these cache coherence services, the RTS
provides an externally callable function (see _reg_synch_api.h in
rtssrc.zip):

  void _register_data_synch_api(void (*Inv)  (void *ptr, size_t sz),
                                void (*Wb)   (void *ptr, size_t sz),
				void (*WBInv)(void *ptr, size_t sz));

  where:

    Inv   - is the address of an RTOS function that invalidates the 
            local cache line(s) which contain(s) the data indicated by
	    the target address (ptr) and size (sz) arguments.

    Wb    - is the address of an RTOS function that writes back to 
            shared memory the local cache line(s) which contain(s) the
	    data indicated by the target address (ptr) and size (sz) 
	    arguments.

    WbInv - is the address of an RTOS function that writes back to
            shared memory and then invalidates the local cache line(s)
	    which contain(s) the data indicated by the target address 
	    (ptr) and size (sz) arguments.

Please note that on C6x multi-core platforms, it is possible to encounter
a race condition when writing a new value to a shared data object in 
global memory. This can occur if a write of a shared data object on one 
thread does not land in shared memory before another thread acquires access
to the same object. The RTS avoids this situation on C66x multi-core 
platforms by calling the _mfence() intrinsic before leaving the critical
section that protects access to the shared data. The RTS library does not
take preventive action for this situation in the case of C64x multi-core 
platforms (which do not support an _mfence() intrinsic). If this race
condition occurs on a C64x multi-core platform, you may need to customize
the Wb and WbInv functions that are registered with the RTS to account
for this race condition.

To link with a thread-safe RTS library, the appropriate thread-safe RTS 
library (chosen from the list of available thread-safe RTS libraries 
enumerated below) can be explicitly specified on the link command line,
or a libc.a libinfo file can be specified in place of the RTS library in
the link command in which case the linker will automatically select
the thread-safe RTS library that matches the other runtime model criteria 
needed in the OpenMP application.

This includes one of the following thread-safe C6000 EABI libraries:

rts64plus_elf_mt.lib     -- little-endian C64+
rts64pluse_elf_mt.lib    -- big-endian C64+
rts64plus_elf_mt_eh.lib  -- little-endian C64+ with support for exceptions
rts64pluse_elf_mt_eh.lib -- big-endian C64+ with support for exceptions

rts6600_elf_mt.lib       -- little-endian C66x
rts6600e_elf_mt.lib      -- big-endian C66x
rts6600_elf_mt_eh.lib    -- little-endian C66x with support for exceptions
rts6600e_elf_mt_eh.lib   -- big-endian C66x with support for exceptions

rts6740_elf_mt.lib       -- little-endian C6740
rts6740e_elf_mt.lib      -- big-endian C6740
rts6740_elf_mt_eh.lib    -- little-endian C6740 with support for exceptions
rts6740e_elf_mt_eh.lib   -- big-endian C6740 with support for exceptions

Please note that only rts6600_elf_mt.lib and rts6600e_elf_mt.lib are pre-built
as part of the 7.4.0 product distribution. When specified in the link step of
a multi-threaded application build, if the library cannot be found, the RTS
library builder will build it at link time.

If you have need for another configuration of the thread-safe RTS, please
report this as a defect (see section 1 for Defect Reporting).

-------------------------------------------------------------------------------
4) Thread-Local Storage
-------------------------------------------------------------------------------

Given the increase in the number of C6000 CPU based multi-core devices,
multi-threaded programming is expected to be more widely adopted
to leverage the multiple cores. Also, multi-core programming models like
OpenMP and OpenCL normally rely on underlying multi-threading support.
These complex multi-threading programs can be better structured and
easier to develop if the threads can use variables that have static
storage duration which is specific to the thread. That is, other threads
cannot see or access this thread's specific variable with static storage
duration. 

Consider the following C code:

    int global_x;
    foo() 
    {
       int local_x;
       static int static_x = 0;
       ...
    }

global_x and static_x are allocated once per process and all threads
share the same instance. Whereas local_x is allocated in stack and each
thread gets its own stack and hence the auto variable local_x is thread
specific. There is no easy way to define a per thread global/static
variable. The POSIX thread interface allows creating thread specific static
storage variables using pthread getspecific and pthread setspecific, but
this interface is cumbersome to use and inefficient.

To solve this, Thread Local Storage (TLS) has been defined as a class of
storage that allows defining thread specific variables with static storage
durations. A TLS variable or thread-local variable is a global/static
variable that is instanced once per thread. It is allocated such that there 
is one instance of this variable per thread. 

The C6x v7.4.0 compiler supports thread-local variables in EABI mode. 
The user can use the new storage class keyword, __thread, to designate a
variable thread-local. For example,

    __thread int var_i;
    extern __thread long var_l;
    static __thread int *p;

    int foo()
    {
       static __thread struct st1 var_st1;
       ...
    }

The __thread keyword can be applied to the definition/declaration of global 
and static variables. It can be applied to the static data member of a class.
It cannot be applied to local variables and non-static data members.

A thread-local variable can be initialized or uninitialized. If initialized,
the initializer must be a constant-expression. 

When the address-of operator is applied to a thread-local variable the address
of the current thread's instance is returned. This address can be used by
other threads. However, when the thread terminates, any pointer to its thread-
local variables are invalid. The address of a thread-local variable cannot be 
used as an initializer. 

The initialized and uninitialized thread-local variables are by default 
allocated to the ".tdata" and ".tbss" output sections respectively. 

Please note that the Thread-Local Storage feature requires significant support
from the underlying runtime system, specifically the thread library. The 
thread library is responsible for creating threads and it must allocate space
for thread-local variables and initialize them properly. 

The current TLS specification limits the size of the total static storage to 
32Kbytes. 

If you are using an underlying runtime operating system other than that 
provided by the MCSDK (version 2.1 or later), please verify if the 
thread-library you are using supports a Thread-Local storage run-time system
as specified in the Thread-Local Storage Specification for C6000 EABI (see 
C6000_TLS.docx in the doc subdirectory where the 7.4.0 tools were installed).


-------------------------------------------------------------------------------
5) Errno Interface Changes
-------------------------------------------------------------------------------

A thread-safe version of the RTS library requires that its implementation
of errno be in thread-local storage (TLS). That is, in a multi-threaded 
application that uses a thread-safe RTS library, each thread will be given 
its own copy of errno. In a single-threaded application, errno is implemented
as a scalar type global variable since only one copy is needed.

To accommodate both of these use scenarios under the EABI model, the interface
to errno has been updated in the C6000 v7.4.0 CGT. Any references to errno 
will be converted into a function call as specified in the following errno.h
directives:

   #ifdef __cplusplus
    #define errno (*::std::__c6xabi_errno_addr())
   #else
    #define errno (*__c6xabi_errno_addr())
   #endif

where '__c6xabi_errno_addr()' is a new C6000 EABI function which returns the
address of the RTS library's internal representation of the errno data object.

While this change to the errno interface hides the RTS library's internal
implementation of errno from the reference site, it does introduce a slight
problem for old EABI object files that have been compiled with an older
C6000 EABI compliant compiler (v7.0.x -> 7.3.x). Specifically, an older
EABI object file may contain a direct reference to the errno global object.
To alleviate this problem, the v7.4.0 RTS libraries will map the 'errno'
global symbol to the RTS library's internal definition of errno (__errno
in the errno.c source file of the RTS).

Here are a few useful rules of thumb to keep in mind if you have to use
errno or other global state variables that may get TLS in a user developed
library:

    i) If use of errno can be avoided, it should be.
   ii) If errno is used in an application, the application source code
       should include the RTS library's errno.h instead of declaring
       errno explicitly.
  iii) If developing a single-threaded application, do not link with a 
       thread-safe version of the RTS library (rts6600_elf_mt.lib, for
       example - see section 3 above for a complete list of thread-safe
       RTS libraries).
   iv) User developed libraries should try to avoid the use of global
       state variables that require TLS.
    v) If a user developed library must use a global state variable that
       requires TLS, then access to it should be via a function call 
       (similar to the access to errno via the __c6xabi_errno_addr() 
       function as described above).

If a non-TLS symbol reference is made to a global state variable in a library
that is defined with TLS, then the linker will emit a symbol mismatch error.


-------------------------------------------------------------------------------
6) Performance Advice
-------------------------------------------------------------------------------

The C6000 optimizing compiler can generate highly optimized DSP code from the
C source code. The compiler, in some cases, can do better optimization if the
user aids the compiler by providing additional information in the code. The 
compiler now emits Performance Advice which can help programmers improve the
performance of their compiled code.

To get Performance Advice from the compiler, invoke it with the 
"--advice:performance" option: 
 
     cl6x [--advice:performance] [filenames] [-z [link_options] object files]]

The compiler will write "Advice" for "filename.c" to stdout by default. 
To generate advice to a specific file or to a specific file in a specific
directory, use "--advice:performance_file" and "--advice:performance_dir" :

To emit Advice to 

  - stdout:

     cl6x --advice:performance [filenames] . . .

  - Custom files (advice output to f1.advice and f2.advice) :

     cl6x --advice:performance --advice:performance_file  f1.c f2.c . . .

  - A custom "common" advice file (all advice output to "myfile") :

     cl6x --advice:performance --advice:performance_file=myfile 
                                                              [filenames] . . .
  - A custom file in a custom directory :

     cl6x --advice:performance --advice:performance_file=myfile
                               --advice:performance_dir=mydir [filenames] . . .
   
                       OR
                
     cl6x --advice:performance --advice:performance_file=mydir/myfile 
                                                              [filenames] . . .



If an advice file is requested but there is no advice, the advice file will
not be created; rather the compiler will print a message to stdout:

     advice #27004: No Performance Advice is generated

Performance Advice can be explicitly turned off by using the 
 "--advice:performance=none" option.

Performance Advice alerts you to 3 different types of situations : 

- Advice to use correct compiler options 
  - Advice #27000: Use Optimization Options 
  - Advice #27001: Increase Optimization Level 
  - Advice #27002: Do not turn off software pipelining 
  - Advice #27003: Avoid compiling with debug options 
  - Advice #27004: No Performance Advice generated 
 
- Advice to prevent software pipelining disqualification 
  - Advice #30000: Prevent Loop Disqualification due to call 
  - Advice #30001: Prevent Loop Disqualification due to rts-call 
  - Advice #30002: Prevent Loop Disqualification due to asm statement 
  - Advice #30003: Prevent Loop Disqualification due to complex condition 
  - Advice #30004: Prevent Loop Disqualification due to switch statement 
  - Advice #30005: Prevent Loop Disqualification due to arithmetic operation 
  - Advice #30006: Prevent Loop Disqualification due to call(2) 
  - Advice #30007: Prevent Loop Disqualification due to rts-call(2) 

- Advice to improve loop performance 
  - Advice #30008: Improve Loop; Qualify with restrict 
  - Advice #30009: Improve Loop; Add MUST_ITERATE pragma 
  - Advice #30010: Improve Loop; Add MUST_ITERATE pragma(2) 
  - Advice #30011: Improve Loop; Add _nasssert() 

You can find details on Performance Advice at the following URL:

http://processors.wiki.ti.com/index.php/Compiler/diagnostic_messages/C6000


-------------------------------------------------------------------------------
7) Auto Load Speculation Support (-mh=auto or --speculate_loads=auto option)
-------------------------------------------------------------------------------

The C6000 optimizing compiler can use load speculation (also referred to as
speculative execution) in combination with software pipelining to improve 
performance and reduce code size. 

7.1) Background Information about Software Pipelining and Load Speculation

  Background information on the existing software pipelining and speculative
  execution features/capabilities in the compiler can be found in section 3.2
  of the TMS320C6000 Optimizing Compiler User's Guide (spru187u.pdf):

  * For more details on Software Pipelining, see section 3.2
  * For more details on Speulative Execution and using the existing
    -mh=n option, see section 3.2.3.1

  The latest C6000 Optimizing Compiler User's Guide can be downloaded from
  the following location:

  http://www.ti.com/tool/ccstudio#Technical_Documents

  Additional information about software pipelining is available at the
  following wiki page:

  http://processors.wiki.ti.com/index.php/C6000_Compiler:_Tuning_Software_Pipelined_Loops

  Additional information about speculative execution and software pipelining
  is also available in the application report, "Hand-Tuning Loops and Control
  Code on the TMS320C6000" (spra666.pdf - August 2006). There is a link to 
  this document in the above wiki page.

7.2) Benefits of Combining Load Speculation with Software Pipelining

  As discussed in the documents and wiki article referenced above, the 
  compiler's ability to combine load speculation with software pipelining 
  can improve performance and reduce code size. 

  * Collapsing Software Pipelined (SP) Loop Prologs and Epilogs
  
    If the user asserts via the -mh option that it is safe 
    to access memory beyond the bounds of a data object that is being used
    by an SP loop, then the compiler will likely be able to add iterations 
    to the SP loop which in turn can enable the compiler to collapse the 
    SP loop's prolog and epilog code into the SP loop. This has the 
    immediate benefit of reducing the code size by eliminating or reducing 
    the number of instructions in the prolog and epilog.

    The minimum number of iterations that a loop must execute in order
    to be safely software pipelined is called its safe trip count.
    In cases where the compiler is not able to determine whether the 
    minimum known number of iterations through the loop (also referred
    to as the loop's known trip count) is greater than or equal to the
    loop's safe trip count, the compiler will sometimes generate two
    different versions of the loop; one will be software pipelined and
    the other may not be. When the compiler adds iterations to the SP loop
    in order to enable collapsing of the prolog and epilog, this may 
    increase the minimum known trip count (as described earlier) up to the
    loop's safe trip count allowing the compiler to discard the redundant,
    non-software pipelined loop. This will result in additional code size
    savings.

  * Enabling Software Pipelining of Irregular Loops

    An example of an irregular loop is one which has an early exit point.
    Consider, for instance, a loop that executes a string copy; it
    contains a load from memory, followed by a conditional exit, followed
    by a store to memory. If no load speculation is allowed, then the 
    load from iteration 'i' of the loop must occur (in time) after the 
    store from iteration 'i-1', and so the loop cannot be pipelined. 
    
    However, if the user asserts (via the -mh option) that it is safe to 
    read past the bounds of the object being read, then the compiler can 
    pipeline the loads from successive iterations. Thus, load speculation 
    provides performance improvement in such cases.

  * Reducing Pressure on Predicate Registers
  
    In the absence of speculated loads, the compiler may still be able to
    software pipeline an irregular loop by predicating the loads in the SP
    kernel that are associated with successive iterations of the loop.
    For example, if a condition on an early exit from the loop is computed
    into a predicate register, then that predicate register can be applied
    to a predicate on a load instruction that is scheduled earlier in an
    SP loop in relation to the loop exit. Increasing the number of uses
    of a predicate register increases the demand for registers of that type
    (a phenomenon which is also referred to as register pressure).

    If the user asserts that load speculation is permitted, then the compiler
    can avoid having to predicate a load that occurs early in an SP loop.
    This will in turn reduce the predicate register pressure and may create
    more opportunities for the compiler to generate better code in the SP
    loop.

7.3) An Example Use Case for the -mh Option

  Load speculation involves accessing memory locations which are beyond 
  those specified in the program. Attempts to access memory that has not
  been allocated can result in an illegal memory access. In order to utilize
  load speculation, the compiler must ensure that such memory accesses are
  safe in the context of the loop that it is trying to software pipeline.
  Unfortunately, it is not possible for the compiler to prove the safety
  of a speculative load in many cases.

  The -mh (or --speculate_loads) option supported in the C6000 optimizing
  compiler provides a means by which application developers can inform the 
  compiler about the safety of using speculative loads. The argument to
  the -mh option is the number of bytes that are safe to access beyond the 
  memory that the compiler can prove is allocated. Thus, the compiler is 
  able to use information provided by the application developer to better
  optimize the program.

  Consider the following loop:

  unsigned char  a[128];
  unsigned char  b[128];
  unsigned char loop1(unsigned char start, unsigned char end)
  {
    unsigned char i, flag = 1;
    for (i = start; i < end; i++)
    {
      if (a[i] == 3 || b[i] == 2)
      {
        flag = 0;
        break;
      }
    }
    return flag;
  }

  When this loop is compiled without the -mh option:

    cl6x --abi=eabi -mv64+ -o -mw -s loop_ex.c

  the SP loop generated has an iteration interval (ii) of 10. However,
  if we add a -mh=14 option as suggested in the assembly output (-mw 
  option provides information that may help the compiler to generate 
  a better SP loop), 
  
    ; *  For further improvement on this loop, try option -mh14

  and recompile:

    cl6x --abi=eabi -mv64+ -o -mh=14 -mw -s loop_ex.c

  the ii is reduced to 3. Reducing the ii of the SP loop can have a 
  significant impact on performance. The estimated total cycles for 
  the above loop using the v7.4 compiler is:
  
    ii = 10 (no -mh used)	20 to 1290 cycles
    ii = 3  (-mh=14 used)	18 to 399  cycles
  
  The actual performance will depend on the actual trip count (number 
  of times the SP loop kernel is executed).
  
  This is an example of the kind of improvements that the compiler can
  get by using the -mh option in combination with software pipelining
  an irregular loop.  However, to safely use the -mh option, the
  application developer must ensure that any speculative load generated
  by the compiler will access legal memory. This can be done in two 
  ways:

  1. Add extra padding before and after the buffer that is operated on
     by the loop. This requires that the application knows what buffer
     is being operated on and where it is allocated.

  2. Add extra padding before and after the memory range in which the 
     buffer that is operated on by the loop is allocated. For example,
     the application developer would need to add pre-padding and post-
     padding as follows:
     
     MEMORY {
        /* pre-PADDING required for -mh14 option ... */
	prepad_myregion:  origin = 0x1000, length = 16

        myregion:         origin = 0x1010, length = 0x3FD0

        /* post-PADDING required for -mh14 option ... */
	postpad_myregion: origin = 0x4FE0, length = 16
     }
     
7.4) Automatic Load Speculation Option (-mh=auto or --speculate_loads=auto)

  The v7.4.0 compiler adds support for a new argument, -mh=auto, to make
  it easier to use and benefit from speculative load optimization. This
  option generates speculative loads of up to 256 bytes beyond memory that
  the compiler can prove to be allocated. 
  
  In addition, the compiler communicates information to the linker to help
  automatically ensure the required pre- and/or post-padding: 

  * If the symbol of the speculatively loaded buffer is known during compile
    time, the linker will ensure the object pointed to by the symbol has 
    the required padding to let the speculative load access legal memory.

  * If the symbol information is not known during compile time, the linker 
    will ensure that the placement of data sections will allow legal 
    accessing beyond the boundaries of the data sections. The linker does
    this by simply padding the start and end of the memory range(s) where
    the data sections are placed.

-------------------------------------------------------------------------------
8) Pack Pragma Support                                                       
-------------------------------------------------------------------------------

Version 7.4.0 of the C6000 compiler enables beta-level support for the pack
pragma. This pragma can be used to control the alignment of fields within a
class type. Supported subtargets are C64x, C64+, C6600, and C6740. The basic 
syntax supported is as follows:

   #pragma pack(n)
      This pragma will affect the next seen class declaration, forcing the
      maximum alignment of each field to be the value represented by n. Valid
      values for n are 1, 2, 4, 8, and 16 bytes.

   #pragma pack(push, n)
   #pragma pack(pop)
      As above, but affects all class declarations between the push and pop
      directives. Note that a pop with no prior push results in a warning 
      diagnostic being issued from the compiler.
   
   #pragma pack(show)
      Emits a warning diagnostic to stderr, describing the current state of
      the pack pragma stack. This is useful for diagnosing issues while 
      debugging.

As the support in this release is of beta quality, there are two known
issues that will be resolved in a future version of the compiler:

   1) A pack pragma affecting a derivation of a base class will ignore
      alignment restrictions imposed by that pragma.

         struct B { int i; };  // Usually aligned on a 4-byte boundary.
         #pragma pack(1)
         struct D: B {
         char c;
         };  // Struct D always had the same alignment as struct B.

   2) A bitfield with an align attribute within a class affected by a pack
      pragma currently ignores the attribute.

         #pragma pack(4)
         struct S {
            char c;
            int i:1 __attribute((aligned(4)));
         };  //Currently, S is size 4 when it should be size 8 

-------------------------------------------------------------------------------
9) Typeinfo in subsections
-------------------------------------------------------------------------------

This release contains an option for users who wish the control the placement
of C++ type information. This information is generated both at the user's
discretion via access through the typeinfo header file as well as
automatically when code contains exception handling or virtual members and
base classes.

Normally, it is impossible to control where this information is placed via the
linker command file, but with this new option, all type information is placed
into the subsection .const:.typeinfo

To enable the placement of typeinfo into subsections, use the option
--typeinfo_subsections when running the compiler, and then place the subsection
.const:.typeinfo in the linker command file to the desired memory bank.

Using this option could potentially change cache behavior in the program and
therefore change performance. In general, however, placing typeinfo into
slower memory will allow for more frequently used information to be placed
into fast memory and increase speed.

-------------------------------------------------------------------------------
10) Support for <complex.h>
-------------------------------------------------------------------------------
Complex in C99 is supported starting from 7.4.0 for C6000.

In C99, complex is a built-in type. Or more specifically, there are three
built-in types as summarized in the following table:

Type	             Memory space	Alignment
float complex	     64	                32
double complex	     128	        64
long double complex  128	        64

To use complex, you need to #include <complex.h> 

Complex is supported by default. There is no special compiler option to use it.

Appendix G of the C99 standard specifies additional functionality for complex
types for conformance to the IEC 60559 Standard.  7.4.0 does not support 
Appendix G.

As for debug, TI compiler implements the complex number as a struct with a two
element array. For example, for a given float complex object:

            float complex x;

In the debugger, the user should know that x._Vals[0] is the real part,
and x._Vals[1] is the imaginary part.

-- End Of File --
