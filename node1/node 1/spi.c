#include "spi.h"

void spi_init() {
	/* Set MOSI direction to output, SCK direction to output, and set Slave Select to output*/
	DDRB = (1 << DDB5) | (1 << DDB7) | (1 << DDB4);
	/* SPI control register 
	 * Bit 7: SPIE - Interrupt enable = 0
	 * Bit 6: SPE - SPI enable = 1
	 * Bit 5: DORD - Data order = 0 MSB first
	 * Bit 4: MSTR - Master / Slave select = 1 
	 * Bit 3: CPOL - Clock polarity = 0, leading edge rising
	 * Bit 2: CPHA - Clock Phase = 0, sample on leading edge
	 * Bit 1 and 0: SPR1, SPR0, = 0, 0 (F_CPU/4), Table 68 atmel, SPI clock rate select
	 */
	SPCR = (1 << SPE) | (1 << MSTR);
	
	PORTB |= (1 << PB4); //Slave Select high
}

void spi_write(uint8_t data) {
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF))) {

	}
	data = SPDR;
	return;
}

uint8_t spi_read() {
	spi_write(0b00000000); // dummy transmission
	return SPDR;
}
