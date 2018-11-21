#include "status_led.h"

void status_led_init() {
	DDRB |= (1 << PB0);
	PORTB |= (1 << PB0);
}

void status_led_toggle() {
	static uint8_t counter = 0;
	static uint8_t led_on = 1;
	if (led_on && (counter % 128 == 0)) {
		PORTB &= ~(1 << PB0);
		led_on = 0;
	}
	else if (!led_on && (counter % 128 == 0)) {
		PORTB |= (1 << PB0);
		led_on = 1;
	}
	counter++;
}
