/*************************************************************************
 * SINTEO project
 * Copyright (C) 2022 ISAE-SUPAERO / ONERA
*************************************************************************/

/*--------------------------- main.c -------------------------------------
 |  File main.c
 |
 |  Description:  A timer is configured and the interruption captured
 |                in order to periodically send events measurements from the
 |                DDR SDRAM controller.
 |
 |  Caveats: The program running on this DSP sends SDRAM profiling information
 |           from either an ARM or another DSP running in parallel.
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

// CSL libraries
#include <ti\csl\soc\k2h\src\cslr_device.h>
#include <ti/csl/csl.h>
#include <ti/csl/csl_cache.h>
#include <ti/csl/csl_cacheAux.h>
#include <ti/csl/src/intc/csl_intc.h>
#include <ti/csl/src/intc/csl_intcAux.h>

#include <stdio.h>

#include "timer_manager.h"
#include "../arm0/UART.h"
#include "../arm0/DDR3MemoryController.h"


/* ----------------------- GLOBAL FUNCTIONS --------------------------- */

static Int32 intc_init (void);
static void timer_interrupt_handler (void *arg);
void send_measurements();
Int32 timer_int_setup (Uint8 event);
void DSP_init();
void main();


/* --------------- GLOBAL VARIABLES DEFINITIONS ----------------------- */

// Whether to send the profiling data or not
#define MEASUREMENTS

// Interruption event ID of TIMER_8_INTL (check Table 8-22. System Event Mapping in https://www.ti.com/lit/ds/sprs866g/sprs866g.pdf?ts=1651595161047&ref_url=https%253A%252F%252Fwww.google.com%252F)
Uint8 timer_event_int =  66;
unsigned const TIMER_ID = 8;

// INTC Objects
CSL_IntcObj                  tmrIntcObj;
CSL_IntcContext              context;
CSL_IntcEventHandlerRecord   EventHandler[30];
CSL_IntcHandle              tmrIntcHandle;


// DSP frequency
#define DSP_CLK_FREQ 1.2
// Timer period in cycles
unsigned const SLEEP_CYCLES = DSP_CLK_FREQ*10000000; // 10ms

// EMIF0 performance counters initial and final read variables
unsigned ddr_cycles_emif0, ddr_evt0_emif0, ddr_evt1_emif0;


#ifdef MEASUREMENTS

// Maximum size of measurement to store
#define QUANTITY_OF_MEASUREMENTS 1000

// Array with the stored profiling measurements
unsigned meas_array[QUANTITY_OF_MEASUREMENTS];
unsigned meas_cnt = 0;

// Synchronization flag. Placed on the MSMC SDRAM.
unsigned* task_finished_flag;
unsigned* task_start_flag;

#endif


/* intc_init
 *
 * Description: Enables and initializes the C66x DSP interruptions
 *
 * Parameter:
 *              None
 *
 * Returns:     Error identifier
 *
 * */
static Int32 intc_init(void){
    CSL_IntcGlobalEnableState   state;

    /* INTC module initialization */
    context.eventhandlerRecord = EventHandler;
    context.numEvtEntries      = 10;
    if (CSL_intcInit(&context) != CSL_SOK)
        return -1;

    /* Enable NMIs */
    if (CSL_intcGlobalNmiEnable() != CSL_SOK)
        return -1;

    /* Enable global interrupts */
    if (CSL_intcGlobalEnable(&state) != CSL_SOK)
        return -1;

    /* INTC has been initialized successfully. */
    return 0;
}


/* timer_interrupt_handler
 *
 * Description: Retrieve the DDR SDRAM measurements from the SDRAM controller and send them via UART once the task under analysis is finished.
 *
 * Parameter:
 *              - void *arg: The event that generated the interruption.
 *
 * Returns:     Nothing
 *
 * */
static void timer_interrupt_handler(void *arg){

#ifdef MEASUREMENTS

    meas_array[meas_cnt] = get_PERF_CNT_TIMER();
    meas_cnt++;
    meas_array[meas_cnt] = get_PERF_CNT_1();
    meas_cnt++;
    meas_array[meas_cnt] = get_PERF_CNT_2();
    meas_cnt++;

    if(*task_finished_flag == 1){
        // Stop timer and interruptions
        stop_timer();
        CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTDISABLE, NULL);

        // Send captured data
        unsigned cnt = 0;
        for(cnt = 0; cnt < meas_cnt; cnt=cnt+3){
            char data_str[64];
            sprintf(data_str, "%u %u %u %u \n\r", cnt/3, meas_array[cnt]-meas_array[0], meas_array[cnt+1]-meas_array[1], meas_array[cnt+2]-meas_array[2]);
            write_UART_THR(data_str);
        }

        write_UART_THR("***********\n\r");

        // Restart timer and interruptions
        meas_cnt = 0;
        start_timer();
        CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);

        // Reset flags
        *task_finished_flag = 0;
        *task_start_flag = 1;
    }


