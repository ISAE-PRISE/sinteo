 /*--------------------------- C6678.cmd -------------------------------
 |  File C6678.cmd
 |
 |  Description: This file provides the memory layout and allocation 
 |               scheme for the linking process.
 |               It is a modification from Rafael de Souza's sample.
 |
 *-----------------------------------------------------------------------*/
 
MEMORY
{

    OCMC_RAM1:  o = 0x40300000  l = 0x00080000  /* 512kB L3 OCMC RAM1 */
    OCMC_RAM2:  o = 0x40400000  l = 0x00100000  /* 1MB L3 OCMC RAM2 */
    OCMC_RAM3:  o = 0x40500000  l = 0x00100000  /* 1MB L3 OCMC RAM3 */

    ARM_DDR3:      o = 0x80000000 l = 0x10000000   /* 256MB DDR3 SDRAM for CORE0 */
    used:      o = 0x90000000 l = 0x08000000   /* 128MB DDR3 SDRAM for CORE0 */
    CORE1_DDR3:      o = 0xB0000000 l = 0x10000000   /* 256MB DDR3 SDRAM for CORE1 */
    CORE2_DDR3:      o = 0xC0000000 l = 0x10000000   /* 256MB DDR3 SDRAM for CORE2 */
    CORE3_DDR3:      o = 0xD0000000 l = 0x10000000   /* 256MB DDR3 SDRAM for CORE3 */
}

SECTIONS
{


    .text          >  used
    .stack         >  used
    .bss           >  used
    .cio           >  used
    .const         >  used
    .data          >  used
    .switch        >  used
    .sysmem        >  used
    .far           >  used
    .args          >  used
    .ppinfo        >  used
    .ppdata        > used

    /* COFF sections */
    .pinit         >  used
    .cinit         >  used

    /* EABI sections */
    .binit         >  used
    .init_array    >  used
    .neardata      >  used
    .fardata       >  used
    .rodata        >  used
    .c6xabi.exidx  >  used
    .c6xabi.extab  >  used


}
