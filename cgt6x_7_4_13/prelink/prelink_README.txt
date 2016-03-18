
                       ===========================
                       TMS320C6x  Prelink  Utility
			Early Adopter Capability
                           7.2 -- January 2011
                       ===========================

===============================================================================
Contents
===============================================================================
1) Functional Summary
   1.1) What is Implemented in This Release?
   1.2) What is Missing?
2) Prelink Tool Usage
3) Examples
   3.1) Prelink a Dynamic Executable with No Dependents
   3.2) Prelink a Group of Interdependent DLLs
   3.3) Prelink a Dynamic Executable with an XIP Segment
   3.4) Provide DSBT Assistance to Dynamic App via Prelink

-------------------------------------------------------------------------------
1) Functional Summary
-------------------------------------------------------------------------------

The C6000 Code Generation Tools Release v7.2.0 contains an early adopter
version of the prelink utility, prelink6x.

The prelink utility can be used to offload tasks that are normally performed
by the dynamic linker/loader in order to reduce load and/or startup time.

Some of the tasks typically performed by the prelinker include:

* Relocation of Load Segments - Binding load segments in a dynamic object
  file to the addresses where they will be loaded so that the dynamic 
  linker/loader does not have to perform storage allocation at load time.

* Dynamic Relocation - Resolving references to imported symbols. A normal 
  dynamic linker/loader spends a significant percentage of its time doing
  symbol lookups during the processing of dynamic relocations. If the 
  prelink utility is tasked with processing the dynamic relocations
  statically, then this processing can be avoided at load time.

When a dynamic system is using the DSBT model, the prelinker can also be
used to provide DSBT assistance:

* DSBT Index Assignment - The prelinker can be used to honor specific
  user requests to assign a specific DSBT index to a specific dynamic object
  file. The prelinker can also be used to auto-assign DSBT indices to 
  dynamic object files that are left without an assigned DSBT index after
  processing all specific user requests.

* DSBT Size Checking - When prelinking a dynamic system that makes use of
  the DSBT model, the prelinker will check the space allocated for the
  DSBT for each dynamic object file to ensure that each module's DSBT is
  large enough to accommodate all needed DSBT entries for the dynamic 
  system.


1.1) What is Implemented in This Release?
-----------------------------------------

* Input

  The input to the prelink command line is limited to the following:

  o Command File

    A named input file can be a command file which is effectively an
    extension of the prelink command line. A command file may only 
    contain options and file names, each on a line by themselves.
    The prelinker will begin processing the contents of a command 
    file at the point which it is specified in the command line or
    in another command file.

  o Dynamic Object File

    A named input file that is not a command file, must be either a 
    dynamic executable or a dynamic shared object. Any other kind of 
    file will be ignored with a warning diagnostic to the user.

  o Options

    The prelinker supports several options. The primary interface
    for controlling the placement of segments is the --segment_address
    option. A complete list of the options supported is provided in
    the "Prelink Tool Usage" section below (see section 2).
    
* File Dependency Graph Completion

  The prelink utility currently assumes that all files to be prelinked
  as part of a system of applications will be explicitly input via
  the command line of the prelinker or in a prelink command file.

  The prelinker will check to make sure that all dependent files in
  the system are accounted for before proceeding with the prelink.

  Why? If there is more than one definition of a symbol among the
  dependents of a file that uses that symbol, and if the first 
  dependent file that contains the definition of the symbol is 
  missing, then the parent file will patch its references to the
  symbol using the wrong definition. Insisting on file dependency
  graph completeness avoids this problem.

  It is anticipated that there will be a search path supported 
  whereby the prelinker can search for missing dependents in order
  to complete the file dependency graph. This would lessen the burden
  on the user to explicitly input all files in the system each time
  the prelinker is invoked.

