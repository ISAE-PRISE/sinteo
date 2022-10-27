/*--------------------------- DDR3MemoryController.c ---------------------
 |  File DDR3MemoryController.h
 |
 |  Description: This file provides the definition of functions for
 |  managing the EMIFs on Keystone II TCI6636K2H
 |
 |  Version: 2.1
 *-----------------------------------------------------------------------*/

#include "DDR3MemoryController.h"


/* get_PERF_CNT_1
 *
 * Description: Retrieves the first performance counter value
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
unsigned get_PERF_CNT_1(){
    unsigned int* PERF_CNT_1 = (unsigned*)(DDR3A_EMIF_CONFIGURATION + PERF_CNT_1_OFFSET);
    return *PERF_CNT_1;
}

/* get_PERF_CNT_2
 *
 * Description: Retrieves the second performance counter value
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
unsigned get_PERF_CNT_2(){
    unsigned int* PERF_CNT_2 = (unsigned*)(DDR3A_EMIF_CONFIGURATION + PERF_CNT_2_OFFSET);
    return *PERF_CNT_2;
}

/* get_PERF_CNT_TIMER
 *
 * Description: Retrieves the dedicated timer counter value
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
unsigned get_PERF_CNT_TIMER(){
    unsigned int* PERF_CNT_TIMER = (unsigned*)(DDR3A_EMIF_CONFIGURATION + PERF_CNT_TIM_OFFSET);
    return *PERF_CNT_TIMER;
}


/* set_PERF_CNT_EVENT
 *
 * Description: Sets the event to study for the chosen performance counter
 *
 * PERF_CNT_CFG.[CNTR_CFG]    Event Selected for counting   PERF_CNT_CFG.[CTNR_REGION_EN]   PERF_CNT_CFG.[CNTR_MSTID_EN]
 * 0x0                          Total SDRAM accesses             NA                         0 - Disable, 1 - Enable
 * 0x1                          Total SDRAM activates            NA                         0 - Disable, 1 - Enable
 * 0x2                          Total Reads                      0 - Disable, 1 - Enable    0 - Disable, 1 - Enable
 *
 * See more at: https://www.ti.com/lit/ug/spruhz6l/spruhz6l.pdf (Table 2-12. Performance Counter Filter Configuration)
 *
 * Parameter:
 *              - unsigned id: Performance counter to select (0 for first counter, 1 for second counter)
 *              - unsigned event: Event to study
 *
 * Returns:     Nothing
 *
 * */
void set_PERF_CNT_EVENT(unsigned id, unsigned event){
    unsigned int* PERF_CNT_CFG = (unsigned*)(DDR3A_EMIF_CONFIGURATION + PERF_CNT_CFG_OFFSET);

    if(id == 0){
        *PERF_CNT_CFG &= 0xFFFFFFF0; // Clear CNTR1_CFG bits
        *PERF_CNT_CFG |= (event<<0); // Set CNTR1_CFG bits
    }
    else if(id == 1){
        *PERF_CNT_CFG &= 0xFFF0FFFF; // Clear CNTR2_CFG bits
        *PERF_CNT_CFG |= (event<<16); // Set CNTR2_CFG bits
    }

}


/* enable_CNT_MSTID
 *
 * Description: Enable the use of filters for a performance counter
 *
 *
 * Parameter:
 *              - unsigned id: Performance counter to select (0 for first counter, 1 for second counter)
 *
 * Returns:     Nothing
 *
 * */
void enable_CNT_MSTID(unsigned id){
    unsigned int* PERF_CNT_CFG = (unsigned*)(DDR3A_EMIF_CONFIGURATION + PERF_CNT_CFG_OFFSET);

    if(id == 0)
        *PERF_CNT_CFG |= (1<<15); // Set CNTR1_CFG bits
    else if(id == 1)
        *PERF_CNT_CFG |= (1<<31); // Set CNTR2_CFG bits
}



/* set_MSTID
 *
 * Description: Sets the master to be considered by the chosen performance counter
 *
 * Reference: https://www.ti.com/lit/ug/spruhn7c/spruhn7c.pdf?ts=1646756863389&ref_url=https%253A%252F%252Fwww.google.com%252F (Table 2-12. Performance Counter Filter Configuration)
 *            https://www.ti.com/lit/ds/symlink/66ak2h06.pdf?ts=1663928051848&ref_url=https%253A%252F%252Fwww.google.com%252F (Table 8-6. Master ID Settings)
 *
 * Master Id    Entity
 * 0            C66x Core Pac0 Data
 * 1            C66x Core Pac1 Data
 * 2            C66x Core Pac2 Data
 * 3            C66x Core Pac3 Data
 * 4            C66x Core Pac4 Data
 * 5            C66x Core Pac5 Data
 * 6            C66x Core Pac6 Data
 * 7            C66x Core Pac7 Data
 * 8            ARM Core Pac0
 *
 * Parameter:
 *              - unsigned id: Performance counter to select (0 for first counter, 1 for second counter)
 *              - unsigned master_id: Id of the master to focus on
 *
 * Returns:     Nothing
 *
 * */
