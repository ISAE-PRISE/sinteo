/*************************************************************************
 * SINTEO project
 * Copyright (C) 2022 ISAE-SUPAERO / ONERA
*************************************************************************/

/*--------------------------- main.c -------------------------------------
 |  File main.c
 |
 |  Description:  Profiling functions are defined and used
 |                for analyzing the effect of different
 |                benchmarks on the system.
 |
 |  Version: 1.0V
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
#include "benchmarks.h"
#include "MMU.h"
#include "PMH.h"
#include "UART.h"
#include "MSMC.h"
#include "DDR3MemoryController.h"


/* ----------------------- LOCAL FUNCTIONS --------------------------- */
void ARM_disable_caches();
void ARM_init();
void counters_init();
void critical_task_start_eval();
void critical_task_end_eval();
void DDR_configure_eval(unsigned filter_events);
void DDR_start_eval();
void DDR_end_eval();
void configure_AXI(unsigned priority);


/* --------------- GLOBAL FUNCTION DEFINITIONS ----------------------- */

// Iteration number
#define  MAX_ITERATIONS 1000
// ARM configuration mode. 0 = only L1 instruction cache, 1 = all caches plus others (MMU, branch predictor...)
#define ARM_INIT_CONFIGURATION   1

// ARM performance counter ID to use
#define counter_id_0 0x0
#define counter_id_1 0x1
#define counter_id_2 0x2
#define counter_id_3 0x3
#define counter_id_4 0x4
#define counter_id_5 0x5

/**
 * Select event to study.
 *
 * Event Name/Number List:
 *
 * Cycle = 0x11
 * Bus Access = 0x19
 *
 * Level 1 data cache refill = 0x03
 * Level 1 data cache access = 0x04
 * Level 1 instruction cache refill = 0x01
 * Level 1 instruction cache access = 0x14
 *
 * Level 2 data cache access = 0x16
 * Level 2 data cache refill = 0x17
 *
 * Miss-predicted branch = 0x10
 * Instruction speculatively executed = 0x1B
 * Predictable branch speculatively executed = 0x12
 *
 * For more, see: https://developer.arm.com/docs/ddi0438/c/performance-monitor-unit/events
 * */

#define event_id_0   0x19
#define event_id_1   0x04
#define event_id_2   0x03
#define event_id_3   0x16
#define event_id_4   0x17
#define event_id_5   0x10

// ARM performance counter final read variables
unsigned long value0f = 0, value1f = 0, value2f = 0, value3f = 0, value4f = 0, value5f = 0, valueCf = 0;
// EMIF0 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif0,t2_ddr_cycles_emif0, result_ddr_cycles_emif0, t1_ddr_evt0_emif0, t2_ddr_evt0_emif0, result_ddr_evt0_emif0, t1_ddr_evt1_emif0, t2_ddr_evt1_emif0, result_ddr_evt1_emif0;

// Addresses to different DDR3 memory banks
const unsigned DDR_BANK_0 = 0xC8012000;
const unsigned DDR_BANK_1 = 0xC8014000;
const unsigned DDR_BANK_2 = 0xC8016000;
const unsigned DDR_BANK_3 = 0xC8018000;


/* ========================================================================== */
/*                   Internal Function Declarations                           */
/* ========================================================================== */

