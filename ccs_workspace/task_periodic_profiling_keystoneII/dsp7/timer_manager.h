/*--------------------------- timer_management.h -------------------------------------
 |  File timer_management.h
 |
 |  Description:  Provides functions related to the timer management.
 |                These functions are CSL dependent.
 |
 |  Version: 1.0V
 *-----------------------------------------------------------------------*/

#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

#include <ti/csl/csl_tmr.h>
#include <ti/csl/csl_tmrAux.h>

#include "../arm0/UART.h"


#define TIMER0_BASE_ADDRESS         (0x02200000) // Timer n = TIMER0_BASE_ADDRESS + n* 0x10000 for timer0 to timer15
#define TIMER_BASE_ADDRESS_SEP      (0x10000)
#define EMUMGT_CLKSPD_OFFSET        (0x004)



// Timer object
CSL_TmrHandle hTmr;


/* set_timer
 *
 * Description: Configures the timer to 64bit Timer mode. Currently, this function only make use of the 32LSBs.
 *              See information about the timers at https://www.ti.com/lit/ug/sprugv5a/sprugv5a.pdf?ts=1654252820280
 *
 * Parameter:
 *              - Uint8 timer_id: Indicates the timer unit to use.
 *              - Uint32 period_low: Indicates the real timer period for the 32-bit timer configuration in cycles.
 *                                   The clock value prescale is done internally by the function.
 *
 *
 * Returns:     Nothing
 *
 * */
void set_timer(Uint8 timer_id, Uint32 period_low){
    CSL_TmrObj                  TmrObj;
    CSL_Status                  status;
    CSL_TmrHwSetup              hwSetup = CSL_TMR_HWSETUP_DEFAULTS;

    // Open timer "timer_id"
    hTmr = CSL_tmrOpen(&TmrObj, timer_id, NULL, &status);

    if (hTmr == NULL)
        printf("Error during timer instantiation\n");


    // Retrieve clock divider value
    unsigned* EMUGT_reg = (unsigned *)(TIMER0_BASE_ADDRESS + timer_id*TIMER_BASE_ADDRESS_SEP + EMUMGT_CLKSPD_OFFSET);
    unsigned clk_div =  (*EMUGT_reg>>16)&0xF;


    // Set the timer mode to 64bit GP Timer Mode and set the PRD registers
    hwSetup.tmrTimerMode     = CSL_TMR_TIMMODE_GPT;
    hwSetup.tmrTimerPeriodLo = period_low/clk_div;
    hwSetup.tmrTimerCounterHi = 0;

    CSL_tmrHwSetup(hTmr, &hwSetup);

}

/* reset_timer
 *
 * Description: Resets the timer
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void reset_timer(){
    /* Reset the Timer */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET64, NULL);
}


/* start_timer
 *
 * Description: Starts the timer with counter autoreload capabilities
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void start_timer(){
    CSL_TmrEnamode TimeCountMode = CSL_TMR_ENAMODE_CONT_RELOAD; // CSL_TMR_ENAMODE_ENABLE = One-time mode ||  TimeCountMode = CSL_TMR_ENAMODE_CONT_RELOAD
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START64, (void *)&TimeCountMode);
}


/* stop_timer
 *
 * Description: Stops the timer
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void stop_timer(){
    CSL_TmrEnamode TimeCountMode = CSL_TMR_ENAMODE_DISABLE;
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_STOP64, (void *)&TimeCountMode);
}

/* close_timer
 *
 * Description: Removes the timer
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void close_timer(){
    /* Close the Tmr and interrupt handles */
    CSL_tmrClose(hTmr);
}


/* print_timer_count
 *
 * Description: Prints the current timer count
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void print_timer_count(){
    Uint32* counter = NULL;
    CSL_tmrGetTimLoCount(hTmr, counter);
    printf("Current count: %X \n", *counter);
}


#endif /* TIMER_MANAGER_H_ */
