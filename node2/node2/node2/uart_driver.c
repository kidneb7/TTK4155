#include "f_cpu.h"
#include "uart_driver.h"
#include <avr/io.h>
#define BAUD 9600 //Baud Rate

#define FOSC 16000000UL // system clock frequency. Skal være 1843200 ?
#define MYUBRR (FOSC/16/BAUD-1)

/*

#define UBRR0H		0xC5
#define UBRR0L		0xC4

#define UCSR0C		0xC2
#define USBS0		0x03
#define UCSZ00		0x01

#define UCSR0B		0xC1
#define RXEN0		0x04
#define TXEN0		0x03

#define UCSR0A		0xC0
#define UDRE0		0x05

#define UDR0		0xC6

#define RXC0		0x07

*/

void uart_init() {
	/* Set baud rate */
	UBRR0H = (MYUBRR>>8);
	UBRR0L = MYUBRR;
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);

	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
	
}

void uart_transmit(unsigned char data){
	/* Wait for empty transmit bugger */
	while ( !(UCSR0A & (1<<UDRE0)) )
	;
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char uart_recieve(void){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)))
	;
	/* Get and return received data from buffer */
	return UDR0;
}

FILE* uart_printf() {
	return fdevopen(uart_transmit, uart_recieve);
}