* XIP Segment Instructions

  The prelinker supports an --xip_segment option which allows a
  user to specify an assumed file address and then to impose an
  alignment constraint on one segment in the file. The prelinker
  will then set the file offset, alignment, and virtual address 
  fields for the segment appropriately based on the given file 
  address and the alignment constraint on the execute-in-place (XIP)
  segment.

  Syntax:

  --xip_segment="<file soname>=<file addr>,<seg index>,<seg align>"

  > file soname - names an input file in the system; the prelinker 
    will search for the file via its soname first, and then via the
    input file specification for the file

  > file addr - indicates the virtual address of the file to be 
    assumed by the prelinker when computing the XIP segment's file
    offset and virtual address. The specified file address must
    be aligned to the specified segment alignment; otherwise the
    option will be ignored with a warning to the user

  > seg index - indication of which segment in the specified file
    is to be considered execute-in-place (XIP). Only one segment
    in a given dynamic object file can be identified as an XIP
    segment

  > seg align - indicates the alignment constraint to be applied 
    to the specified XIP segment in the file. The specified alignment
    must be a power of 2 less than or equal to 0x1000 (4K). As
    indicated above, the specified file address is also constrained
    to be aligned to the specified segment alignment boundary

* Segment Address Instructions

  The prelinker supports a --segment_address option which allows
  a user to specify a new address for a segment in the system.

  Syntax:

  --segment_address="<file soname>[<segment index>]=<address>"

  > file soname - names an input file in the system; the prelinker 
    will search for the file via its soname first, and then via the
    input file specification for the file

  > segment index - optional indication of which segment in the
    file the instruction is to be applied to. If the segment index
    is not specified, then the address will be applied to the 
    first PT_LOAD segment in the file. The address delta of the first 
    segment will be applied to the remaining PT_LOAD segments in
    the file.

  > address - address where segment is to be placed.

* Updating Address References

  The prelinker will patch address references in the following:

  o Entry Point

  o Program Header Table - array of segment descriptors

  o Section Header Table - array of section descriptors

  o Dynamic Table - array of dynamic tag/value pairs

  o Symbol Tables - all symbols that are defined in a section will
                    be updated to reflect the new segment addresses

  o Relocated Data - relocations will be applied

  o Relocation Entry Offsets - all relocation entries will be 
                    updated; their offset field will reflect the
		    new virtual address where the relocation is to
		    be applied (should the data need to be relocated
		    again)

* DSBT Assistance

  The prelink utility will now provide DSBT assistance for applications
  that are built to use the DSBT model for sharing dynamic objects.

  DSBT Index Assignment Paradigm 

  1. Honor DT_C6000_DSBT_INDEX requests from input files; 
  2. Honor user requests for DSBT index assignments via --dsbt_index options 
  3. For any dynamic object file in the system that doesn't have a DSBT index
     assignment; assign a DSBT slot to the dynamic object 
  
  New DSBT-Related Options 

  --auto_assign_dsbt_indices[=on|off] 

     Indicates whether or not prelink utility performs auto-assignment of 
     DSBT indices to any dynamic object file in the system that doesn't
     already have a DSBT index assignment; this is assumed "on" by default. 
     "off" means that the prelinker will leave dynamic object files that do 
     not have a DSBT index assigment unassigned. This behavior is subject
     to change in the near future. It is expected that if the option is
     "off", if there any objects that are left unassigned after the user 
     DSBT index requests have been processed, then the prelinker will 
     emit an error and terminate the prelink session.

     --dsbt_index request options are allowed and will be processed even 
     when the --auto_assign_dsbt_indices is "off". 

  --dsbt_index="<soname>=<index>" 

    Request a specific DSBT index to be assigned to the specified dynamic
    object file.
    
    > soname - names an input file in the system; the prelinker will 
      search for the file via its soname first, and then via the input 
      file specification for the file

    > index - indicates the DSBT index to be assigned to the file

    If the requested DSBT index is already assigned to another file, then 
    a warning is emitted and the option is ignored. 

  Assumptions / Limitations / Potential Issues 

  o Assume that each DSO in the system gets a unique DSBT index 

    At this time, this means that assigning two separate DSOs to the same DSBT
    slot will be detected and treated as a fatal error, even though they may not
    conflict with each other at run time 
    
    - as long as they are never actually shared between two or more application 
      that could potentially be running at the same time, then there should not 
      be a conflict 

  o Assume that loader or other tool is responsible for actually populating
    the DSBTs 

    The prelink utility cannot do this. 

    - Load/run or map tool is responsible for actual allocation of a shared 
      object's RW segment in a given application's memory space 
    - Prelink doesn't know the value to put in the 0th entry of a shared 
      object's DSBT 

  o Assume that any object that has a DSBT index assigned will not be changed
    (given a different DSBT index) 

    Once prelink makes an assignment to an object and resolves the relocation
    that references the DSBT index, the dynamic relocation will be removed

