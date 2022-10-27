/*--------------------------- ddr3_memory_controller.h -------------------------------------
 |  File ddr3_memory_controller.h
 |
 |  Description: This file provides functions for managing the
 |  EMIFs on Sitara AM5728
 |
 |  Version: 2.2
 *-----------------------------------------------------------------------*/

#ifndef DDR3MEMORYCONTROLLER_H_
#define DDR3MEMORYCONTROLLER_H_

#define SDCFG_OFFSET 0x008
#define LAT_CONFIG_OFFSET 0x54
#define PERF_CNT_1_OFFSET 0x80
#define PERF_CNT_2_OFFSET 0x84
#define PERF_CNT_CFG_OFFSET 0x88
#define PERF_CNT_SEL_OFFSET 0x8C
#define PERF_CNT_TIM_OFFSET 0x90

#define RWTHRESH_OFFSET 0x120


/* get_PERF_CNT_1
 *
 * Description: Retrieves the first performance counter value from the selected EMIF
 *
 * Parameter:
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
unsigned get_PERF_CNT_1(void* emif_emif_base_address){
    unsigned int* perf_cnt = NULL;
    perf_cnt = (unsigned *)(emif_emif_base_address + PERF_CNT_1_OFFSET);

    return *perf_cnt;
}

/* get_PERF_CNT_2
 *
 * Description: Retrieves the second performance counter value from the selected EMIF
 *
 * Parameter:
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
unsigned get_PERF_CNT_2(void* emif_base_address){
    unsigned int* perf_cnt = NULL;
    perf_cnt = (unsigned *)(emif_base_address + PERF_CNT_2_OFFSET);

    return *perf_cnt;
}

/* get_PERF_CNT_TIMER
 *
 * Description: Retrieves the dedicated timer counter value from the selected EMIF
 *
 * Parameter:
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
unsigned get_PERF_CNT_TIMER(void* emif_base_address){
    unsigned int* perf_cnt_timer = NULL;
    perf_cnt_timer = (unsigned *)(emif_base_address + PERF_CNT_TIM_OFFSET);

    return *perf_cnt_timer;
}


/* set_PERF_CNT_EVENT
 *
 * Description: Sets the event to study for the selected EMIF performance counter 
 *
 * CNTRn_CFG                    Event Selected for counting      CNTRn_REGION_EN            CNTRn_MCONNID_EN
 * 0x0                          Total SDRAM accesses             NA                         0 - Disable, 1 - Enable
 * 0x1                          Total SDRAM activates            NA                         0 - Disable, 1 - Enable
 * 0x2                          Total Reads                      0 - Disable, 1 - Enable    0 - Disable, 1 - Enable
 * 0x3                          Total Writes                     0 - Disable, 1 - Enable    0 - Disable, 1 - Enable
 *
 * See more at: https://www.ti.com/lit/ug/spruhz6l/spruhz6l.pdf (Section 15.3.4.16 Performance Counters)
 *
 * Parameter:
 *              - unsigned id: Performance counter to select (0 for first counter, 1 for second counter)
 *              - unsigned event: Event to study
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
void set_PERF_CNT_EVENT(unsigned id, unsigned event, void* emif_base_address){
    unsigned int* perf_cnt_cfg = NULL;
    perf_cnt_cfg = (unsigned *)(emif_base_address + PERF_CNT_CFG_OFFSET);

    if(id == 0){
        *perf_cnt_cfg &= 0xFFFFFFF0; // Clear CNTR1_CFG bits
        *perf_cnt_cfg |= (event<<0); // Set CNTR1_CFG bits
    }
    else if(id == 1){
        *perf_cnt_cfg &= 0xFFF0FFFF; // Clear CNTR2_CFG bits
        *perf_cnt_cfg |= (event<<16); // Set CNTR2_CFG bits
    }

}


/* enable_CNT_MSTID
 *
 * Description: Enables the use of filters for an EMIF performance counter
 *
 *
 * Parameter:
 *              - unsigned id: Performance counter to select (0 for first counter, 1 for second counter)
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
void enable_CNT_MSTID(unsigned id,  void* emif_base_address){
    unsigned int* perf_cnt_cfg = NULL;
    perf_cnt_cfg = (unsigned *)(emif_base_address + PERF_CNT_CFG_OFFSET);

    if(id == 0)
        *perf_cnt_cfg |= (1<<15); // Set CNTR1_CFG bits
    else if(id == 1)
        *perf_cnt_cfg |= (1<<31); // Set CNTR2_CFG bits
}





/* set_MSTID
 *
 * Description: Sets the master to study for the selected EMIF performance counter (assuming master filtering is enable)
 *
 * Reference: https://www.ti.com/lit/ug/spruhz6l/spruhz6l.pdf (Table 14-10. ConnID Values)
 *
 * Master Id    Entity
 * 0x0           MPU (ARM Cortex A15 cores 0 and 1)
 * 0x20          DSP1 MDMA
 * 0x34          DSP2 MDMA
 *
 * Parameter:
 *              - unsigned id: Performance counter to select (0 for first counter, 1 for second counter)
 *              - unsigned master_id: Id of the master to focus on
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
void set_MSTID(unsigned id, unsigned master_id, void* emif_base_address){
    unsigned int* perf_cnt_sel = NULL;
    perf_cnt_sel = (unsigned *)(emif_base_address + PERF_CNT_SEL_OFFSET);

    if(id == 0)
        *perf_cnt_sel |= (master_id<<8); // Set MSTID1 bits
    else if(id == 1)
        *perf_cnt_sel |= (master_id<<24); // Set MSTID2 bits
}


/* set_DDR3A_SDCFG_IBANK
 *
 * Description: Sets the number of SDRAM banks to use
 *
 * Caveats: It is better to use GEL configuration file to set this feature to avoid issues
 *
 *
 * Parameter:
 *              - unsigned banks_number: Value for setting the number of banks (0 = 1 bank, 1 = 2 banks, 2 = 4 banks, 3 = 8 banks)
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_SDCFG_IBANK(int banks_number,  void* emif_base_address){
    unsigned int* sdcfg = NULL;
    sdcfg = (unsigned *)(emif_base_address + SDCFG_OFFSET);

    *sdcfg &= 0xFFFFFF9F; // Clear IBANK bits
    *sdcfg |= (banks_number<<5); // Set IBANK bits
}


/* get_DDR3A_SDCFG_IBANK
 *
 * Description: Retrieves the number of banks in use by an EMIF
 *
 *
 * Parameter:
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     The number of banks used
 *
 * */
