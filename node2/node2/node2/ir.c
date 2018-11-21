#include "ir.h"

const uint16_t threshold = 100;
const int measurements = 3;

int is_blocked = 0;

void ir_init() {
	adc_init();
	ir_is_blocked();
}

uint8_t ir_is_blocked() {
	uint16_t ir_value = 0;
	for (int i = 0; i < measurements; i++) {
		ir_value += adc_read();
	}
	if (ir_value <= threshold*measurements && !is_blocked) {
		is_blocked = 1;
		return 1;
	}
	else if (ir_value > threshold*measurements && is_blocked){
		is_blocked = 0;
	}
	return 0;
}

uint8_t score_count(uint8_t reset) {
	static score = 0;
	if (ir_is_blocked()) {
		score++;
	}
	if (reset) {
		score = 0;
	}
	return score;
} 