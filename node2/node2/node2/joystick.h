#pragma once
#include "f_cpu.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "can.h"


struct Position {
	int8_t x;
	int8_t y;
};

struct ADCPosition {
	uint8_t x;
	uint8_t y;
};

enum direction {UP = 0, DOWN, RIGHT, LEFT, NEUTRAL};
	
	
struct ADCPosition joystick_read_position();

uint8_t slider_read_position(can_message new_msg);

uint8_t joystick_button_read_status(can_message new_msg);