int main(void)
{
    // Disable caches for a safe cache set up
    ARM_disable_caches();

    // Configure ARM
    if(ARM_INIT_CONFIGURATION == 1)
        ARM_init(0x86000000);
    else if(ARM_INIT_CONFIGURATION == 0)
        enable_caches(1,0);

    // Set ARM AXI bus priority
    configure_AXI(0x7);

    // Change salve starvation value
    write_ARM_SBNDC(0x00FF00FF);

    // Configure EMIF performance counters
    DDR_configure_eval(1);

    // Configure ARM Cortex A15 performance counters
    counters_init();

    write_UART_THR("Task profiling: Start-Stop pattern on ARMs \n\r");
    write_UART_THR("Task profiling: Start-Read pattern on memory controller \n\r");

    unsigned i = 0;
    char data_str[128];


    /* Start tasks profiling */
    /*************************/

    // Intended for no data caches implementation
    write_UART_THR("Store burst on DDR SDRAM bank 0: Execution time (cycles), bus accesses, L1 and L2 cache access and refill, and miss-predicted branch \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        critical_task_start_eval();
        cpu_microbenchmark_store(DDR_BANK_0, 0xFF00FF);
        __asm__ __volatile("dsb");
        critical_task_end_eval();
        sprintf(data_str, "%u %lu %lu %lu %lu %lu %lu %lu \n\r", i, valueCf, value0f, value1f, value2f, value3f, value4f, value5f);
        write_UART_THR(data_str);

    }


    // Intended for no data caches implementation
    write_UART_THR("Store burst on DDR SDRAM bank 0: Utilization time (cycles), number of accesses and actives for both EMIFs \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        DDR_start_eval();
        cpu_microbenchmark_store(DDR_BANK_0, 0xFF00FF);
        __asm__ __volatile("dsb");
        DDR_end_eval();

        sprintf(data_str, "%u %u %u %u \n\r", i, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
        write_UART_THR(data_str);
    }


    // Intended for no data caches implementation
    write_UART_THR("Load burst on DDR SDRAM bank 0: Execution time (cycles), bus accesses, L1 and L2 cache access and refill, and miss-predicted branch \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        critical_task_start_eval();
        cpu_microbenchmark_load(DDR_BANK_1);
        __asm__ __volatile("dsb");
        critical_task_end_eval();

        sprintf(data_str, "%u %lu %lu %lu %lu %lu %lu %lu \n\r", i, valueCf, value0f, value1f, value2f, value3f, value4f, value5f);
        write_UART_THR(data_str);

    }

    // Intended for no data caches implementation
    write_UART_THR("Load burst on DDR SDRAM bank 0: Utilization time (cycles), number of accesses and actives \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        DDR_start_eval();
        cpu_microbenchmark_load(DDR_BANK_1);
        __asm__ __volatile("dsb");
        DDR_end_eval();

        sprintf(data_str, "%u %u %u %u \n\r", i, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
        write_UART_THR(data_str);
    }


    // Intended especially for data caches implementation but also useful for the without data caches implementation
    write_UART_THR("Pointer chasing cache stress: Execution time (cycles), bus accesses, L1 and L2 cache access and refill, and miss-predicted branch \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        critical_task_start_eval();
        cpu_pointer_chasing_microbenchmark(100000, 16, 8*1024*1024);
        __asm__ __volatile("dsb");
        critical_task_end_eval();

        sprintf(data_str, "%u %lu %lu %lu %lu %lu %lu %lu \n\r", i, valueCf, value0f, value1f, value2f, value3f, value4f, value5f);
        write_UART_THR(data_str);

    }

    // Intended especially for data caches implementation but also useful for the without data caches implementation
    write_UART_THR("Pointer chasing cache stress: Utilization time (cycles), number of accesses and actives for both EMIFs \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        DDR_start_eval();
        cpu_pointer_chasing_microbenchmark(100000, 16, 8*1024*1024);
        __asm__ __volatile("dsb");
        DDR_end_eval();

        sprintf(data_str, "%u %u %u %u \n\r", i, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
        write_UART_THR(data_str);
    }


    // Intended especially for data caches implementation but also useful for the without data caches implementation
    write_UART_THR("System stress matrix: Execution time (cycles), bus accesses, L1 and L2 cache access and refill, and miss-predicted branch \n\r");

    unsigned const MATRIX_SIZE = 512;

    for(i=0; i < MAX_ITERATIONS; i++){
        critical_task_start_eval();
        matrix_stress2_task(MATRIX_SIZE);
        __asm__ __volatile("dsb");
        critical_task_end_eval();

        sprintf(data_str, "%u %lu %lu %lu %lu %lu %lu %lu \n\r", i, valueCf, value0f, value1f, value2f, value3f, value4f, value5f);
        write_UART_THR(data_str);

    }

    // Intended especially for data caches implementation but also useful for the without data caches implementation
    write_UART_THR("System stress matrix: Utilization time (cycles), number of accesses and actives for both EMIFs\n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        DDR_start_eval();
        matrix_stress2_task(MATRIX_SIZE);
        __asm__ __volatile("dsb");
        DDR_end_eval();

        sprintf(data_str, "%u %u %u %u \n\r", i, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
        write_UART_THR(data_str);
    }


    while(1);
}


/* configure_AXI
 *
 * Description: Configures the AXI bus serving priority when different processing elements requests are being served
 *
 *
 * Parameter:
 *              - unsigned priority: Priority from 0 to 7, being 0 the highest
 *
 * Returns:     Nothing
 *
 * */
void configure_AXI(unsigned priority){

    const unsigned BUS_ADDRESS = 0x1000000;
    unsigned* bus_PRI = BUS_ADDRESS + 0x20;

//    printf("Register bus_PRI = %X \n", *bus_PRI);
    *bus_PRI = priority;
//    printf("Register bus_PRI = %X \n", *bus_PRI);

}

/* counters_init
 *
 * Description: Sets the events for each ARM Cortex A15 performance counters
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
volatile void counters_init(){
    // Select counter to program: counter_number can be between 0-5
    select_evt_counter(counter_id_0);

    // Select event to track in selected counter: event_id numbers are in the ARM A15 TRM
    event_track(event_id_0);

    select_evt_counter(counter_id_1);
    event_track(event_id_1);

    select_evt_counter(counter_id_2);
    event_track(event_id_2);

    select_evt_counter(counter_id_3);
    event_track(event_id_3);

    select_evt_counter(counter_id_4);
    event_track(event_id_4);

    select_evt_counter(counter_id_5);
    event_track(event_id_5);


}


/* critical_task_start_eval
 *
 * Description: Prepares the performance counters for its use by: clearing a possible overflow flag, reseting the configuration of each counter and activating all of them at once
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
volatile void critical_task_start_eval(){

    // Clear possible overflows of every counter
    clear_overflows();

    // Select counter to program: counter_number can be between 0-5
    select_evt_counter(counter_id_0);

    // Reset the actual value and enables of the counter and don't enable the divider
    reset_all_counters(0);

    select_evt_counter(counter_id_1);
    reset_all_counters(0);

    select_evt_counter(counter_id_2);
    reset_all_counters(0);

    select_evt_counter(counter_id_3);
    reset_all_counters(0);

    select_evt_counter(counter_id_4);
    reset_all_counters(0);

    select_evt_counter(counter_id_5);
    reset_all_counters(0);

    reset_all_counters(0);

    // Synchronize context (Instruction Synchronization Barrier)
    __asm__ __volatile("isb");

    // Enable counters
    enable_all_counters(0x3F);

}

/* critical_task_start_eval
 *
 * Description: Deactivates all performance counters at once and reads the event values for each of them
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
volatile void critical_task_end_eval(){

    // Disable counters
    disable_all_counters(0x3F);

    // Select general performance counter to read from
    select_evt_counter(counter_id_0);

    // Read value
    value0f=read_evt_counter();

    select_evt_counter(counter_id_1);
    value1f=read_evt_counter();

    select_evt_counter(counter_id_2);
    value2f=read_evt_counter();

    select_evt_counter(counter_id_3);
    value3f=read_evt_counter();

    select_evt_counter(counter_id_4);
    value4f=read_evt_counter();

    select_evt_counter(counter_id_5);
    value5f=read_evt_counter();

    // Read from the dedicated execution cycles performance counter
    valueCf = read_cycle_counter();

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
 *              - Pages (assumes 1MB page sizes)
 *              - Caches
 *              - MMU
 *              - Branch predictor
 *
 * Parameter:
 *              - unsigned tlb1_pos: Indicates the address to where the pages are written
 *
 *
 * Returns:     Nothing
 *
 * */
void ARM_init(unsigned tlb1_pos){

    volatile unsigned int* reg = NULL;

//    printf("Configuring 1MB pages... \n");

    // Set pages for the DDR Memory as cacheable
    for(int cnt = 2048; cnt < 4091; cnt++){
        reg = tlb1_pos + (cnt<<2);
        *reg = 0x015DE6|(cnt<<20);
    }
    // Set pages for the lower PA addresses as non-cacheable
    for(int cnt = 0; cnt < 2048; cnt++){
        reg = tlb1_pos + (cnt<<2);
        *reg = 0x010DE2|(cnt<<20);
    }

   // TTBR0, address must be equal to tlb1_pos, which is where we have written the pages
   __asm__ __volatile("MOV r1,#0x0 \n\t"
                      "MCR p15, 0, r1, c2, c0, 2 \n\t"
                      "MCR p15, 0, %[input_i], c2, c0, 0 \n\t"
                       :: [input_i] "r" (tlb1_pos)
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

/* DDR_configure_eval
 *
 * Description: Sets the performance counters events and master (MSTID) from who the event are captured.
 *
 *
 * Parameter:
 *              - unsigned filter_events: Chooses whether to filter by master ID or to globally analyze the system
 *
 * Returns:     Nothing
 *
 * */
void DDR_configure_eval(unsigned filter_events){
    /* EMIF1, performance counter 0 */
    set_PERF_CNT_EVENT(0, 0x0);

    if (filter_events){
        enable_CNT_MSTID(0);
        set_MSTID(0, 0x8); // Filter by Master ID
    }
    /* EMIF1, performance counter 1 */
    set_PERF_CNT_EVENT(1, 0x1);

    if (filter_events){
        enable_CNT_MSTID(1);
        set_MSTID(1, 0x8); // Filter by Master ID
    }

}

/* DDR_start_eval
 *
 * Description: Reads the performance counters for the first time.
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void DDR_start_eval(){
    t1_ddr_evt0_emif0 = get_PERF_CNT_1();
    t1_ddr_evt1_emif0 = get_PERF_CNT_2();
    t1_ddr_cycles_emif0 = get_PERF_CNT_TIMER();
}

/* DDR_end_eval
 *
 * Description: Reads the performance counters a final time and calculates the final time.
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void DDR_end_eval(){
    t2_ddr_evt0_emif0 = get_PERF_CNT_1();
    t2_ddr_evt1_emif0 = get_PERF_CNT_2();
    t2_ddr_cycles_emif0 = get_PERF_CNT_TIMER();

    result_ddr_cycles_emif0 = t2_ddr_cycles_emif0 - t1_ddr_cycles_emif0;
    result_ddr_evt0_emif0 = t2_ddr_evt0_emif0 - t1_ddr_evt0_emif0;
    result_ddr_evt1_emif0 = t2_ddr_evt1_emif0 - t1_ddr_evt1_emif0;

}