void set_MSTID(unsigned id, unsigned master_id){
    unsigned int* PERF_CNT_SEL = (unsigned*)(DDR3A_EMIF_CONFIGURATION + PERF_CNT_SEL_OFFSET);

    if(id == 0)
        *PERF_CNT_SEL |= (master_id<<8); // Set MSTID1 bits
    else if(id == 1)
        *PERF_CNT_SEL |= (master_id<<24); // Set MSTID2 bits
}


/* set_DDR3A_SDCFG_IBANK
 *
 * Description: Sets the number of SDRAM banks to use by the controller
 *
 * Caveats: It is better to use GEL configuration file to set this feature to avoid issues
 *
 *
 * Parameter:
 *              - unsigned banks_number: Value for setting the number of banks (0 = 1 bank, 1 = 2 banks, 2 = 4 banks, 3 = 8 banks)
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_SDCFG_IBANK(unsigned banks_number){
    unsigned int* SDCFG = (unsigned*)(DDR3A_EMIF_CONFIGURATION + SDCFG_OFFSET);
    *SDCFG &= 0xFFFFFF9F; // Clear IBANK bits
    *SDCFG |= (banks_number<<5); // Set IBANK bits
}


/* get_DDR3A_SDCFG_IBANK
 *
 * Description: Retrieves the number of banks in use by the controller
 *
 *
 * Parameter:   None
 *
 * Returns:     The number of banks used
 *
 * */
unsigned get_DDR3A_SDCFG_IBANK(){
    unsigned int* SDCFG = (unsigned*)(DDR3A_EMIF_CONFIGURATION + SDCFG_OFFSET);
    return *SDCFG & 0x060; // Clear all bits but IBANK bits
}

/* get_DDR3A_SDCFG_PAGESIZE
 *
 * Description: Retrieves the page size used by the controller
 *
 *
 * Parameter:   None
 *
 * Returns:     The number the page size (0 = 256-word page, 1 = 512-word page, 2 = 1024-word page, 3 = 2048-word page)
 *
 * */
unsigned get_DDR3A_SDCFG_PAGESIZE(){
    unsigned int* SDCFG = (unsigned*)(DDR3A_EMIF_CONFIGURATION + SDCFG_OFFSET);
    return *SDCFG & 0x003; // Clear all bits but PAGESIZE bits
}

/* set_DDR3A_SDCFG_EBANK
 *
 * Description: Defines the number of chip select lines in use
 *
 * Caveats: It is better to use GEL configuration file to set this feature to avoid issues
 *
 * Parameter:
 *              - unsigned chips_number: Value for setting the number of chips (0 = 1 chip, 1 = 2 chips)
 *              - unsigned emif_id: Indicates the EMIF to choose (0 or 1)
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_SDCFG_EBANK(int chips_number, unsigned emif_id){
    unsigned int* SDCFG = (unsigned*)(DDR3A_EMIF_CONFIGURATION + SDCFG_OFFSET);
    *SDCFG &= 0xFFFFFFF7; // Clear EBANK bits
    *SDCFG |= (chips_number<<3); // Set EBANK bits
}


/* get_DDR3A_SDCFG_EBANK
 *
 * Description: Retrieves the number of chip select lines in use
 *
 *
 * Parameter:   None
 *
 * Returns:     The number of chips used
 *
 * */
unsigned get_DDR3A_SDCFG_EBANK(){
    unsigned int* SDCFG = (unsigned*)(DDR3A_EMIF_CONFIGURATION + SDCFG_OFFSET);
    return *SDCFG & 0x08; // Clear all bits but EBANK bits
}


/* set_DDR3A_PR_OLD_COUNT
 *
 * Description: Sets the priority elevation count (starvation mechanism triggering count)
 *
 *
 * Parameter:
 *              - unsigned count: Priority raise old counter (max value is 0xFF)
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_PR_OLD_COUNT(unsigned count){
    unsigned int* LAT_CONFIG = (unsigned*)(DDR3A_EMIF_CONFIGURATION + LAT_CONFIG_OFFSET);
    *LAT_CONFIG &= 0xFFFFFF00; // Clear PR_OLD_COUNT bits
    *LAT_CONFIG |= (count); // Set PR_OLD_COUNT bits
}

/* set_DDR3A_READ_EXECUTION_THRESHOLD
 *
 * Description: Sets the read batches size.
 *
 * Parameter:
 *              - unsigned size: Read batch size. The set value is minus 1 the required number. Max size is 0x1F.
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_READ_EXECUTION_THRESHOLD(unsigned size){
    unsigned int* RWTHRESH = (unsigned*)(DDR3A_EMIF_CONFIGURATION + RWTHRESH_OFFSET);
    *RWTHRESH &= 0xFFFFFFD0; // Clear RD_THRESH bits
    *RWTHRESH |= (size); // Set RD_THRESH bits

}

/* set_DDR3A_WRITE_EXECUTION_THRESHOLD
 *
 * Description: Sets the write batches size.
 *
 * Parameter:
 *              - unsigned size: Write batch size. The set value is minus 1 the required number. Max size is 0x1F.
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_WRITE_EXECUTION_THRESHOLD(unsigned size){
    unsigned int* RWTHRESH = (unsigned*)(DDR3A_EMIF_CONFIGURATION + RWTHRESH_OFFSET);
    *RWTHRESH &= 0xFFFFD0FF; // Clear WR_THRESH bits
    *RWTHRESH |= (size<<8); // Set WR_THRESH bits
}


