#include "mcp2515_driver.h"

uint8_t mcp2515_read(uint8_t addr) {
	PORTB &= ~(1 << PB7);			//Slave Select low
	PORTB &= ~(1 << PB0);
	spi_write(MCP_READ);			// Send read instruction
	spi_write(addr);				// Send address
	uint8_t result = spi_read();	
	PORTB |= (1 << PB7);			//Slave Select high
	PORTB |= (1 << PB0);
	return result;
}

void mcp2515_write(uint8_t addr, uint8_t data) {
	PORTB &= ~(1 << PB7);//Slave Select low
	PORTB &= ~(1 << PB0);
	spi_write(MCP_WRITE);
	spi_write(addr);
	spi_write(data);
	PORTB |= (1 << PB7);			//Slave Select high
	PORTB |= (1 << PB0);
}

void mcp2515_request_to_send(uint8_t buffer) {
	PORTB &= ~(1 << PB7);			//Slave Select low
	PORTB &= ~(1 << PB0);
	switch(buffer) {
		case 0: {
			spi_write(MCP_RTS_TX0);
			break;
		}
		case 1: {
			spi_write(MCP_RTS_TX1);
			break;
		}
		case 2: {
			spi_write(MCP_RTS_TX2);
			break;
		}
		default: {
			printf("Buffer number should be 0-2\n\r");
		}
	}

	PORTB |= (1 << PB7);			//Slave Select high
	PORTB |= (1 << PB0);
}

uint8_t mcp2515_read_status() { 
	PORTB &= ~(1 << PB7);			//Slave Select low
	PORTB &= ~(1 << PB0);
	spi_write(MCP_READ_STATUS);
	uint8_t status = spi_read();
	PORTB |= (1 << PB7);			//Slave Select high
	PORTB |= (1 << PB0);
	return status;
}

void mcp2515_bit_modify(uint8_t addr, uint8_t bitmask, uint8_t data) {  // not all registers apply - see register map mcp2515
	PORTB &= ~(1 << PB7);			//Slave Select low
	PORTB &= ~(1 << PB0);
	spi_write(MCP_BITMOD);
	spi_write(addr);
	spi_write(bitmask);
	spi_write(data);
	PORTB |= (1 << PB7);			//Slave Select high
	PORTB |= (1 << PB0);
}

void mcp2515_reset() {				// resets internal registers to default state
	PORTB &= ~(1 << PB7);			//Slave Select low
	PORTB &= ~(1 << PB0);
	spi_write(MCP_RESET);
	PORTB |= (1 << PB7);			//Slave Select high
	PORTB |= (1 << PB0);
}

uint8_t mcp2515_init() {
	spi_init();
	mcp2515_reset();
	_delay_us(60);
	uint8_t value = mcp2515_read(MCP_CANSTAT);
	if((value & MODE_MASK) != MODE_CONFIG) {
		printf("NOT IN CONFIG MODE\n\r");
		return 1;
	}
	return 0;
}