#endif

    CSL_intcEventClear((CSL_IntcEventId)arg);

}


/* timer_int_setup
 *
 * Description: Enables and configures the timer interruption "timer_event_int" for the C66x DSP.
 *
 * Parameter:
 *              - Uint8 event: Event that causes the interruption.
 *
 * Returns:     Error identifier
 *
 * */
Int32 timer_int_setup(Uint8 event){
    CSL_TmrObj                  TmrObj;
    CSL_IntcEventHandlerRecord  EventRecord;
    CSL_IntcParam               vectId;

    // Clear local data structures
    memset(&TmrObj, 0, sizeof(CSL_TmrObj));

    // Open the interrupt controller INTC
    vectId = CSL_INTC_VECTID_12;
    tmrIntcHandle = CSL_intcOpen(&tmrIntcObj, event, &vectId, NULL);

    // Bind the interrupt service routine ISR to our event
    EventRecord.handler = (CSL_IntcEventHandler)&timer_interrupt_handler;
    EventRecord.arg     = (void *)event;
    CSL_intcPlugEventHandler(tmrIntcHandle, &EventRecord);

    // Event enable
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);

    // Return success.
    return 0;
}


/* DSP_init
 *
 * Description: Configures the DSP core caches and cacheability of the physical addresses
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void DSP_init(){


    // Enabling the DDR memory caching (0x80000000-0xFFFFFFFF) by configuring the MAR bits
    unsigned i = 0;
    for(i = 0; i < 128; i++)
        CACHE_disableCaching(i);
    for(i = 128; i < 255; i++)
        CACHE_enableCaching(i);


    //  Enabling and setting the cache L2 size
    CACHE_setL2Size(CACHE_1024KCACHE);
    CACHE_setL1DSize(CACHE_L1_32KCACHE);
    CACHE_setL1PSize(CACHE_L1_32KCACHE);


    // Make MSMC SRAM uncacheable through address re-mapping using the MPAX unit
    // See TMS320C66x DSP User guide at https://www.ti.com/lit/ug/sprugw0c/sprugw0c.pdf?ts=1655201467225&ref_url=https%253A%252F%252Fwww.google.com%252F
    unsigned* XMPAXH4_reg = (unsigned*)0x08000024;
    unsigned* XMPAXL4_reg = (unsigned*)0x08000020;


    *XMPAXH4_reg = 0;
    *XMPAXL4_reg = 0;

    // MPAX --> 0x0D000000 (Reserved space) = 0x0C000000 (MSMC SRAM space)
    *XMPAXH4_reg = *XMPAXH4_reg|(0x22A00<<12); // BADDR     Input address = 0x22A00XXX
    *XMPAXH4_reg = *XMPAXH4_reg|0x14;          // SEGSZ     0x14 = 2MB of re-addressing
    *XMPAXL4_reg = *XMPAXL4_reg|(0x00C000<<8); // RADDR     Output address = 0x00C0000XX
    *XMPAXL4_reg = *XMPAXL4_reg|0x3F;          // PERM      0x3F = Read/Write/Execute in supervisor and user mode


    task_finished_flag = (unsigned *) 0x22A00000;  // MPAX --> 0x22A00000 (Reserved space) = 0x0C000000 (MSMC SRAM space)
    task_start_flag = (unsigned *) (0x22A00000 + sizeof(unsigned));     // MPAX --> 0x22A00004 (Reserved space) = 0x0C000004 (MSMC SRAM space)

}


void main(){
    // Initialize DSP
    DSP_init();

    // Initialize the INTC Module
    if (intc_init() < 0){
        printf ("Error: Initialization of the INTC module failed\n");
        return;
    }

    // Initialize timer CSL module
    CSL_tmrInit(NULL);

    // Start the testing for the 64bit General Purpose Timer
    if (timer_int_setup(timer_event_int) < 0){
        printf("Error: Testing 64bit Timer in Single Shot Mode FAILED\n");
        return;
    }

    // Configure Timer 8
    set_timer(TIMER_ID, SLEEP_CYCLES);

    // Start timer counter
    start_timer();


    // Do nothing. Just wait for interruption.
    while (1);


}

