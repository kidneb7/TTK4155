#include "pwm.h"

uint16_t pwm_DUTY(uint8_t input) {
	if (input >= 0 && input <= 255) {  // unint8_t cast guarantees 0-255 value
		return TOP*(0.00019608*(double)input+0.05);
	}
	return 0.075*TOP;
}