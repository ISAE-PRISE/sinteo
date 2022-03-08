/****************************************************************************/
/*  C6678.cmd                                                               */
/*  Copyright (c) 2011 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an C6678              */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/*    Usage:       The map below divides the external memory in segments    */
/*                 Use the linker option --define=COREn=1                   */
/*                 Where n is the core number.                              */
/*                                                                          */
/****************************************************************************/

MEMORY
{

    OCMC_RAM1:  o = 0x40300000  l = 0x00080000  /* 512kB L3 OCMC RAM1 */
    OCMC_RAM2:  o = 0x40400000  l = 0x00100000  /* 1MB L3 OCMC RAM2 */
    OCMC_RAM3:  o = 0x40500000  l = 0x00100000  /* 1MB L3 OCMC RAM3 */

    ARM_DDR3:      o = 0x80000000 l = 0x10000000   /* 512MB DDR3 SDRAM for CORE0 */
    used:      o = 0x90000000 l = 0x08000000   /* 256MB DDR3 SDRAM for CORE0 */
    CORE1_DDR3:      o = 0xB0000000 l = 0x10000000   /* 512MB DDR3 SDRAM for CORE1 */
    CORE2_DDR3:      o = 0xC0000000 l = 0x10000000   /* 512MB DDR3 SDRAM for CORE2 */
    CORE3_DDR3:      o = 0xD0000000 l = 0x10000000   /* 512MB DDR3 SDRAM for CORE3 */

    stack:      o = 0xF0000000 l = 0x4000000
}
/*
     DDR_ROW_1 = 0x8801A000;
     DDR_ROW_2 = 0x8802A000;
*/
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
