/*--------------------------- emif_management.c ------------------------
 |  File emif_management.c
 |
 |  Description: The functions definition for the Sitara AM5728 EMIF
 |               management are done here
 |
 |  Version: 1V
 *-----------------------------------------------------------------------*/

#include <stdio.h>
#include "ddr3_memory_controller.h"

/* *
 * Select the event to be analized by the EMIFs
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


// EMIF0 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif0,t2_ddr_cycles_emif0, result_ddr_cycles_emif0, t1_ddr_evt0_emif0, t2_ddr_evt0_emif0, result_ddr_evt0_emif0, t1_ddr_evt1_emif0, t2_ddr_evt1_emif0, result_ddr_evt1_emif0;
// EMIF1 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif1,t2_ddr_cycles_emif1, result_ddr_cycles_emif1, t1_ddr_evt0_emif1, t2_ddr_evt0_emif1, result_ddr_evt0_emif1, t1_ddr_evt1_emif1 ,t2_ddr_evt1_emif1, result_ddr_evt1_emif1;


// Configures the DDR memory controller perofrmance counter 
void DDR_configure_eval(unsigned filter_events, unsigned master0_id, unsigned master1_id, void* emif0_addr, void* emif1_addr){
    /* EMIF1, performance counter 0 */
    set_PERF_CNT_EVENT(0, EMIF_EVENT_ID_0, emif0_addr);

    if (filter_events){
        enable_CNT_MSTID(0, emif0_addr);
        set_MSTID(0, master0_id, emif0_addr); // Filter by Master ID
    }
    /* EMIF1, performance counter 1 */
    set_PERF_CNT_EVENT(1, EMIF_EVENT_ID_1, emif0_addr);

    if (filter_events){
        enable_CNT_MSTID(1, emif0_addr);
        set_MSTID(1, master0_id, emif0_addr); // Filter by Master ID
    }

    /* EMIF2, performance counter 0 */
    set_PERF_CNT_EVENT(0, EMIF_EVENT_ID_0, emif1_addr);

    if (filter_events){
        enable_CNT_MSTID(0, emif1_addr);
        set_MSTID(0, master1_id, emif1_addr); // Filter by Master ID
    }

    /* EMIF2, performance counter 1 */
    set_PERF_CNT_EVENT(1, EMIF_EVENT_ID_1, emif1_addr);

    if (filter_events){
        enable_CNT_MSTID(1, emif1_addr);
        set_MSTID(1, master1_id, emif1_addr); // Filter by Master ID
    }
}

// Reads the DDR performance counters for the first time
void DDR_start_eval(void* emif0_addr, void* emif1_addr){
    t1_ddr_evt0_emif0 = get_PERF_CNT_1(emif0_addr);
    t1_ddr_evt1_emif0 = get_PERF_CNT_2(emif0_addr);
    t1_ddr_cycles_emif0 = get_PERF_CNT_TIMER(emif0_addr);

    t1_ddr_evt0_emif1 = get_PERF_CNT_1(emif1_addr);
    t1_ddr_evt1_emif1 = get_PERF_CNT_2(emif1_addr);
    t1_ddr_cycles_emif1 = get_PERF_CNT_TIMER(emif1_addr);
}

// Reads the DDR performance counters for the second time and calculates the
// time difference
void DDR_end_eval(void* emif0_addr, void* emif1_addr){
    t2_ddr_evt0_emif0 = get_PERF_CNT_1(emif0_addr);
    t2_ddr_evt1_emif0 = get_PERF_CNT_2(emif0_addr);
    t2_ddr_cycles_emif0 = get_PERF_CNT_TIMER(emif0_addr);

    t2_ddr_evt0_emif1 = get_PERF_CNT_1(emif1_addr);
    t2_ddr_evt1_emif1 = get_PERF_CNT_2(emif1_addr);
    t2_ddr_cycles_emif1 = get_PERF_CNT_TIMER(emif1_addr);

    result_ddr_cycles_emif0 = t2_ddr_cycles_emif0 - t1_ddr_cycles_emif0;
    result_ddr_evt0_emif0 = t2_ddr_evt0_emif0 - t1_ddr_evt0_emif0;
    result_ddr_evt1_emif0 = t2_ddr_evt1_emif0 - t1_ddr_evt1_emif0;

    result_ddr_cycles_emif1 = t2_ddr_cycles_emif1 - t1_ddr_cycles_emif1;
    result_ddr_evt0_emif1 = t2_ddr_evt0_emif1 - t1_ddr_evt0_emif1;
    result_ddr_evt1_emif1 = t2_ddr_evt1_emif1 - t1_ddr_evt1_emif1;
}


// Print the metrics  
void print_emif_results(unsigned id){
 printf("%u %u %u %u %u %u %u \n", id, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0, result_ddr_cycles_emif1, result_ddr_evt0_emif1, result_ddr_evt1_emif1);
}






