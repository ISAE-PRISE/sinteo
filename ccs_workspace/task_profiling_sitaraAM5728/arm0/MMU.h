/*--------------------------- MMU.h -------------------------------------
 |  File MMU.h
 |
 |  Description:  MMU set up functions
 |  Version: 1.1V
 *-----------------------------------------------------------------------*/

#define PMSELR_MASK  0xFFFFFFE0
#define PMXEVTYPER_MASK  0xFFFFFF00
#define PMCNTENSET_MASK  0x7FFFFFC0
#define PMCR_MASK  0xFFFFFFC0
#define PMOVSR_MASK  0x7FFFFFC0
#define CSSELR  0xFFFFFFF0


/* disable_L1D_cache
 *
 * Description: Disables the L1 data cache
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void disable_L1D_cache(){
    // Disable L1 Caches
    __asm__ __volatile("MRC    P15, 0, R1, C1, C0, 0 \n\t"
                       "BIC    R1,   R1, #(0x1 << 2)  \n\t"
                       "MCR    P15, 0, R1, C1, C0, 0 \n\t"
    );

    // Invalidate Data cache to  create general-purpose code. Calculate the
    // cache size first and loop through each set + way

    __asm__ __volatile("MOV    R0, #0x0 \n\t"
                       "MCR    P15, 2, R0, C0, C0, 0 \n\t"
                       "MRC    P15, 1, R4, C0, C0, 0  \n\t"
                       "AND    R1, R4, #0x7 \n\t"
                       "ADD    R1, R1, #0x4 \n\t"
                       "LDR    R3, =0x7FFF  \n\t"
                       "AND    R2, R3, R4, LSR   #13 \n\t"
                       "LDR    R3, =0x3FF \n\t"
                       "AND    R3, R3, R4, LSR #3 \n\t"
                       "CLZ    R4, R3   \n\t"
        );

    __asm__ __volatile("MOV    R5, #0 \n\t"
                       "way_loop: \n\t"
                       "MOV    R6, #0   \n\t"
                       "set_loop: \n\t"
                       "ORR    R7, R0, R5, LSL R4 \n\t"
                       "ORR    R7, R7,  R6, LSL R1 \n\t"
                       "MCR    P15, 0, R7, C7, C6, 2  \n\t"
                       "ADD    R6, R6, #1 \n\t"
                       "CMP    R6, R2 \n\t"
                       "BLE    set_loop \n\t"
                       "ADD    R5, R5, #1 \n\t"
                       "CMP    R5, R3  \n\t"
                       "BLE    way_loop \n\t"
            );

}

/* disable_L1I_cache
 *
 * Description: Disables the L1 instruction cache
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void disable_L1I_cache(){
    // Disable L1 Caches.
    __asm__ __volatile("MRC    P15, 0, R1, C1, C0, 0 \n\t"
                       "BIC    R1,   R1, #(0x1 << 12)  \n\t"
                       "MCR    P15, 0, R1, C1, C0, 0 \n\t"
        );

    __asm__ __volatile("MOV r1, #0 \n\t"
                      " MCR p15, #0, r1, c7, c5, #0  \n\t"
        );
    __asm__ __volatile("MOV    R0, #0x1 \n\t"
                           "MCR    P15, 2, R0, C0, C0, 0 \n\t"
                           "MRC    P15, 1, R4, C0, C0, 0  \n\t"
                           "AND    R1, R4, #0x7 \n\t"
                           "ADD    R1, R1, #0x4 \n\t"
                           "LDR    R3, =0x7FFF  \n\t"
                           "AND    R2, R3, R4, LSR   #13 \n\t"
                           "LDR    R3, =0x3FF \n\t"
                           "AND    R3, R3, R4, LSR #3 \n\t"
                           "CLZ    R4, R3   \n\t"
            );

        __asm__ __volatile("MOV    R5, #0 \n\t"
                           "way_loop2: \n\t"
                           "MOV    R6, #0   \n\t"
                           "set_loop2: \n\t"
                           "ORR    R7, R0, R5, LSL R4 \n\t"
                           "ORR    R7, R7,  R6, LSL R1 \n\t"
                           "MCR    P15, 0, R7, C7, C6, 2  \n\t"
                           "ADD    R6, R6, #1 \n\t"
                           "CMP    R6, R2 \n\t"
                           "BLE    set_loop2 \n\t"
                           "ADD    R5, R5, #1 \n\t"
                           "CMP    R5, R3  \n\t"
                           "BLE    way_loop2 \n\t"
                );

}


/* disable_L2_cache
 *
 * Description: Disables the L2 cache
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void disable_L2_cache(){
    // Disable L1 Caches.
    __asm__ __volatile("MRC    P15, 0, R1, C1, C0, 0 \n\t"
                       "BIC    R1,   R1, #(0x1 << 2)  \n\t"
                       "MCR    P15, 0, R1, C1, C0, 0 \n\t"
    );

    // Invalidate Data cache to  create general-purpose code. Calculate the
    // cache size first and loop through each set + way
    __asm__ __volatile("MOV    R0, #0x2 \n\t"
                       "MCR    P15, 2, R0, C0, C0, 0 \n\t"
                       "MRC    P15, 1, R4, C0, C0, 0  \n\t"
                       "AND    R1, R4, #0x7 \n\t"
                       "ADD    R1, R1, #0x4 \n\t"
                       "LDR    R3, =0x7FFF  \n\t"
                       "AND    R2, R3, R4, LSR   #13 \n\t"
                       "LDR    R3, =0x3FF \n\t"
                       "AND    R3, R3, R4, LSR #3 \n\t"
                       "CLZ    R4, R3   \n\t"
        );

    __asm__ __volatile("MOV    R5, #0 \n\t"
                       "way_loop3: \n\t"
                       "MOV    R6, #0   \n\t"
                       "set_loop3: \n\t"
                       "ORR    R7, R0, R5, LSL R4 \n\t"
                       "ORR    R7, R7,  R6, LSL R1 \n\t"
                       "MCR    P15, 0, R7, C7, C6, 2  \n\t"
                       "ADD    R6, R6, #1 \n\t"
                       "CMP    R6, R2 \n\t"
                       "BLE    set_loop3 \n\t"
                       "ADD    R5, R5, #1 \n\t"
                       "CMP    R5, R3  \n\t"
                       "BLE    way_loop3 \n\t"
            );
}



/* read_system_control
 *
 * Description: Reads the register System Control Register (SCTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned
 *
 * */
