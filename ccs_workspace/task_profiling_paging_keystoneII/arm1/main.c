/*************************************************************************
 * SINTEO project
 * Copyright (C) 2022 ISAE-SUPAERO / ONERA
*************************************************************************/

/*--------------------------- main.c -------------------------------------
 | File main.c
 |
 | Description:  The core is set up for causing interference
 |               and see the response of arm0 to them
 |
 | Version: 1.0
 |
 | Contact:
 | alfonso.mascarenas-gonzalez@isae-supaero.fr
 | jean-baptiste.chaudron@isae-supaero.fr
 | youcef.bouchebaba@onera.fr
 | frederic.boniol@onera.fr
 | jean-loup.bussenot@onera.fr
 *-----------------------------------------------------------------------*/


/* ------------------------- FILE INCLUSION -------------------------- */
#include <stdio.h>
#include "../arm0/benchmarks.h"
#include "../arm0/MMU.h"
#include "../arm0/PMH.h"
#include "../arm0/MSMC.h"


/* ----------------------- LOCAL FUNCTIONS --------------------------- */
void ARM_disable_caches();
static inline void ARM_init(unsigned page_level1_descriptor_addr);
static inline void paging_setup(unsigned page_option, unsigned page_level1_descriptor_addr);
void page_coloring(unsigned page_level1_descriptor_addr, unsigned page_level2_descriptor_addr, unsigned nb_partition_bits, unsigned initial_partition_position_bit, unsigned selected_partition_bit_id);


/* --------------- GLOBAL VARIABLES DEFINITIONS --------------- */

// ARM configuration mode. 0 = only L1 instruction cache, 1 = all caches plus others (MMU, branch predictor...)
#define ARM_INIT_CONFIGURATION   1


/* ========================================================================== */
/*                   Internal Function Declarations                           */
/* ========================================================================== */

int main(void)
{
    // Disable caches for a safe cache set up
    ARM_disable_caches();

    // Configure ARM
    if(ARM_INIT_CONFIGURATION == 1)
        ARM_init(0xD8000000);
    else if(ARM_INIT_CONFIGURATION == 0)
        enable_caches(1,0);


    unsigned const MATRIX_SIZE = 512;

    // Produce memory interference endlessly
    while(1){
        matrix_stress2_task(MATRIX_SIZE);

    }


}


/* ARM_disable_caches
 *
 * Description: Disables the L1I, L1D, L2 and invalidates the TLB
 *
 * Parameter: None
 *
 * Returns:     Nothing
 *
 * */
void ARM_disable_caches(){
    //    printf("Invalidating L1D... \n");
        disable_L1D_cache();
    //    printf("Flushing L1I... \n");
        disable_L1I_cache();
    //    printf("Invalidating L2... \n");
        disable_L2_cache();
    //    printf("Invalidating TLB... \n");
        __asm__ __volatile("MCR p15, 0, r1, c8, c7, 0 \n\t");
}

/* ARM_init
 *
 * Description: Configures the ARM core following features:
 *              - Pages granularity
 *              - Caches
 *              - MMU
 *              - Branch predictor
 *
 * Parameter:
 *              - unsigned page_level1_descriptor_addr: Indicates the physical address where the pages are written
 *
 *
 * Returns:     Nothing
 *
 * */
