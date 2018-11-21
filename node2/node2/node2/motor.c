#include "motor.h"

#define MOTOR_CTRL	PORTH
#define DIR			PH1
#define SEL			PH3
#define EN			PH4
#define OE			PH5
#define RST			PH6

#define RIGHT_DIR	1
#define LEFT_DIR	0

const uint8_t middle = 255/2;
const uint8_t thres = 4;

void motor_init() {
	DDRH |= (1 << DIR) | (1 << SEL) | (1 << EN) | (1 << OE) | (1 << RST);
	MOTOR_CTRL |= (1 << EN); // motor enabled
}

void motor_enable(uint8_t enable) {
	if (enable) {
		MOTOR_CTRL |= (1 << EN);	// motor enabled
	}
	else {
		MOTOR_CTRL &= ~(1 << EN);	// motor disabled
	}
}

void motor_set_direction(uint8_t direction) {
	if (direction == RIGHT_DIR) {
		MOTOR_CTRL |= (1 << DIR);
	}
	else if (direction == LEFT_DIR) {
		MOTOR_CTRL &= ~(1 << DIR);
	}
}

void motor_set_speed(int16_t speed) {
	uint8_t u_speed = 0;
	if (speed > thres) {
		motor_set_direction(RIGHT_DIR);
		u_speed = 2*speed + 1;
	}
	else if (speed < -thres) {
		motor_set_direction(LEFT_DIR);
		u_speed = 2*speed - 1;
	}
	dac_send(speed);
}

void motor_position_calibrate() {
	int16_t value = encoder_read(1);
	int16_t prev_value = value + 1;
	motor_set_speed(-20);
	int i = 0;
	while (/*prev_value != value*/ i < 20) {
		prev_value = value;
		value = encoder_read(1);
		_delay_ms(100);
		motor_set_speed(-5);
		_delay_ms(100);
		i++;
	}
	dac_send(0);
	encoder_reset();
	_delay_ms(100);
}


