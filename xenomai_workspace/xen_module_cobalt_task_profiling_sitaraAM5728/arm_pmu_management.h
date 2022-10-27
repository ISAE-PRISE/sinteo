/*--------------------------- arm_pmu_management.h ------------------------
 |  File arm_pmu_management.h
 |
 |  Description: The functions declaration for the ARMv7 PMU management
 |               are done here
 |
 |  Version: 1.0 
 *-----------------------------------------------------------------------*/


/* counters_init
 *
 * Description: Sets the events for each ARM Cortex A15 performance counters
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void counters_init();


/* critical_task_start_eval
 *
 * Description: Prepares the performance counters for its use by:
 *              clearing a possible overflow flag,
 *              reseting the configuration of each counter
 *              and activating all of them at once
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void critical_task_start_eval();


/* critical_task_end_eval
 *
 * Description: Deactivates all performance counters at once and reads the event values for each of them
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void critical_task_end_eval();


/* print_pmu_results
 *
 * Description: Prints the results for the chosen events
 *
 * Parameter:
 *		- unsigned id: the identification number for the printed result
 *
 * Returns:     Nothing
 *
 * */
void print_pmu_results(unsigned id);

