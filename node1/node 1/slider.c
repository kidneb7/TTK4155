#include "slider.h"

uint8_t slider_read_left() {
	volatile char *ext_adc_x = (char *) 0x1400; // start address for ADC.
	ext_adc_x[0] = 6;
	_delay_us(60);
	return ext_adc_x[0];
}

uint8_t slider_read_right() {
	volatile char *ext_adc_x = (char *) 0x1400; // start address for ADC.
	ext_adc_x[0] = 7;
	_delay_us(60);
	return ext_adc_x[0];
}