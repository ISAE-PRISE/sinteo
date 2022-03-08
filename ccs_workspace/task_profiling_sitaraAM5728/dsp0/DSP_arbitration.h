/*--------------------------- DSP_arbitration.h -------------------------------------
 |  File DSP_arbitration.h
 |
 |  Description:  Provides function related to the DSP
 |                slaves such as arbitration management, priority or
 |                anti-starvation mechanisms configuration.
 |
 |  Version: 1.0V
 *-----------------------------------------------------------------------*/

#define CPUARB_BASE_ADDRESS         (0x01820200)
#define CPUARBU_BASE_ADDRESS         (0x01841000)
#define CPUARBD_BASE_ADDRESS         (0x01841040)
#define MDMAARBU_BASE_ADDRESS         (0x01841010)
#define SDMAARBD_BASE_ADDRESS         (0x01841048)
#define SDMAARBU_BASE_ADDRESS         (0x01841008)
#define SDMAARBE_BASE_ADDRESS         (0x01820208)
#define MDMAARBX_BASE_ADDRESS         (0x08000280)

#define SBNDC0_OFFSET               (0x30)
#define ARM_SBNDC8_OFFSET               (0xD0)

#define SBNDC_MASK            (0x00FF00FF)
#define CPUARBE_MASK          (0x0007003F)
#define MDMAARBU_MASK         (0x07070000)
#define SDMAARB_MASK          (0x0000003F)


/* read_CPUARBE
 *
 * Description: Retrieves the DSP Arbitration Control Register CPUARBE values, which manages the bandwidth of the DSP operations memory accesses made in EMC blocks. It applies to all the available DSPs
 *              Bits 16-18: Priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *              Bits 0-5: Maximum wait time in EMC cycles
 *
 * Parameter:   None
 *
 *
 * Returns:     The register CPUARBE
 *
 * */
unsigned read_CPUARBE(){
    unsigned* address = CPUARB_BASE_ADDRESS;
    return *address;
}

/* write_CPUARBE
 *
 * Description: Sets the DSP Arbitration Control Register CPUARBE values, which manages the bandwidth of the DSP operations memory accesses made in EMC blocks. It applies to all the available DSPs
 *              Bits 16-18: Priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *              Bits 0-5: Maximum wait time in EMC cycles
 *
 * Parameter:
 *              - unsigned value: The new values of the CPUARBE register.
 *                See register values at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1645783090235 (Table 8-4 DSP Arbitration Control Register (CPUARBD, CPUARBU, CPUARBE))
 *
 * Returns:     Nothing
 *
 * */
void write_CPUARBE(unsigned value){
    unsigned* address = CPUARB_BASE_ADDRESS;
    *address = value & CPUARBE_MASK;
}

/* read_CPUARBD
 *
 * Description: Retrieves the DSP Arbitration Control Register CPUARBD values, which manages the bandwidth of the DSP operations memory accesses made in L1D/L1P blocks. It applies to all the available DSPs
 *              Bits 16-18: Priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *              Bits 0-5: Maximum wait time in EMC cycles
 *
 * Parameter:   None
 *
 *
 * Returns:     The register CPUARBD
 *
 * */

unsigned read_CPUARBD(){
    unsigned* address = CPUARBD_BASE_ADDRESS;
    return *address;
}

/* write_CPUARBD
 *
 * Description: Sets the DSP Arbitration Control Register CPUARBD values, which manages the bandwidth of the DSP operations memory accesses made in L1D/L1P blocks. It applies to all the available DSPs
 *              Bits 16-18: Priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *              Bits 0-5: Maximum wait time in EMC cycles
 *
 * Parameter:
 *              - unsigned value: The new values of the CPUARBD register.
 *                See register values at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1645783090235 (Table 8-4 DSP Arbitration Control Register (CPUARBD, CPUARBU, CPUARBE))
 *
 * Returns:     Nothing
 *
 * */
void write_CPUARBD(int value){
    unsigned* address = CPUARBD_BASE_ADDRESS;
    *address = value & CPUARBE_MASK;
}

