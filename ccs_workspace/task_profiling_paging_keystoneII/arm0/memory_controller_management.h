/*-------------------- memory_controller_management.h --------------------
 |  File memory_controller_management.h
 |
 |  Description: The functions declaration for Keystone II SDRAM
 |               controller management are done here
 |
 |  Version: 1
 *-----------------------------------------------------------------------*/

// EMIF0 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif0,t2_ddr_cycles_emif0, result_ddr_cycles_emif0, t1_ddr_evt0_emif0, t2_ddr_evt0_emif0, result_ddr_evt0_emif0, t1_ddr_evt1_emif0, t2_ddr_evt1_emif0, result_ddr_evt1_emif0;

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
void DDR_configure_eval(unsigned filter_events);


/* DDR_start_eval
 *
 * Description: Reads the performance counters for the first time.
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void DDR_start_eval();


/* DDR_end_eval
 *
 * Description: Reads the performance counters a final time and calculates the final time.
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void DDR_end_eval();


/* print_emif_results
 *
 * Description: Prints the results for the chosen DDR SDRAM events
 *
 * Parameter:
 *		- unsigned id: the identification number for the printed result
 *
 * Returns:     Nothing
 *
 * */
void print_emif_results(unsigned id);