static inline void ARM_init(unsigned page_level1_descriptor_addr){

    // Configures the pages size (0 = 16 MB page, 1 = 1 MB page, 2 = 64 KB, 3 = 4 KB page, 4 = 4 KB page with cache/bank partitioning)
    // Currently, the link script is configured for partitioned mode. Do modify the link script (.lds) if configuration 0 to 3 are used.
    paging_setup(4, page_level1_descriptor_addr);

   // TTBR0, address must be equal to page_level1_descriptor_addr, which is where we have written the pages
   __asm__ __volatile("MOV r1,#0x0 \n\t"
                      "MCR p15, 0, r1, c2, c0, 2 \n\t"
                      "MCR p15, 0, %[input_i], c2, c0, 0 \n\t"
                       :: [input_i] "r" (page_level1_descriptor_addr)
                       );


   //    printf("Enabling D prefetching... \n");
   __asm__ __volatile("MRC p15, 0, r1, c1, c0, 1 \n\t"
                      "ORR r1, r1, #(0x1 <<2)   \n\t"
                      "MCR p15, 0, r1, c1, c0, 1 \n\t"
                      "DSB \n\t"
                      "ISB \n\t"
                       );

    write_DACR(0x55555555);
    enable_SMP();

//    printf("Enabling MMU...  \n");
    __asm__ __volatile("isb");
    enable_MMU();

//    printf("Enabling Caches...  \n");
    enable_caches(1,1);

//    printf("Enabling Branch Predictor...  \n");
    enable_branch_prediction();


}


/* TLB_setup
 *
 * Description: Configures the pages according to the selected page granularity.
 *              The pages for the DDR memory are configured to follow the write-back and write-allocate cache policy (i.e., TEX bits = 101 and C and B bits = 0 and 1 respectively). The rest are set to uncacheable.
 *
 * Reference: https://developer.arm.com/documentation/ddi0406/c/System-Level-Architecture/Virtual-Memory-System-Architecture--VMSA-/Short-descriptor-translation-table-format/Short-descriptor-translation-table-format-descriptors?lang=en
 *
 * Parameter:
 *              - unsigned int page_option: Page option which selects the page granularity (0 = 16 MB page, 1 = 1 MB page, 2 = 64 KB, 3 = 4 KB page, 4 = 4 KB page with cache/bank partitioning)
 *              - unsigned int page_level1_descriptor_addr: Physical address where the first-level descriptor pages are located
 *
 * Returns:     Nothing
 *
 * */
