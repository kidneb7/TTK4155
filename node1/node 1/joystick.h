#pragma once

#include "f_cpu.h"
#include "can.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct Position {
	int8_t x;
	int8_t y;
};

struct ADCPosition {
	uint8_t x;
	uint8_t y;
};

enum direction {UP = 0, DOWN, RIGHT, LEFT, NEUTRAL};

struct ADCPosition joystick_read();
void joystick_init();
struct Position joystick_position();
enum direction joystick_direction();
void joystick_print_direction();
void joystick_send_position();
uint8_t slider_read();
uint8_t joystick_button_read();