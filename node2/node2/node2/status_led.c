#include "status_led.h"

void status_led_init() {
	DDRD |= (1 << PD3);
	PORTD |= (1 << PD3);
}

void status_led_toggle() {
	//printf("toggle\n\r");
	static volatile uint8_t counter = 0;
	static uint8_t led_on = 1;
	if (led_on && (counter % 256 == 0)) {
		PORTD &= ~(1 << PD3);
		led_on = 0;
	}
	else if (!led_on && (counter % 256 == 0)) {
		PORTD |= (1 << PD3);
		led_on = 1;
	}
	counter++;
}
