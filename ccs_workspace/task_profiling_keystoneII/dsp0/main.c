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
 |  Version: 1.1V
 |
 | Contact:
 | alfonso.mascarenas-gonzalez@isae-supaero.fr
 | jean-baptiste.chaudron@isae-supaero.fr
 | youcef.bouchebaba@onera.fr
 | frederic.boniol@onera.fr
 | jean-loup.bussenot@onera.fr
 *-----------------------------------------------------------------------*/


// CSL libraries
#include <benchmark.h>
#include <ti/csl/soc/k2l/src/cslr_device.h>
#include <ti/csl/csl.h>
#include <ti/csl/csl_cache.h>
#include <ti/csl/csl_cacheAux.h>

// Bring in references to TSCL, TSCH
#include <c6x.h>

#include <stdio.h>
#include <string.h>

#include "DSP_arbitration.h"
#include "../arm0/DDR3MemoryController.h"
#include "../arm0/UART.h"
#include "../arm0/MSMC.h"

/* ----------------------- LOCAL FUNCTIONS --------------------------- */
void DSP_init();
void slaves_configuration();
void critical_task_start_eval();
void critical_task_end_eval();
void DDR_configure_eval(unsigned filter_events);
void DDR_start_eval();
void DDR_end_eval();


// Iteration number
#define  MAX_ITERATIONS 1000
// DSP configuration mode. 0 = only L1 instruction cache, 1 = all caches
#define DSP_INIT_CONFIGURATION   0

/* L1 and L2 Caching Memory area */
#define CACHE_L2_CORE0    (16) // MAR16 0184 8040h
#define RAM_0_CORE0         (144)   // 0184 8240h MAR144 Memory Attribute Register 9000 0000h - 90FF FFFFh
#define RAM_1_CORE0         (145)
#define RAM_2_CORE0         (146)
#define RAM_3_CORE0         (147)
#define RAM_4_CORE0         (148)
#define RAM_5_CORE0         (149)
#define RAM_6_CORE0         (150)
#define RAM_7_CORE0         (151)
#define RAM_8_CORE0         (152)
#define RAM_9_CORE0         (153)
#define RAM_A_CORE0         (154)
#define RAM_B_CORE0         (155)
#define RAM_C_CORE0         (156)
#define RAM_D_CORE0         (157)
#define RAM_E_CORE0         (158)
#define RAM_F_CORE0         (159)

// DSP Time Stamp Register variables
unsigned long long t1_L,t2_L, t1_H, t2_H, t1, t2, result;
// EMIF0 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif0,t2_ddr_cycles_emif0, result_ddr_cycles_emif0, t1_ddr_evt0_emif0, t2_ddr_evt0_emif0, result_ddr_evt0_emif0, t1_ddr_evt1_emif0, t2_ddr_evt1_emif0, result_ddr_evt1_emif0;

const unsigned DDR_BANK_0 = 0x88032000;
const unsigned DDR_BANK_1 = 0x88034000;
const unsigned DDR_BANK_2 = 0x88036000;
const unsigned DDR_BANK_3 = 0x88038000;



/* DSP_init
 *
 * Description: Configures the DSP core caches and cacheability of the physical addresses
 *
 * Parameter:   None
 *
 *
 * Returns:     Nothing
 *
 * */
void DSP_init(){

    // Configure DSP
    if(DSP_INIT_CONFIGURATION == 1){
        // Enabling the DDR memory caching (0x80000000-0xFFFFFFFF) by confuring the MAR bits
        unsigned i = 0;
        for(i = 128; i < 255; i++)
            CACHE_enableCaching(i);

        // Set cache size
        CACHE_setL2Size(CACHE_1024KCACHE);
        CACHE_setL1DSize(CACHE_L1_32KCACHE);
        CACHE_setL1PSize(CACHE_L1_32KCACHE);
    }
    else if(DSP_INIT_CONFIGURATION == 0){
        CACHE_setL2Size(CACHE_0KCACHE);
        CACHE_setL1DSize(CACHE_L1_0KCACHE);
        CACHE_setL1PSize(CACHE_L1_32KCACHE);
    }

    // Set out-of-core requests priority
    write_MDMAARBU(0x07070000);

    // Change salve starvation value
    write_SBNDC(0, 0x00FF00FF);

}

