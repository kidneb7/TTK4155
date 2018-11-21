#include "adc.h"

void adc_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= (1 << MUX0);
}

uint16_t adc_read() {
	ADCSRA |= (1 << ADSC);
	return ADC;
}