 /*--------------------------- keystoneII.lds ----------------------------
 |  File keystoneII.lds
 |
 |  Description: This file provides the memory layout and allocation
 |               scheme for the linking process.
 |               It is a modification from Rafael de Souza's sample.
 |
 *-----------------------------------------------------------------------*/

MEMORY
{

	MSMC_SRAM:      o = 0x0C000000,  l = 0x00600000   /* 6MB Multicore shared Memmory */

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


    ARM_DDR3:      o = 0x80000000 l = 0x10000000   /* 256MB DDR3 SDRAM for CORE0 */
    used:      o = 0x90000000 l = 0x08000000   	   /* 128MB DDR3 SDRAM for DSP0 */
    CORE1_DDR3:      o = 0xB0000000 l = 0x10000000   /* 256MB DDR3 SDRAM */
    CORE2_DDR3:      o = 0xC0000000 l = 0x10000000   /* 256MB DDR3 SDRAM */
    CORE3_DDR3:      o = 0xD0000000 l = 0x10000000   /* 256MB DDR3 SDRAM */

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
