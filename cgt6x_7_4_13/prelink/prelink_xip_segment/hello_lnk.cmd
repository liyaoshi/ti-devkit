/****************************************************************************/
/*  lnk.cmd   v4.00                                                         */
/*  Copyright (c) 1996-2000  Texas Instruments Incorporated                 */
/****************************************************************************/
-c
-heap  0x2000
-stack 0x6000   /* Modified by Gayathri on 6/3/2003 as Perennial P50031 fails
		   due to stack overflow - solution suggested by Todd Snider */

MEMORY
{
        PMEM:   o = 00000020h   l = 01000000h
        BMEM:   o = 80000000h   l = 01000000h
}

/* Added sections .neardata and .rodata to permit ELF testing. Doesn't      */
/* affect COFF, since COFF doesn't have these sections. -Indira, 6/9/08     */                     

SECTIONS
{
    big_ro:
    {
       *(.text)
       *(.const)
       *(.far)
       *(.fardata)
    } > PMEM

    .stack      >       BMEM
    .args       >       BMEM

    GROUP
    {
            .neardata   /* Move .bss after .neardata and .rodata. ELF  allows */
            .rodata     /* uninitialized data to follow initialized data in a */
            .bss        /* single segment. This order facilitates a single    */
                        /* segment for the near DP sections.                  */
    }>BMEM

    .cinit      >       BMEM
    .cio        >       BMEM
    .data       >       BMEM
    .switch     >       BMEM
    .sysmem     >       BMEM
    .ppinfo     >       BMEM
    .ppdata     >       BMEM, palign(32) /* Work-around kelvin bug */
}