static inline void paging_setup(unsigned page_option, unsigned page_level1_descriptor_addr){
    unsigned int* reg;
    unsigned int page_level2_descriptor_addr = page_level1_descriptor_addr + 0x1000;

    // 16 MB page
    if(page_option == 0){
        // From  0x0 to 0x7FFFFFFF
        for(int cnt = 0; cnt < 127; cnt++){
            // Supersection descriptor must: (1) occur first on a sixteen-word boundary and (2) be repeated in 16 consecutive memory locations
            for(int i=0; i<16;i++){
                reg = (unsigned*)(page_level1_descriptor_addr + (cnt<<6) + (i<<2));
                *reg = 0x044C02|(cnt<<24);
            }
        }

        // From  0x80000000 to 0xFFFFFFFF (DDR SDRAM)
        for(int cnt = 127; cnt <= 255; cnt++){
            // Supersection descriptor must: (1) occur first on a sixteen-word boundary and (2) be repeated in 16 consecutive memory locations
            for(int i=0; i<16;i++){
                reg = (unsigned*)(page_level1_descriptor_addr + (cnt<<6) + (i<<2));
                *reg = 0x047C06|(cnt<<24);
            }
        }

    }
    // 1 MB page
    else if(page_option == 1){
        // From  0x0 to 0x7FFFFFFF
        for(int cnt = 0; cnt < 2048; cnt++){
            reg = (unsigned*)(page_level1_descriptor_addr + (cnt<<2));
            *reg = 0x014DE2|(cnt<<20);
        }
        // From  0x80000000 to 0xFFFFFFFF (DDR SDRAM)
        for(int cnt = 2048; cnt <= 4091; cnt++){
            reg = (unsigned*)(page_level1_descriptor_addr + (cnt<<2));
            *reg = 0x015DE6|(cnt<<20);
        }
    }
    // 64 KB page
    else if(page_option == 2){
        // Coarse table splits 1MB into 256 entries with 4KB each
        for(int cnt = 0; cnt <= 4091; cnt++){
            reg = (unsigned*)(page_level1_descriptor_addr + (cnt<<2));
            *reg = 0x00E1|(page_level2_descriptor_addr + (cnt<<10));  // 2nd TLB with space of 1KB between addresses

            // From  0x0 to 0x7FFFFFFF
            if(cnt < 2048){
                for(int c = 0; c <= 15; c++){
                    //  Large page descriptors must be repeated in 16 consecutive entries.
                    for(int i = 0; i <= 15; i++){
                        reg = (unsigned*)(page_level2_descriptor_addr + (cnt<<10) + (c<<6) + (i<<2));
                        *reg = 0x0004431|((cnt<<20) + (c<<16)); // c<<16 covers 64KB
                    }
                }
            }
            // From  0x80000000 to 0xFFFFFFFF (DDR SDRAM)
            else{
                for(int c = 0; c <= 15; c++){
                    //  Large page descriptors must be repeated in 16 consecutive entries.
                    for(int i = 0; i <= 15; i++){
                        reg = (unsigned*)(page_level2_descriptor_addr + (cnt<<10) + (c<<6) + (i<<2));
                        *reg = 0x0005435|((cnt<<20) + (c<<16)); // c<<16 covers 64KB
                    }
                }
            }

        }

    }
    // 4 KB page
    else if(page_option == 3){
        for(int cnt = 0; cnt <= 4091; cnt++){
            reg = (unsigned*)(page_level1_descriptor_addr + (cnt<<2));
            *reg = 0x0E1|(page_level2_descriptor_addr + (cnt<<10));  // 2nd TLB with space of 1KB between addresses

            // From  0x0 to 0x7FFFFFFF
            if(cnt < 2048){
                for(int c = 0; c <= 255; c++){
                    reg = (unsigned*)(page_level2_descriptor_addr + (cnt<<10) + (c<<2));
                    *reg = 0x532|((cnt<<20) + (c<<12)); // c<<12 covers 4KB
                }
            }
            // From  0x80000000 to 0xFFFFFFFF (DDR SDRAM)
            else{
                for(int c = 0; c <= 255; c++){
                    reg = (unsigned*)(page_level2_descriptor_addr + (cnt<<10) + (c<<2));
                    *reg = 0x576|((cnt<<20) + (c<<12)); // c<<12 covers 4KB
                }
            }

        }

    }

    // 4 KB page partitioned
    else if(page_option == 4){
        const unsigned NB_PARTITION_BITS = 2;
        const unsigned INITIAL_PARTITION_BIT = 14;
        const unsigned SELECTED_PARTITION_BIT_ID = 1;

        page_coloring(page_level1_descriptor_addr, page_level2_descriptor_addr, NB_PARTITION_BITS, INITIAL_PARTITION_BIT, SELECTED_PARTITION_BIT_ID);

    }


}



/* page_coloring
 *
 * Description: Performs physical address partitioning for contiguous bits (i.e., the function does not support separated bits partitioning). 4KB pages are used.
 *
 * Parameter:
 *              - unsigned page_level1_descriptor_addr: Indicates the base physical address where the ARMv7 coarse page (first level descriptor) table is located
 *              - unsigned page_level2_descriptor_addr: Indicates the base physical address where the ARMv7 second-level descriptor table is located
 *              - unsigned nb_partition_bits: Number of bits used for partitioning, e.g. 1 (only one bit is used meaning 2 colors), 3 (8 colors/partitions)
 *              - unsigned initial_partition_position_bit: Bit position where the partition starts, e.g. 16 (L2 cache partition),  13 (L2 cache and SDRAM bank partition)
 *              - unsigned selected_partition_bit_id: The bit used for this program partition, e.g. 0x1 (second bit), 0x0 (first bit)
 *
 * Returns:     Nothing
 *
 * */
