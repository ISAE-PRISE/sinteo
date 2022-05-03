/*--------------------------- UART.h -------------------------------------
 |  File UART.h
 |
 |  Description: This file provides basic functions for managing the
 |  UART device for the Keystone II TCI6636K2H platform
 |
 |  Version: 2.1V
 *-----------------------------------------------------------------------*/

#ifndef UART_H_
#define UART_H_

#include "string.h"

#define UART1_BASE_ADDRESS           (0x0002530C00)
#define UART_THR_MASK         (0x000000FF)
#define TX_FIFO_E_MASK         (0x00000020)


// Choose UART from where data is transmitted
unsigned const UART_BASE = UART1_BASE_ADDRESS;


void write_UART_THR(char str[]);
int read_UART_LSR();
void clear_tx_FIFO();
void enable_FIFO();
int read_UART_IER();
void write_UART_IER(unsigned value);


/* write_UART_THR
 *
 * Description: Sends the information through the UART
 *
 * Parameter:
 *              - char str[]: String of data to transmit
 *
 * Returns:     Nothing
 *
 * */
void write_UART_THR(char str[]){
    unsigned* address = (unsigned*)UART_BASE;
    unsigned i = 0;
    unsigned value = 0;

    // Check UART availability until the whole data is transmitted
    while(i <= strlen(str)){
        // Transmit hold register(TX FIFO) is empty. The transmission is not necessarily complete.
        if((read_UART_LSR()&TX_FIFO_E_MASK) == 0x20){
            value = (unsigned)str[i];
            *address = value & UART_THR_MASK;
            i++;
        }
    }

}

/* read_UART_LSR
 *
 * Description: Reads the register UART_LSR which reports the line status.
 *              See meaning of fields at: https://www.ti.com/lit/ug/sprugp1/sprugp1.pdf?ts=1646758757775 (Table 3-12 Line Status Register (LSR) Field Description)
 *
 * Parameter:   None
 *
 * Returns:     The register value
 *
 * */
int read_UART_LSR(){
    unsigned* UART_LSR = (unsigned*)(UART_BASE + 0x14);
    return *UART_LSR;
}


/* clear_tx_FIFO
 *
 * Description: Clears the TX FIFO filed of the UART_FCR register
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void clear_tx_FIFO(){
    unsigned* UART_FCR = (unsigned*)(UART_BASE + 0x08);
    *UART_FCR = *UART_FCR |(1<<2);
}


/* enable_FIFO
 *
 * Description: Enables the TX and RX FIFOs
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void enable_FIFO(){
    unsigned* UART_FCR = (unsigned*)(UART_BASE + 0x08);
    *UART_FCR = *UART_FCR |(1<<0);
}

/* read_UART_IER
 *
 * Description: Reads the register UART_IER which deals with the interrupts enabling
 *              See meaning of fields at: https://www.ti.com/lit/ug/sprugp1/sprugp1.pdf?ts=1646758757775 (Table 3-4 Interrupt Enable Register (IER) Field Descriptions)
 *
 * Parameter:   None
 *
 * Returns:     The register value
 *
 * */
int read_UART_IER(){
    unsigned* address = (unsigned*)(UART_BASE + 0x4);
    return *address;
}

/* write_UART_IER
 *
 * Description: Writes the register UART_IER which deals with the interrupts enabling
 *              See meaning of fields at: https://www.ti.com/lit/ug/sprugp1/sprugp1.pdf?ts=1646758757775 (Table 3-4 Interrupt Enable Register (IER) Field Descriptions)
 *
 *
 * Parameter:
 *            - unsigned value: Value of the UART_IER register
 *
 * Returns:     Nothing
 *
 * */
void write_UART_IER(unsigned value){
    unsigned* address = (unsigned*)(UART_BASE + 0x4);
    *address = value;
}


#endif /* UART_H_ */