unsigned get_DDR3A_SDCFG_IBANK(void* emif_base_address){
    unsigned int* sdcfg = NULL;
    sdcfg = (unsigned *)(emif_base_address + SDCFG_OFFSET);

    return *sdcfg & 0x060; // Clear IBANK bits
}

/* get_DDR3A_SDCFG_PAGESIZE
 *
 * Description: Retrieves the size of the SDRAM pages in use by an EMIF
 *
 *
 * Parameter:
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     The number of banks used
 *
 * */
unsigned get_DDR3A_SDCFG_PAGESIZE(void* emif_base_address){
    unsigned int* sdcfg = NULL;
    sdcfg = (unsigned *)(emif_base_address + SDCFG_OFFSET);

    return *sdcfg & 0x003; // Clear IBANK bits
}

/* set_DDR3A_SDCFG_EBANK
 *
 * Description: Defines the number of chip select lines in use
 *
 * Caveats: It is better to use GEL configuration file to set this feature to avoid issues
 *
 * Parameter:
 *              - unsigned chips_number: Value for setting the number of chips (0 = 1 chip, 1 = 2 chips)
 *              - unsigned unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_SDCFG_EBANK(int chips_number, void* emif_base_address){
    unsigned int* sdcfg = NULL;
    sdcfg = (unsigned *)(emif_base_address + SDCFG_OFFSET);

    *sdcfg &= 0xFFFFFFF7; // Clear EBANK bits
    *sdcfg |= (chips_number<<3); // Set EBANK bits
}


/* get_DDR3A_SDCFG_EBANK
 *
 * Description: Retrieves the number of chip select lines in use
 *
 *
 * Parameter:
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     The number of chips used
 *
 * */
unsigned get_DDR3A_SDCFG_EBANK(void* emif_base_address){
    unsigned int* sdcfg = NULL;
    sdcfg = (unsigned *)(emif_base_address + SDCFG_OFFSET);

    return *sdcfg & 0x08; // Clear IBANK bits
}


/* set_DDR3A_PR_OLD_COUNT
 *
 * Description: Sets the priority elevation count (starvation mechanism triggering count)
 *
 *
 * Parameter:
 *              - unsigned count: Priority raise old counter (max value is 0xFF)
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_PR_OLD_COUNT(int count,  void* emif_base_address){
    unsigned int* lat_config = NULL;
    lat_config = (unsigned *)(emif_base_address + LAT_CONFIG_OFFSET);

    *lat_config &= 0xFFFFFF00; // Clear PR_OLD_COUNT bits
    *lat_config |= (count); // Set PR_OLD_COUNT bits
}

/* set_DDR3A_READ_EXECUTION_THRESHOLD
 *
 * Description: Sets the read batches size.
 *
 * Parameter:
 *              - unsigned size: Read batch size. The set value is minus 1 the required number. Max size is 0x1F.
 *              - unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_READ_EXECUTION_THRESHOLD(int size, void* emif_base_address){
    unsigned int* rw_thresh = NULL;
    rw_thresh = (unsigned *)(emif_base_address + RWTHRESH_OFFSET);

    *rw_thresh &= 0xFFFFFFD0; // Clear RD_THRESH bits
    *rw_thresh |= (size); // Set RD_THRESH bits
}

/* set_DDR3A_WRITE_EXECUTION_THRESHOLD
 *
 * Description: Sets the write batches size.
 *
 * Parameter:
 *              - unsigned size: Write batch size. The set value is minus 1 the required number. Max size is 0x1F.
 *              - unsigned unsigned emif_base_address: Address of EMIF 0 or 1 
 *
 * Returns:     Nothing
 *
 * */
void set_DDR3A_WRITE_EXECUTION_THRESHOLD(int number, void* emif_base_address){
    unsigned int* rw_thresh = NULL;
    rw_thresh = (unsigned *)(emif_base_address + RWTHRESH_OFFSET);

    *rw_thresh &= 0xFFFFD0FF; // Clear WR_THRESH bits
    *rw_thresh |= (number<<8); // Set WR_THRESH bits
}

#endif /* DDR3MEMORYCONTROLLER_H_ */