* Output

  A prelinked output file, by default, will be written to the current
  working directory using the basename of the input file with a 
  default extension of ".pdo".

  i.e. An input file, "xyz.dll", will produce "xyz.pdo" as the
  prelinked output of "xyz.dll".

  The prelinker also supports the following options to provide some
  control over the name and location of the prelink output file:

  --prelink_extension="<ext>"

  --prelink_directory="<directory path of prelink output files>"

  For example,

     prelink6x --prelink_extension="pre" --prelink_directory="./PRE" xyz.dll ...

  will write prelink output file, "xyz.pre" to the "PRE" subdirectory.

  The prelinked output file will now contain a DT_C6000_PRELINKED dynamic
  tag in its dynamic table to indicate that the file has been prelinked.
  This tag can be read in combination with the timestamp in the file 
  header to determine when the prelinked output file was created.

* Prelinked Output XML Reports

  This release of the prelink utility introduces a new option, 
  --xml_prelink_info, which causes the prelinker to generate an XML
  file that contains useful details about the output of the prelink
  session, including:

  o File Dependency Information

    Including use counts for all files in the system and a list of each
    file's dependents.

  o DSBT Assistance Results
  
    If applicable, this includes a summary of the DSBT index assignments 
    for the entire dynamic system that was input to the prelinker.

  o Prelinked Output Files Summary

    For each prelinked output file, the XML report will include:

    - File Header (entry point, prelink timestamp)
    - Program Header Table (updated segment placement information)
    - Dynamic Table (contents of the .dynamic section)
    - Updated Symbol Tables (symbols reflect updated segment placements)

  Usage:

  --xml_prelink_info=<file>

  <file> -- user-specified file to which XML information will be written.

1.2) What is Missing?
---------------------

* Prelinked Output Text Reports

  An output file much like the linker's map file that reports the affect
  of the prelink session. For each dynamic object file specified as input
  for the dynamic system, this file should contain a minimum of the 
  updated segment addresses for each file along with a summary of the
  DSBT index assignments for the system, if applicable.

  Additionally, an XML representation of the file dependency graph will
  be provided in a separate output file by the prelinker.

* Search Path

  A mechanism whereby the prelinker can search for dependent files that
  are missing from the file dependency graph without having to specify
  all files explicitly to the prelinker.

-------------------------------------------------------------------------------
2) Prelink Tool Usage
-------------------------------------------------------------------------------

Below is the output of "prelink6x --help" ...

<start help output>

TMS320C6x Prelink                       v7.2.0
Tools Copyright (c) 1996-2011 Texas Instruments Incorporated

Usage: prelink6x [-options] filename

Use 'prelink6x -h <option>' for more information on a particular option.  Use
'prelink6x -h <text>' to search options for information regarding <text>.

Option arguments surrounded by [] declare they are optional.  Option arguments
separated by commas specify that the option's argument must be chosen from
those arguments listed.

When shown, option arguments and defaults apply to the usage of both long and
short option forms.

Options:
  --auto_assign_dsbt_indices[=off,on]
                               Auto-assign DSBT indices for objects that need
                                an index (argument optional, defaults to: on)
  --dsbt_index=specification   Specify DSBT index to be assigned to a dynamic
                                object file
  --help,-h                    Display help
  --prelink_directory=dir      Prelink file directory (default is .)
  --prelink_extension[=ext]    Specify extension for prelinked files (default
                                is .pdo)
  --quiet,-q                   Suppress banner and progress output
  --segment_address=specification
                               Specify segment to address placement instruction
  --xip_segment=specification  Specify file's address and alignment for an XIP
                                segment

