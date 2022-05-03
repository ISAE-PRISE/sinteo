/*--------------------------- arm_pmu_management.h ------------------------
 |  File arm_pmu_management.c
 |
 |  Description: The functions definition for the ARMv7 PMU management
 |               are done here
 |
 |  Version: 1V
 *-----------------------------------------------------------------------*/

#include <stdio.h>
#include "PMH.h"

// ARM performance counter ID to use
#define COUNTER_ID_0 0x0
#define COUNTER_ID_1 0x1
#define COUNTER_ID_2 0x2
#define COUNTER_ID_3 0x3
#define COUNTER_ID_4 0x4
#define COUNTER_ID_5 0x5

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
#define EVENT_ID_0   0x19
#define EVENT_ID_1   0x04
#define EVENT_ID_2   0x03
#define EVENT_ID_3   0x16
#define EVENT_ID_4   0x17
#define EVENT_ID_5   0x10


// ARM performance counter final read variables
unsigned value0f = 0, value1f = 0, value2f = 0, value3f = 0, value4f = 0, value5f = 0, valueCf = 0;

// Initializes the Armv7 performance counters with the events to track
void counters_init(){
    // Select counter to program: counter_number can be between 0-5
    select_evt_counter(COUNTER_ID_0);

    // Select event to track in selected counter: event_id numbers are in the A$
    event_track(EVENT_ID_0);

    select_evt_counter(COUNTER_ID_1);
    event_track(EVENT_ID_1);

    select_evt_counter(COUNTER_ID_2);
    event_track(EVENT_ID_2);

    select_evt_counter(COUNTER_ID_3);
    event_track(EVENT_ID_3);

    select_evt_counter(COUNTER_ID_4);
    event_track(EVENT_ID_4);

    select_evt_counter(COUNTER_ID_5);
    event_track(EVENT_ID_5);

}

// Resets the performance counters and starts counting
void critical_task_start_eval(){

    // Clear possible overflows of every counter
    clear_overflows();

    // Select counter to program: counter_number can be between 0-5
    select_evt_counter(COUNTER_ID_0);

    // Reset the actual value and enables of the counter and don't enable the d$
    reset_all_counters(0);

    select_evt_counter(COUNTER_ID_1);
    reset_all_counters(0);

    select_evt_counter(COUNTER_ID_2);
    reset_all_counters(0);

    select_evt_counter(COUNTER_ID_3);
    reset_all_counters(0);

    select_evt_counter(COUNTER_ID_4);
    reset_all_counters(0);

    select_evt_counter(COUNTER_ID_5);
    reset_all_counters(0);

    reset_all_counters(0);

    // Synchronize context (Instruction Synchronization Barrier)
    __asm__ __volatile("isb");

    // Enable counters
    enable_all_counters(0x3F);

}

// Stops the performance counters and retrieves the metrics 
void critical_task_end_eval(){

    // Disable counters
    disable_all_counters(0x3F);

    // Select general performance counter to read from
    select_evt_counter(COUNTER_ID_0);

    // Read value
    value0f=read_evt_counter();

    select_evt_counter(COUNTER_ID_1);
    value1f=read_evt_counter();

    select_evt_counter(COUNTER_ID_2);
    value2f=read_evt_counter();

    select_evt_counter(COUNTER_ID_3);
    value3f=read_evt_counter();

    select_evt_counter(COUNTER_ID_4);
    value4f=read_evt_counter();

    select_evt_counter(COUNTER_ID_5);
    value5f=read_evt_counter();

    // Read from the dedicated execution cycles performance counter
    valueCf = read_cycle_counter();

}

// Prints the metrics
void print_pmu_results(unsigned id){
    printf("%u %u %u %u %u %u %u %u \n\r", id, valueCf, value0f, value1f, value2f, value3f, value4f, value5f);
}






