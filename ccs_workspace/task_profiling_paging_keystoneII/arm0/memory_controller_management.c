/*-------------------- memory_controller_management.c --------------------
 |  File memory_controller_management.c
 |
 |  Description: The functions definition for the Keystone II SDRAM
 |               controller management are done here
 |
 |  Version: 1
 *-----------------------------------------------------------------------*/

#include <stdio.h>
#include "DDR3MemoryController.h"
#include "memory_controller_management.h"


/* *
 * Select the event to be analyzed by the EMIFs
 *
 * CNTRn_CFG                    Event Selected for counting      CNTRn_REGION_EN            CNTRn_MCONNID_EN
 * 0x0                          Total SDRAM accesses             NA                         0 - Disable, 1 - Enable
 * 0x1                          Total SDRAM activates            NA                         0 - Disable, 1 - Enable
 * 0x2                          Total Reads                      0 - Disable, 1 - Enable    0 - Disable, 1 - Enable
 * 0x3                          Total Writes                     0 - Disable, 1 - Enable    0 - Disable, 1 - Enable
 * ...
 *
 * See all events at: https://www.ti.com/lit/ug/spruhn7c/spruhn7c.pdf?ts=1649333950012 (Table 2-12. Performance Counter Filter Configuration)
* */
#define EMIF_EVENT_ID_0   0x0
#define EMIF_EVENT_ID_1   0x1

/*
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
 * ...
 *
 * See all master IDs at: https://www.ti.com/lit/ds/symlink/66ak2h06.pdf?ts=1663928051848&ref_url=https%253A%252F%252Fwww.google.com%252F (Table 8-6. Master ID Settings)
 */
#define MASTER_ID_PERF_CNT_0   0x8
#define MASTER_ID_PERF_CNT_1   0x8


// Configures the DDR memory controller performance counter
void DDR_configure_eval(unsigned filter_events){
    /* EMIF1, performance counter 0 */
    set_PERF_CNT_EVENT(0, 0x0);

    if (filter_events){
        enable_CNT_MSTID(0);
        set_MSTID(0, MASTER_ID_PERF_CNT_0); // Filter by Master ID
    }
    /* EMIF1, performance counter 1 */
    set_PERF_CNT_EVENT(1, 0x1);

    if (filter_events){
        enable_CNT_MSTID(1);
        set_MSTID(1, MASTER_ID_PERF_CNT_1); // Filter by Master ID
    }

}

// Reads the DDR performance counters for the first time
void DDR_start_eval(){
    t1_ddr_evt0_emif0 = get_PERF_CNT_1();
    t1_ddr_evt1_emif0 = get_PERF_CNT_2();
    t1_ddr_cycles_emif0 = get_PERF_CNT_TIMER();
}

// Reads the DDR performance counters for the second time and calculates the
// time difference
void DDR_end_eval(){
    t2_ddr_evt0_emif0 = get_PERF_CNT_1();
    t2_ddr_evt1_emif0 = get_PERF_CNT_2();
    t2_ddr_cycles_emif0 = get_PERF_CNT_TIMER();

    result_ddr_cycles_emif0 = t2_ddr_cycles_emif0 - t1_ddr_cycles_emif0;
    result_ddr_evt0_emif0 = t2_ddr_evt0_emif0 - t1_ddr_evt0_emif0;
    result_ddr_evt1_emif0 = t2_ddr_evt1_emif0 - t1_ddr_evt1_emif0;

}


// Print the metrics  
void print_emif_results(unsigned id){
 printf("%u %u %u %u \n", id, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
}