<stop help output>

All inquiries and defect reports about the prelink utility, prelink6x, should
be submitted using the ClearQuest database at the following URL:

    http://cqweb.itg.ti.com/SDO

Enter the version 7.2.0 in the "Release/Version" section.

-------------------------------------------------------------------------------
3) Examples
-------------------------------------------------------------------------------

Below are a couple of examples that were used during the development and
testing of the basic prelinker functionality.

There are four subdirectories included under the "./prelink" directory where
the v7.2.0 release was installed (prelink_dyn_exe, prelink_dependents, 
prelink_xip_segment, and prelink_dsbt_assistance). The sections below provide 
a brief tour through the use of the prelinker using the files in these 
subdirectories to illustrate.

3.1) Prelink a Dynamic Executable with No Dependents
----------------------------------------------------

Working in "prelink_dyn_exe" sub-directory ...

0. Build a simple dynamic executable, hello.exe:

   %> ./build_dyn_exe

   Notes: 
   
   o -r option is used to retain relocations
   o you will need to update the definition of C_DIR and C6X_C_DIR to reflect
     the location of your lnk.cmd file and RTS libraries
   o run the executable somewhere to make sure that it works

1. Prelink; explicitly defining a new address for every segment

   %> prelink6x hello_1.cmd

   Notes:

   o hello.exe is specified in command file along with all --segment_address
     options
   o run hello.pdo somewhere to make sure that it works
   o use ofd6x -v hello.pdo to browse the result of the prelink and ensure
     that the new segment addresses have been applied properly

2. Prelink; rename extension and location of prelink output file

   %> mkdir prelink_out_area
   %> prelink6x hello_2.cmd

   Notes:

   o prelink output is hello.pde in prelink_out_area subdirectory
   o run hello.pde somewhere to make sure that it works
   o use ofd6x -v hello.pde to browse the result of the prelink and ensure
     that the new segment addresses have been applied properly

3. Prelink; specify only one new segment address for segment #2

   %> prelink6x hello_3.cmd

   Notes:

   o only segment #2 moves to a new address; all other segments 
     are left unchanged except for references to objects in 
     segment #2
   o run hello.pdo somewhere to make sure that it works
   o use ofd6x -v hello.pdo to browse the result of the prelink;
     relocations that apply to segment #2 will move into the 
     0xa0000000 address range
     that the new segment addresses have been applied properly

4. Prelink; no segment index is specified in --segment_address instruction

   %> prelink6x hello_4.cmd

   Notes:

   o first PT_LOAD segment will move to 0x2000; all other segments will
     move according to segment #1's address delta
   o run hello.pdo somewhere to make sure that it works
   o use ofd6x -v hello.pdo to browse the result of the prelink and ensure
     that the new segment addresses have been applied properly


3.2) Prelink a Group of Interdependent DLLs
-------------------------------------------

Working in "prelink_dependents" sub-directory ...

0. Build some interdependent DLLs:

   %> ./build_dlls

   Notes: 
   
   o -r option is used to retain relocations
   o you will need to update the definition of C_DIR and C6X_C_DIR to reflect
     the location of your lnk.cmd file and RTS libraries
   o the interdependencies are detailed in the build_dlls script

1. Prelink; move segments of each DLL to a different address area

   %> prelink6x depends.cmd

   Notes:

   o all DLL files are specified as input in the depends.cmd file
   o see --segment_address instructions in depends.cmd for details
     about where each DLL should get moved to as the result of the prelink
   o use ofd6x -v <basename>.pdo to browse the result of the prelink and ensure
     that the new segment addresses have been applied properly in each
     prelink output file produced


3.3) Prelink a Dynamic Executable with an XIP Segment
-----------------------------------------------------

Working in "prelink_xip_segment" sub-directory ...

