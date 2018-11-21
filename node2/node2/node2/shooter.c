#include "shooter.h"

static uint8_t activated = 0;

void shooter_init() {
	DDRD |= (1 << DDD2);	//Set direction output
	PORTD |= (1 << PD2);	//Set pin high (active low)
}

void shooter_on() {
	PORTD &= ~(1 << PD2);	//Set pin low (active low)
	activated = 1;
}

void shooter_off() {
	_delay_ms(100);
	PORTD |= (1 << PD2);	//Set pin high
	activated = 0;
	_delay_ms(10);
}

uint8_t shooter_get_status() {
	return activated;
}