#include "dac.h"

void dac_init() {
	TWI_Master_Initialise();
}

void dac_send(uint8_t data_byte) {
	uint8_t slave_address = 0b01010000;
	uint8_t command_byte = 0x00;  // addressing dac0
	
	uint8_t dac_data[3] = {slave_address, command_byte, data_byte};
		
	TWI_Start_Transceiver_With_Data(dac_data, 3);
}