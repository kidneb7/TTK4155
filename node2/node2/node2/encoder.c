#include "encoder.h"

#define MOTOR_CTRL	PORTH
#define DIR			PH1
#define SEL			PH3
#define EN			PH4
#define OE			PH5
#define RST			PH6

#define ENCODER_OUT	PINK

uint16_t pos = 0;
int8_t enc = 0;

void encoder_reset() {
	MOTOR_CTRL &= ~(1 << RST);
	_delay_us(20);
	MOTOR_CTRL |= (1 << RST);
}

void encoder_init() {
	DDRH |= (1 << DIR) | (1 << SEL) | (1 << EN) | (1 << OE) | (1 << RST);
	DDRK = 0x00;
	MOTOR_CTRL |= (1 << EN); // motor enabled	
	encoder_reset();
}

int16_t encoder_read(uint8_t reset) {
	
	int16_t encoder_data = 0;
	uint8_t high_byte = 0;
	uint8_t low_byte = 0;
	MOTOR_CTRL &= ~(1 << OE);
	
	MOTOR_CTRL &= ~(1 << SEL);  // read high byte
	_delay_us(20);
	high_byte = ENCODER_OUT;
	
	MOTOR_CTRL |= (1 << SEL);  // read low byte
	_delay_us(20);
	low_byte = ENCODER_OUT;
	
	if (reset) {
		encoder_reset();
	}
	MOTOR_CTRL |= (1 << OE);

	encoder_data = (high_byte << 8) + low_byte;  // casting two's complement
	return encoder_data;
}

void encoder_position() {
	pos += encoder_read(0);
	uint16_t prev_pos = pos;
	if (pos != prev_pos) {
			pos = (~pos) + 1;
	}
}

int8_t encoder_get_value(){
	return enc;
}