void page_coloring(unsigned page_level1_descriptor_addr, unsigned page_level2_descriptor_addr, unsigned nb_partition_bits, unsigned initial_partition_position_bit, unsigned selected_partition_bit_id){

    const unsigned DDR_MEMORY_PARTITIONED_SPACE_BASE_ADDRESS_MB = 2048; // Memory starting space address where the partitioning is to be applied
    const unsigned DDR_MEMORY_NOT_PARTITIONED_SPACE_BASE_ADDRESS_MB = 3072; // Memory starting space address free of partitioning. This memory space is needed for placing the initial data and instructions and avoid page faults.
    const unsigned TOTAL_MEMORY_MB = 4096; // Total physical address space size where the DDR memory goes from 2048 to 4096

    const unsigned PAGE_SHIFT = 12; // 4KB page offset
    const unsigned USED_DDR_BANKS_NUM = (unsigned)(1 << nb_partition_bits); // Total bank partitions. Only one is used for this core. 2^(nb_partition_bits)

    unsigned int* reg;
    unsigned bank_addr = 0;
    unsigned lower_bits = 0;


    for(int cnt = 0; cnt <= TOTAL_MEMORY_MB; cnt++){
        reg = (unsigned*)(page_level1_descriptor_addr + (cnt<<2));
        *reg = 0x0E1|(page_level2_descriptor_addr + (cnt<<10));

        // Non SDRAM addresses are set to uncacheable
        if(cnt < DDR_MEMORY_PARTITIONED_SPACE_BASE_ADDRESS_MB){
            for(int c = 0; c <= 255; c++){
                reg = (unsigned*)(page_level2_descriptor_addr + (cnt<<10) + (c<<2));
                *reg = 0x532|((cnt<<20) + (c<<PAGE_SHIFT)); // c<<12 covers 4KB
            }
        }
        // The region of the DDR memory where partitioning is performed
        else if (cnt < (DDR_MEMORY_PARTITIONED_SPACE_BASE_ADDRESS_MB + ((DDR_MEMORY_NOT_PARTITIONED_SPACE_BASE_ADDRESS_MB-DDR_MEMORY_PARTITIONED_SPACE_BASE_ADDRESS_MB)/USED_DDR_BANKS_NUM))){
            for(int c = 0; c <= 255; c++){
                reg =(unsigned*)(page_level2_descriptor_addr + (cnt<<10) + (c<<2)); // Virtual Address
                *reg = (0x576)|((DDR_MEMORY_PARTITIONED_SPACE_BASE_ADDRESS_MB<<20) + // Starting physical address
                                (bank_addr<<(initial_partition_position_bit+nb_partition_bits)) + // Upper bits w.r.t. partitioning bits
                                (selected_partition_bit_id<<initial_partition_position_bit) +   // Bits that indicate the partition (this is fixed)
                                (lower_bits<<(PAGE_SHIFT))); // Space between the end of the page size (4KB) and the beginning of the partitioning bits (initial_partition_position_bit)

                // Keep track of the times we have used the bits below the ones used for partitioning
                lower_bits++;
                // We do the modulo so that we don't get into the partitioning bits when these are reached. Therefore staying in the lower bits all the time
                lower_bits = lower_bits%((unsigned)(1 << ( initial_partition_position_bit-(PAGE_SHIFT) ) ));
                // Keep track of the times we have reached the partitioning bits
                if (lower_bits == 0)
                    bank_addr++;
            }

        }
        // The region of the DDR memory where free of partitioning
        else if(cnt >= DDR_MEMORY_NOT_PARTITIONED_SPACE_BASE_ADDRESS_MB){
            for(int c = 0; c <= 255; c++){
                reg = (unsigned*)(page_level2_descriptor_addr + (cnt<<10) + (c<<2));
                *reg = 0x576|((cnt<<20) + (c<<PAGE_SHIFT));
            }
        }
        else{
            for(int c = 0; c <= 255; c++){
                reg = (unsigned*)(page_level2_descriptor_addr + (cnt<<10) + (c<<2));
                *reg = 0x532; // c<<12 covers 4KB
            }

        }

    }


}