/* read_CPUARBU
 *
 * Description: Retrieves the DSP Arbitration Control Register CPUARBU values, which manages the bandwidth of the DSP operations memory accesses made in L2 blocks. It applies to all the available DSPs
 *              Bits 16-18: Priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *              Bits 0-5: Maximum wait time in EMC cycles
 *
 * Parameter:   None
 *
 *
 * Returns:     The register CPUARBU
 *
 * */
unsigned read_CPUARBU(){
    unsigned* address = CPUARBU_BASE_ADDRESS;
    return *address;
}

/* write_CPUARBU
 *
 * Description: Sets the DSP Arbitration Control Register CPUARBU values, which manages the bandwidth of the DSP operations memory accesses made in L2 blocks. It applies to all the available DSPs
 *              Bits 16-18: Priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *              Bits 0-5: Maximum wait time in EMC cycles
 *
 * Parameter:
 *              - unsigned value: The new values of the CPUARBD register.
 *                See register values at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1645783090235 (Table 8-4 DSP Arbitration Control Register (CPUARBD, CPUARBU, CPUARBE))
 *
 * Returns:     Nothing
 *
 * */
void write_CPUARBU(int value){
    unsigned* address = CPUARBU_BASE_ADDRESS;
    *address = value & CPUARBE_MASK;
}


/* read_MDMAARBU
 *
 * Description: Retrieves the Master DMA Arbitration Control Register MDMAARBU values, which manages controls the priority levels of MDMA requests going out of CorePac
 *              Bits 24-26: Urgent priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *              Bits 16-18: Normal priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register CPUARBD
 *
 * */
unsigned read_MDMAARBU(){
    unsigned* address = MDMAARBU_BASE_ADDRESS;
    return *address;
}

/* write_MDMAARBU
 *
 * Description: Sets the Master DMA Arbitration Control Register MDMAARBU values, which manages controls the priority levels of MDMA requests going out of CorePac
 *              Bits 24-26: Urgent priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *              Bits 16-18: Normal priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *
 * Parameter:
 *              - unsigned value: The new values of the MDMAARBU register.
 *                See register values at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1645783090235 (Table 8-8 Master DMA Arbitration Control Register (MDMAARBU) Field Descriptions)
 *
 * Returns:     Nothing
 *
 * */
void write_MDMAARBU(int value){
    unsigned* address = MDMAARBU_BASE_ADDRESS;
    *address = value & MDMAARBU_MASK;
}



/* read_SDMAARBD
 *
 * Description: Retrieves the slave DMA arbitration control register SDMAARBD values, which controls the bandwidth management of the slave DMA of the C66x CorePac for the L1D cache.
 *              Bits 0-5: Maximum wait time in EMC cycles (0x1 = 1 cycle wait, 0x2 = 2 cycles wait, 0x4 = 4 cycles wait, 0x8 = 8 cycle waits, 0x10 = 16 cycles wait, 0x20 = 32 cycle wait).
 *
 * Parameter:   None
 *
 *
 * Returns:     The register SDMAARBD
 *
 * */
unsigned read_SDMAARBD(){
    unsigned* address = SDMAARBD_BASE_ADDRESS;
    return *address;
}

/* write_SDMAARBD
 *
 * Description: Sets the slave DMA arbitration control register SDMAARBD values, which controls the bandwidth management of the slave DMA of the C66x CorePac for the L1D cache.
 *              Bits 0-5: Maximum wait time in EMC cycles (0x1 = 1 cycle wait, 0x2 = 2 cycles wait, 0x4 = 4 cycles wait, 0x8 = 8 cycle waits, 0x10 = 16 cycles wait, 0x20 = 32 cycle wait)
 *
 * Parameter:
 *              - unsigned value: The new wait time value for the slave DMA.
 *                See register at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1645783090235 (Table 8-7 Slave DMA Arbitration Control Register ((SDMAARBD, SDMAARBU, SDMARBE) Field Descriptions))
 *
 * Returns:     Nothing
 *
 * */
void write_SDMAARBD(int value){
    unsigned* address = SDMAARBD_BASE_ADDRESS;
    *address = value & SDMAARB_MASK;
}

