/*--------------------------- emif_management.h --------------------------
 |  File emif_management.h
 |
 |  Description: The functions declaration for Sitara AM5728 emif management
 |               are done here
 |
 |  Version: 1.1
 *-----------------------------------------------------------------------*/


/* DDR_configure_eval
 *
 * Description: Sets the performance counters events and master (MSTID) from who the event are captured.
 *
 *
 * Parameter:
 *              - unsigned filter_events: Chooses whether to filter by master ID or to globally analyze the system
 *              - void* emif0_addr: Indicates the base address of the EMIF 0
 *              - void* emif1_addr: Indicates the base address of the EMIF 1
 *
 * Returns: Nothing
 *
 * */
void DDR_configure_eval(unsigned filter_events, void* emif0_addr, void* emif1_addr);


/* DDR_start_eval
 *
 * Description: Reads both EMIFs performance counters for the first time.
 *
 * Parameter:
 *              - void* emif0_addr: Indicates the base address of the EMIF 0
 *              - void* emif1_addr: Indicates the base address of the EMIF 1
 *
 * Returns: Nothing
 *
 */
void DDR_start_eval(void* emif0_addr, void* emif1_addr);


/* DDR_end_eval
 *
 * Description: Reads both EMIFs performance counters a last time and calculates the final time.
 *
 * Parameter:
 *              - void* emif0_addr: Indicates the base address of the EMIF 0
 *              - void* emif1_addr: Indicates the base address of the EMIF 1
 *
 * Returns: Nothing
 *
 * */
void DDR_end_eval(void* emif0_addr, void* emif1_addr);


/* print_emif_results
 *
 * Description: Prints the results for the chosen DDR SDRAM events
 *
 * Parameter:
 *				- unsigned id: the identification number for the printed result
 *
 * Returns:     Nothing
 *
 * */
void print_emif_results(unsigned id);

