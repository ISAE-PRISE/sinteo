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
    SHARED_SRAM:     o = 0x0C000000 l = 0x00600000   /* 6MB Multicore shared Memmory */

    CORE0_L2_SRAM:   o = 0x10800000 l = 0x00100000   /* 1  MB CORE0 L2/SRAM */
    CORE0_L1P_SRAM:  o = 0x10E00000 l = 0x00008000   /* 32kB CORE0 L1P/SRAM */
    CORE0_L1D_SRAM:  o = 0x10F00000 l = 0x00008000   /* 32kB CORE0 L1D/SRAM */
  
    CORE1_L2_SRAM:   o = 0x11800000 l = 0x00100000   /* 1  MB CCORE1 L2/SRAM */
    CORE1_L1P_SRAM:  o = 0x11E00000 l = 0x00008000   /* 32kB CORE1 L1P/SRAM */
    CORE1_L1D_SRAM:  o = 0x11F00000 l = 0x00008000   /* 32kB CORE1 L1D/SRAM */
  
    CORE2_L2_SRAM:   o = 0x12800000 l = 0x00100000   /*1  MB  CORE2 L2/SRAM */
    CORE2_L1P_SRAM:  o = 0x12E00000 l = 0x00008000   /* 32kB CORE2 L1P/SRAM */
    CORE2_L1D_SRAM:  o = 0x12F00000 l = 0x00008000   /* 32kB CORE2 L1D/SRAM */
  
    CORE3_L2_SRAM:   o = 0x13800000 l = 0x00100000   /*  1MB CORE3 L2/SRAM */
    CORE3_L1P_SRAM:  o = 0x13E00000 l = 0x00008000   /* 32kB CORE3 L1P/SRAM */
    CORE3_L1D_SRAM:  o = 0x13F00000 l = 0x00008000   /* 32kB CORE3 L1D/SRAM */

    ARM0_DDR3:      o = 0x80000000 l = 0x10000000   /* 256MB DDR3 SDRAM for ARM CORE0 */
    DSP0_DDR3:      o = 0x90000000 l = 0x10000000   /* 256MB DDR3 SDRAM for DSP CORE0 */
    used:           o = 0xA0000000 l = 0x10000000   /* 256MB DDR3 SDRAM for DSP CORE7 */


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

    .csl_vect >  used


}