static inline unsigned int read_system_control()  {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 0, %0, c1, c0, 0 \t\n": "=r"(value));
   return value;
}


/* enable_caches
 *
 * Description: Modifies the instruction and data caches value in the register System Control Register (SCTLR)
 *
 * Parameter:
 *              - unsigned int instr_cache: Indicates whether or not the instructions cache is used. 1 = enable, else = disable
 *              - unsigned int data_cache: Indicates whether or not the data caches are used. 1 = enable, else = disable
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_caches(unsigned int instr_cache, unsigned int data_cache)  {
      unsigned int value=read_system_control();

      if(data_cache == 1)
          __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value | (1<<2))));
      else
          __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value & ~(1<<2))));

      value=read_system_control();

      if(instr_cache == 1)
          __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value | (1<<12))));
      else
          __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value & ~(1<<12))));
}



/* enable_branch_prediction
 *
 * Description: Enables the branch prediction by modifying the register System Control Register (SCTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_branch_prediction()  {
      unsigned int value=read_system_control();
      __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value | (1<<11))));

}


/* enable_SWP_SWPB
 *
 * Description: Enables the SWP_SWPB operators by modifying the register System Control Register (SCTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_SWP_SWPB() {
    unsigned int value=read_system_control();
    __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value | (1<<10))));
}

/* enable_alignment
 *
 * Description: Enables the alignment error check by modifying the register System Control Register (SCTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_alignment() {
    unsigned int value=read_system_control();
    __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value | (1<<1))));
}

/* enable_MMU
 *
 * Description: Enables the MMU bit by modifying the register System Control Register (SCTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_MMU() {
    unsigned int value=read_system_control();
    __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value | 1)));
}

/* enable_AFE
 *
 * Description: Enables the AFE bit by modifying the register System Control Register (SCTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_AFE() {
    unsigned int value=read_system_control();
    __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value | (1<<29))));
}

/* enable_TRE
 *
 * Description: Enables the TRE bit by modifying the register System Control Register (SCTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_TRE() {
    unsigned int value=read_system_control();
    __asm__ __volatile("MCR p15, 0, %0, c1, c0, 0" :: "r"((value | (1<<28))));
}



/* read_cache_size_ID
 *
 * Description: Reads the Cache Size ID Register (CCSIDR)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned
 *
 * */
static inline unsigned int read_cache_size_ID()  {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 1, %0, c0, c0, 0 \t\n": "=r"(value));
   return value;
}


/* read_cache_size
 *
 * Description: Reads the Cache Size Selection Register (CSSELR)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned
 *
 * */
static inline unsigned int read_cache_size()  {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 2, %0, c0, c0, 0 \t\n": "=r"(value));
   return value;
}

