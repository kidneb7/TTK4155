#pragma once
#include <stdio.h>

void uart_init_2();
void uart_transmit_2(unsigned char data);
unsigned char uart_recieve_2(void);
FILE* uart_printf_2();

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