/* read_SDMAARBU
 *
 * Description: Retrieves the slave DMA arbitration control register SDMAARBU values, which controls the bandwidth management of the slave DMA of the C66x CorePac for the L2 cache.
 *              Bits 0-5: Maximum wait time in EMC cycles (0x1 = 1 cycle wait, 0x2 = 2 cycles wait, 0x4 = 4 cycles wait, 0x8 = 8 cycle waits, 0x10 = 16 cycles wait, 0x20 = 32 cycle wait).
 *
 * Parameter:   None
 *
 *
 * Returns:     The register SDMAARBU
 *
 * */
unsigned read_SDMAARBU(){
    unsigned* address = SDMAARBU_BASE_ADDRESS;
    return *address;
}


/* write_SDMAARBU
 *
 * Description: Sets the slave DMA arbitration control register SDMAARBU values, which controls the bandwidth management of the slave DMA of the C66x CorePac for the L2 cache.
 *              Bits 0-5: Maximum wait time in EMC cycles (0x1 = 1 cycle wait, 0x2 = 2 cycles wait, 0x4 = 4 cycles wait, 0x8 = 8 cycle waits, 0x10 = 16 cycles wait, 0x20 = 32 cycle wait)
 *
 * Parameter:
 *              - unsigned value: The new wait time value for the slave DMA.
 *                See register at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1645783090235 (Table 8-7 Slave DMA Arbitration Control Register ((SDMAARBD, SDMAARBU, SDMARBE) Field Descriptions))
 *
 * Returns:     Nothing
 *
 * */
void write_SDMAARBU(int value){
    unsigned* address = SDMAARBU_BASE_ADDRESS;
    *address = value & SDMAARB_MASK;
}


/* read_SDMAARBE
 *
 * Description: Retrieves the slave DMA arbitration control register SDMAARBE values, which controls the bandwidth management of the slave DMA of the C66x CorePac for the EMC.
 *              Bits 0-5: Maximum wait time in EMC cycles (0x1 = 1 cycle wait, 0x2 = 2 cycles wait, 0x4 = 4 cycles wait, 0x8 = 8 cycle waits, 0x10 = 16 cycles wait, 0x20 = 32 cycle wait).
 *
 * Parameter:   None
 *
 *
 * Returns:     The register SDMAARBE
 *
 * */
unsigned read_SDMAARBE(){
    unsigned* address = SDMAARBE_BASE_ADDRESS;
    return *address;
}

/* write_SDMAARBE
 *
 * Description: Sets the slave DMA arbitration control register SDMAARBE values, which controls the bandwidth management of the slave DMA of the C66x CorePac for the EMC.
 *              Bits 0-5: Maximum wait time in EMC cycles (0x1 = 1 cycle wait, 0x2 = 2 cycles wait, 0x4 = 4 cycles wait, 0x8 = 8 cycle waits, 0x10 = 16 cycles wait, 0x20 = 32 cycle wait)
 *
 * Parameter:
 *              - unsigned value: The new wait time value for the slave DMA.
 *                See register at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1645783090235 (Table 8-7 Slave DMA Arbitration Control Register ((SDMAARBD, SDMAARBU, SDMARBE) Field Descriptions))
 *
 * Returns:     Nothing
 *
 * */
void write_SDMAARBE(int value){
    int* address = SDMAARBE_BASE_ADDRESS;
    *address = value & SDMAARB_MASK;
}


/* read_MDMAARBX
 *
 * Description: Retrieves the XMC MDMA Arbitration Control Register values, which controls the priority of the prefetches it generates from the C66x CorePac.
 *              Bits 16-18: Priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register MDMAARBX
 *
 * */
unsigned read_MDMAARBX(){
    unsigned* address = MDMAARBX_BASE_ADDRESS;
    return *address;
}

/* write_MDMAARBX
 *
 * Description: Sets the XMC MDMA Arbitration Control Register values, which controls the priority of the prefetches it generates from the C66x CorePac.
 *              Bits 16-18: Priority register field (0x7 = lowest priority, 0x0 = highest priority)
 *
 * Parameter:
 *              - unsigned value: The new priority value for the XMC MDMA.
 *                See register at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1645783090235 (Table 7-14 XMC MDMA Arbitration Control Register (MDMAARBX) Field Descriptions)
 *
 * Returns:     Nothing
 *
 * */
void write_MDMAARBX(int value){
    unsigned* address = MDMAARBX_BASE_ADDRESS;
    *address = value & SDMAARB_MASK;
}



