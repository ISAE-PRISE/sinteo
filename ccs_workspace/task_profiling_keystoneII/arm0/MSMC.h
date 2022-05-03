/*--------------------------- MSMC.h -------------------------------------
 |  File MSMC.h
 |
 |  Description:  Contains functions related to the DSPs and ARM cores
 |                slaves properties related to the Multicore Shared Memory
 |                Controller (MSMC), e.g., slaves starvation counter
 |                Functions are Keystone II platform specific.
 |
 |  User Guide: https://www.ti.com/lit/ug/spruhj6/spruhj6.pdf?ts=1639478686458
 |
 |  Version: 1.1V
 *-----------------------------------------------------------------------*/

#define MSMC_BASE_ADDRESS     (0x000BC00000)
#define SBNDC0_OFFSET         (0x30)
#define ARM_SBNDC8_OFFSET     (0xD0)
#define SBNDC_MASK            (0x00FF00FF)



/* read_SBNDC
 *
 * Description: Retrieves the Starvation Bound Register values, which contains the reload value for the DSP slaves starvation counters
 *              Bits 16-23: Reload value (pre-scaled by 16) for the starvation counter for C66x CorePac slave n requests at the EMIF arbiter
 *              Bits 0-7: Reload value for the starvation counters for C66x CorePac slave n requests at the RAM bank arbiters
 *
 * Parameter:
 *              - unsigned slave: The DSP slave to read the register from (value from 0 to 7)
 *
 *
 * Returns:     The register SBNDCn, where n is the given slave.
 *
 * */
unsigned read_SBNDC(unsigned slave){
    unsigned* address = (unsigned*)(MSMC_BASE_ADDRESS + SBNDC0_OFFSET + 0x04*slave);
    return *address;
}

/* write_SBNDC
 *
 * Description: Sets the values for the Starvation Bound Register.
 *              Bits 16-23: Reload value (pre-scaled by 16) for the starvation counter for C66x CorePac slave n requests at the EMIF arbiter
 *              Bits 0-7: Reload value for the starvation counters for C66x CorePac slave n requests at the RAM bank arbiters
 *
 * Parameter:
 *              - unsigned slave: The DSP slave to read the register from (value from 0 to 7)
 *              - unsigned value: The new SBNDC register values of the SBNDC register. The reload starvation counter accepts values from 0 to 0xFF
 *              See register values at https://www.ti.com/lit/ug/spruhj6/spruhj6.pdf?ts=1645815586891 (Table 3-11 Starvation Bound Register for C66x CorePac Slave Ports (SBNDCn) Field Descriptions)
 *
 * Returns:     Nothing
 *
 * */
void write_SBNDC(unsigned slave, unsigned value){
    unsigned* address = (unsigned*)(MSMC_BASE_ADDRESS + SBNDC0_OFFSET + 0x04*slave);
    *address = value & SBNDC_MASK;
}


/* print_SBNDC_Registers
 *
 * Description: Prints via CCS console the values of the SBNDC register
 *              Bits 16-23: Reload value (pre-scaled by 16) for the starvation counter for C66x CorePac slave n requests at the EMIF arbiter
 *              Bits 0-7: Reload value for the starvation counters for C66x CorePac slave n requests at the RAM bank arbiters
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void print_SBNDC_Registers(){
    unsigned i = 0;

    for(i = 0; i < 8; i++){
        unsigned address = read_SBNDC(i);
      printf("SBNDC%d value is: %X \n", i, address);
    }
}


/* read_ARM_SBNDC
 *
 * Description: Retrieves the Starvation Bound Register values, which contains the reload value for the ARMs unified slave starvation counters
 *              Bits 16-23: Reload value (pre-scaled by 16) for the starvation counter for the ARMs unified slave requests at the EMIF arbiter
 *              Bits 0-7: Reload value for the starvation counters for the ARMs unified slave requests at the RAM bank arbiters
 *
 * Caveats:     This register is configurable but hidden in the manual. The same fields as the DSP register apply here as well
 *
 * Parameter:   None
 *
 *
 * Returns:     The register SBNDCn, where n is the given slave.
 *
 * */
unsigned read_ARM_SBNDC(){
    unsigned* address = (unsigned*)(MSMC_BASE_ADDRESS + ARM_SBNDC8_OFFSET); //SBNDC8 (offset 0xD0)
    return *address;
}


/* write_ARM_SBNDC
 *
 * Description: Sets the values for the Starvation Bound Register of the ARMs unified slave.
 *              Bits 16-23: Reload value (pre-scaled by 16) for the starvation counter for the ARMs unified slave requests at the EMIF arbiter
 *              Bits 0-7: Reload value for the starvation counters for the ARMs unified slave requests at the RAM bank arbiters
 *
 * Caveats:     This register is configurable but hidden in the manual. The same fields as the DSP register apply here as well.
 *              Be aware that there is a unique slave for the ARMs, and hence, one register that configures the starvation counter of all of them.
 *
 * Parameter:
 *              - unsigned value: The new ARM SBNDC register values of the ARM SBNDC register. The reload starvation counter accepts values from 0 to 0xFF
 *              See register values at https://www.ti.com/lit/ug/spruhj6/spruhj6.pdf?ts=1645815586891 (Table 3-11 Starvation Bound Register for C66x CorePac Slave Ports (SBNDCn) Field Descriptions)
 *
 *
 * Returns:     Nothing
 *
 * */
void write_ARM_SBNDC(int value){
    unsigned* address = (unsigned*)(MSMC_BASE_ADDRESS + ARM_SBNDC8_OFFSET);
    *address = value & SBNDC_MASK;
}

/* print_ARM_SBNDC_list
 *
 * Description: Prints via CCS console the values of the SBNDC register for the ARMs
 *
 * Caveats:     This register is configurable but hidden in the manual. The same fields as the DSP register applies here as well
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void print_ARM_SBNDC_list(int value){
    unsigned i = 0;
        for(i = 0; i < 5; i++){
            unsigned* address = (unsigned*)(MSMC_BASE_ADDRESS + ARM_SBNDC8_OFFSET + 0x04*i);
            *address = value & SBNDC_MASK;
            printf("SBNDC8%d value is: %X \n", i, *address);
        }
}

