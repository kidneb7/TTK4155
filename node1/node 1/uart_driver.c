#include "f_cpu.h"
#include "uart_driver.h"

#include <avr/io.h>

#define BAUD 9600 //Baud Rate
#define MYUBRR (F_CPU/16/BAUD-1)

void uart_init() {
	/* Set baud rate */
	UBRR0H = (MYUBRR>>8);
	UBRR0L = MYUBRR;

	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00);
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);

}

void uart_transmit(unsigned char data){
	/* Wait for empty transmit buffer */
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
