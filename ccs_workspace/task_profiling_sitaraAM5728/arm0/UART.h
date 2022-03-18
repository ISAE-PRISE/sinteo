/*--------------------------- UART.h -------------------------------------
 |  File UART.h
 |
 |  Description: This file provides basic functions for managing the
 |  UART device for the Sitara AM5728 platform
 |
 |  Version: 2V
 *-----------------------------------------------------------------------*/

#ifndef UART_H_
#define UART_H_

#include "string.h"

// Sitara AM5728 UARTs
#define UART1  0x4806A000;
#define UART2  0x4806C000;
#define UART3  0x48020000; // Debug UART
#define UART4  0x4806E000;
#define UART5  0x48066000;
#define UART6  0x48068000;
#define UART7  0x48420000;
#define UART8  0x48422000;
#define UART9  0x48424000;
#define UART10  0x4AE2B000;

#define UART_THR_MASK         (0x000000FF)
#define TX_FIFO_E_MASK         (0x00000020)


// Choose UART from where data is transmitted
unsigned const UART_BASE = UART3;


void write_UART_THR(char str[]);
int read_UART_LSR();
void clear_tx_FIFO();
void enable_FIFO();
int read_UART_IER();
void write_UART_IER(int value);


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
    unsigned* address = UART_BASE;
    unsigned i = 0;
    unsigned value = 0;

    // Check UART availability until the whole data is transmitted
    while(i <= strlen(str)){
        // Transmit hold register(TX FIFO) is empty. The transmission is not necessarily complete.
        if((read_UART_LSR()&TX_FIFO_E_MASK) == 0x20){
            value = (int)str[i];
            *address = value & UART_THR_MASK;
            i++;
        }
    }

}

/* read_UART_LSR
 *
 * Description: Reads the register UART_LSR which reports the line status.
 *              See fields meaning at: https://www.ti.com/lit/ug/spruhz6l/spruhz6l.pdf (Table 24-212. UART_LSR)
 *
 * Parameter:   None
 *
 * Returns:     The register value
 *
 * */
int read_UART_LSR(){
    unsigned* UART_LSR = UART_BASE + 0x14;
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
    unsigned* UART_FCR = UART_BASE + 0x08;
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
    unsigned* UART_FCR = UART_BASE + 0x08;
    *UART_FCR = *UART_FCR |(1<<0);
}

/* read_UART_IER
 *
 * Description: Reads the register UART_IER which deals with the interrupts enabling
 *              See fields meaning at: https://www.ti.com/lit/ug/spruhz6l/spruhz6l.pdf (Table 24-188. UART_IER)
 *
 * Parameter:   None
 *
 * Returns:     The register value
 *
 * */
int read_UART_IER(){
    unsigned* address = UART_BASE + 0x4;
    return *address;
}

/* write_UART_IER
 *
 * Description: Writes the register UART_IER which deals with the interrupts enabling
 *
 * Parameter:   None
 *
 * Returns:     Nothing
 *
 * */
void write_UART_IER(int value){
    unsigned* address = UART_BASE + 0x4;
    *address = value;
}


#endif /* UART_H_ */