int main(void)
{

    // DSP basic configuration
    DSP_init();

    // Configure EMIF performance counters
    DDR_configure_eval(1);

    write_UART_THR("Task profiling: Start-Read pattern on DSPs \n\r");
    write_UART_THR("Task profiling: Start-Read pattern on EMIFs \n\r");

    TSCL = 0; // Initiate CPU timer by writing any value to TSCL

    unsigned i = 0;
    char data_str[128];


    /* Start tasks profiling */
    /*************************/

    // Intended for no data caches implementation
    write_UART_THR("Store burst on DDR SDRAM bank 0: Execution time (cycles) \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        critical_task_start_eval();
        cpu_microbenchmark_store(DDR_BANK_0, 0xFF00FF);
        critical_task_end_eval();
        sprintf(data_str, "%u %llu \n\r", i, result);
        write_UART_THR(data_str);

    }

    // Intended for no data caches implementation
    write_UART_THR("Store burst on DDR SDRAM bank 0: Utilization time (cycles), number of accesses and actives for both EMIFs \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        DDR_start_eval();
        cpu_microbenchmark_store(DDR_BANK_0, 0xFF00FF);
        DDR_end_eval();

        sprintf(data_str, "%u %u %u %u \n\r", i, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
        write_UART_THR(data_str);
    }


    // Intended for no data caches implementation
    write_UART_THR("Load burst on DDR SDRAM bank 0: Execution time (cycles) \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        critical_task_start_eval();
        cpu_microbenchmark_load(DDR_BANK_1);
        critical_task_end_eval();

        sprintf(data_str, "%u %llu \n\r", i, result);
        write_UART_THR(data_str);

    }

    // Intended for no data caches implementation
    write_UART_THR("Load burst on DDR SDRAM bank 0: Utilization time (cycles), number of accesses and actives for both EMIFs \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        DDR_start_eval();
        cpu_microbenchmark_load(DDR_BANK_1);
        DDR_end_eval();

        sprintf(data_str, "%u %u %u %u \n\r", i, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
        write_UART_THR(data_str);
    }


    // Intended especially for data caches implementation but also useful for the without data caches implementation
    write_UART_THR("Pointer chasing cache stress: Execution time (cycles) \n\r");

    #define VECTOR_SIZE 8*1024*1024
    #define STRIDE_SIZE 16

    unsigned pointer_chasing_vector[VECTOR_SIZE]; // Pass as an argument of the function "cpu_pointer_chasing_microbenchmark" to avoid the use of __vla_alloc

    for(i=0; i < MAX_ITERATIONS; i++){
        critical_task_start_eval();
        cpu_pointer_chasing_microbenchmark(100000, STRIDE_SIZE, VECTOR_SIZE, pointer_chasing_vector);
        critical_task_end_eval();

        sprintf(data_str, "%u %llu \n\r", i, result);
        write_UART_THR(data_str);

    }

    // Intended especially for data caches implementation but also useful for the without data caches implementation
    write_UART_THR("Pointer chasing cache stress: Utilization time (cycles), number of accesses and actives for both EMIFs \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        DDR_start_eval();
        cpu_pointer_chasing_microbenchmark(100000, STRIDE_SIZE, VECTOR_SIZE, pointer_chasing_vector);
        DDR_end_eval();

        sprintf(data_str, "%u %u %u %u \n\r", i, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
        write_UART_THR(data_str);
    }


    // Intended especially for data caches implementation but also useful for the without data caches implementation
    write_UART_THR("System stress matrix: Execution time (cycles)\n\r");

    #define MATRIX_SIZE 512

    int in0[MATRIX_SIZE][MATRIX_SIZE]; // Pass as an argument of the function "matrix_stress2_task" to avoid the use of __vla_alloc
    int in1[MATRIX_SIZE][MATRIX_SIZE]; // Pass as an argument of the function "matrix_stress2_task" to avoid the use of __vla_alloc

    for(i=0; i < MAX_ITERATIONS; i++){
        critical_task_start_eval();
        matrix_stress2_task(MATRIX_SIZE, in0, in1);
        critical_task_end_eval();

        sprintf(data_str, "%u %llu \n\r", i, result);
        write_UART_THR(data_str);

    }

    // Intended especially for data caches implementation but also useful for the without data caches implementation
    write_UART_THR("System stress matrix: Utilization time (cycles), number of accesses and actives for both EMIFs \n\r");

    for(i=0; i < MAX_ITERATIONS; i++){
        DDR_start_eval();
        matrix_stress2_task(MATRIX_SIZE, in0, in1);
        DDR_end_eval();

        sprintf(data_str, "%u %u %u %u \n\r", i, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0);
        write_UART_THR(data_str);
    }


    while(1);

}




/* critical_task_start_eval
 *
 * Description: Reads the time stamp register for the first time.
 *
 * Note: TSCH contains the MSBs and TSCL the LSBs.
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void critical_task_start_eval(){

    t1_L = TSCL;
    t1_H = TSCH;
    t1 = (t1_H<<32) + t1_L; // Read the time stamp register

}


/* critical_task_start_eval
 *
 * Description: Reads the time stamp register a second time and makes the difference.
 *
 * Note: TSCH contains the MSBs and TSCL the LSBs.
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void critical_task_end_eval(){

    t2_L = TSCL;
    t2_H = TSCH;
    t2= (t2_H<<32) + t2_L; // Read the time stamp register
    result = t2-t1; // Obtain final execution time

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
        set_MSTID(0, 0x0); // Filter by Master ID
    }
    /* EMIF1, performance counter 1 */
    set_PERF_CNT_EVENT(1, 0x1);

    if (filter_events){
        enable_CNT_MSTID(1);
        set_MSTID(1, 0x0); // Filter by Master ID
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



