#pragma once

#include <stdio.h>

void uart_init();
void uart_transmit(unsigned char data);
unsigned char uart_recieve(void);
FILE* uart_printf();