0. Build a simple dynamic executable, hello.exe:

   %> ./build_dyn_exe

   Notes: 
   
   o the hello_lnk.cmd linker command file is used to collect initialized
     sections into a single RO segment
   o -r option is used to retain relocations
   o you will need to update the definition of C_DIR and C6X_C_DIR to reflect
     the location of your lnk.cmd file and RTS libraries
   o run the executable somewhere to make sure that it works

1. Prelink; explicitly specify the file address and the XIP segment alignment

   %> prelink6x prelink_hello.cmd

   Notes:

   o hello.exe is specified in command file along with an --xip_segment
     option that indicates an alignment of 0x200 to be applied to the first 
     PT_LOAD segment in the file
   o run hello.pdo somewhere to make sure that it works
   o use ofd6x -v hello.pdo to browse the result of the prelink and ensure
     that the file offset, load/run address, and alignment of the "big_ro"
     segment are correct per the specification of the --xip_segment option

3.4) Provide DSBT Assistance to Dynamic App via Prelink
-------------------------------------------------------

This is a tutorial example which demonstrates the DSBT assistance support
provided by the prelinker.

You can also find these instructions in the "prelink_dsbt_assistance" 
sub-directory in a file called "instructions.txt".

1. Build a DSBT version of the RTS library that you need

   %> mkdir dsbt_rts_work_area
   %> cd dsbt_rts_work_area
   %> cp <release installation directory>/lib/rtssrc.zip .
   %> unzip rtssrc.zip

   For the following step, use the RTS library name that you need in place
   of "rts64plus_elf.lib":

   %> gmake OPT_CMDLINE="--dsbt --mem_model:data=far" rts64plus_elf.lib

   %> cd .. 

2. Build up dynamic libraries and dynamic executable used as prelink6x input

   This tutorial example contains the following source files:

   printf.c
   a.c
   b.c
   c.c
   d.c
   driver.c
   main.c
   format.h

   Use script, build_dyn_objs, to create dynamic objects that will be used 
   for prelink examples below:

   %> ./build_dyn_objs

   You will need to edit build_dyn_objs and make adjustments to use the 
   appropriate options and RTS library for your situation.

3. Now prelink the dynamic libraries and dynamic executables

  3.1 You can order the prelinker to take user requests to assign DSBT 
      indices to any of the input dynamic objects:

      %> prelink6x dsbt_ex_1.cmd

      where dsbt_ex_1.cmd contains:

      --dsbt_index="depends.dll=2" 
      --dsbt_index="printf.dll=1" 
      --dsbt_index="a.dll=6" 
      --dsbt_index="b.dll=4" 
      --dsbt_index="c.dll=5" 
      --dsbt_index="d.dll=3" 

      Observe that in the prelink output files (*.pdo), new dynamic tags 
      have been added to each file's dynamic table to indicate that a DSBT 
      index has been assigned to the file and that the file has been 
      prelinked:
      
      %> ofd6x -v depends.pdo | less

      shows:

          20 DT_C6000_DSBT_INDEX  2


  3.2 You can set up DSBT index assignments during the static link step and 
      these assignments will be honored by the prelinker.

      In this example, you will need to re-build one or more dynamic objects
      and use the static linker's --dsbt_index option to assign a DSBT index
      to the dynamic object that is under construction. You can use the 
      rebuild_some_dlls script provided:

      %> ./rebuild_some_dlls

      Again, you may need to edit the rebuild_some_dlls script to use the
      appropriate options and RTS library for your situation.

      Then run the prelinker:

      %> prelink6x dsbt_ex_2.cmd

      where dsbt_ex_2.cmd contains:

      --dsbt_index="depends.dll=3"

      Observe that in the prelink output file, the DSBT indices that were 
      assigned during the static link step to c.dll and d.dll are kept intact.
      The DSBT requests that were made in the prelink command file are also 
      honored, and for those objects that were left unassigned after 
      processing specific user requests (--dsbt_index options), these will be
      assigned a DSBT index automatically by the prelinker.

      Look for DT_C6000_DSBT_INDEX tags in the following ofd6x commands:

      %> ofd6x -v c.pdo | less
      %> ofd6x -v depends.pdo | less
      %> ofd6x -v b.pdo | less