/* write_cache_size
 *
 * Description: Writes the unreserved bits (4) of the Cache Size Selection Register (CSSELR)
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void write_cache_size(unsigned int write)  {
      unsigned int value=read_cache_size();
      __asm__ __volatile("MCR p15, 2, %0, c0, c0, 0" :: "r"(((value & CSSELR) | write)));
}


/* read_auxiliary_control
 *
 * Description: Reads the Auxiliary Control Register (ACTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned
 *
 * */
static inline unsigned int read_auxiliary_control(){
    unsigned int value=0;
    __asm__ __volatile("MRC p15, 0, %0, c1, c0, 1 \t\n": "=r"(value));
    return value;
}


/* read_auxiliary_controlL2
 *
 * Description: Reads the Auxiliary Control Register (L2ACTLR)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned
 *
 * */
static inline unsigned int read_auxiliary_controlL2(){
    unsigned int value=0;
    __asm__ __volatile("MRC p15, 1, %0, c15, c0, 0 \t\n": "=r"(value));
    return value;
}

/* enable_L2EN
 *
 * Description: Enables the L2EN bit in the Auxiliary Control Register (L2ACTLR). Decapricated in ARM15 oldest versions
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_L2EN()  {
      unsigned int value=read_auxiliary_controlL2();
      __asm__ __volatile("MCR p15, 1, %0, c15, c0, 0" :: "r"(value | (1<<26)));


}

/* enable_SMP
 *
 * Description: Enables the SMP bit in the Auxiliary Control Register (ACTLR). Revision: r2p1
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_SMP()  {
      unsigned int value=read_auxiliary_control();
      __asm__ __volatile("MCR p15, 0, %0, c1, c0, 1" :: "r"((value | (1<<6))));
}


/* read_TTBR0
 *
 * Description: Reads the Translation Table Base Register (TTBR0)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned
 *
 * */
static inline unsigned int read_TTBR0(){
    unsigned int value=0;
    __asm__ __volatile("MRC p15, 0, %0, c2, c0, 0 \t\n": "=r"(value));
    return value;
}


/* write_TTBR0
 *
 * Description: Writes on the Translation Table Base Register (TTBR0)
 *              Revision: r2p1
 *              The processor does not use any implementation-defined bits in the 32-bit TTBR0 and TTBR1 format, so these bits are UNK/SBZP.
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void write_TTBR0(unsigned int write)  {
      __asm__ __volatile("MCR p15, 0, %0, c2, c0, 0" :: "r"((write)));
}


/* read_TTBCR
 *
 * Description: Reads the Translation Table Base Control Register (TTBCR)
 *              Revision: r2p1
 *              The processor does not use any implementation-defined bits when using the Long-descriptor translation table format, so these bits are UNK/SBZP.
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned
 *
 * */
static inline unsigned int read_TTBCR(){
    unsigned int value=0;
    __asm__ __volatile("MRC p15, 0, %0, c2, c0, 2 \t\n": "=r"(value));
    return value;
}

/* write_TTBCR
 *
 * Description: Writes the Translation Table Base Control Register (TTBCR)
 *              Revision: r2p1
 *              The processor does not use any implementation-defined bits when using the Long-descriptor translation table format, so these bits are UNK/SBZP.
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void write_TTBCR(unsigned int write)  {
      unsigned int value=read_TTBCR();
      __asm__ __volatile("MCR p15, 0, %0, c2, c0, 2" :: "r"((value | write)));
}


/* read_DACS
 *
 * Description: Reads the Domain Access Control Register (DACS)
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned
 *
 * */
static inline unsigned int read_DACS(){
    unsigned int value=0;
    __asm__ __volatile("MRC p15, 0, %0, c3, c0, 0 \t\n": "=r"(value));
    return value;
}

/* write_DACS
 *
 * Description: Writes the Domain Access Control Register (DACR)
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
static inline void write_DACR(unsigned int write)  {
      __asm__ __volatile("MCR p15, 0, %0, c3, c0, 0 \t\n" :: "r"((write)));
}

/* read_FCSE
 *
 * Description: Reads the FCSE Register (FCSE).
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned (ARM15 r2p4)
 *
 * */
static inline unsigned int read_FCSE(){
    unsigned int value=0;
    __asm__ __volatile("MRC p15, 0, %0, c13, c0, 0 \t\n": "=r"(value));
    return value;
}


/* read_TTBCR
 *
 * Description: Reads the Main ID Register (MIDR).
 *
 * Parameter:   None
 *
 *
 * Returns:     The register value is returned (ARM15 r2p4)
 *
 * */
static inline unsigned int read_MIDR(){
    unsigned int value=0;
    __asm__ __volatile("MRC p15, 0, %0, c0, c0, 0 \t\n": "=r"(value));
    return value;
}

