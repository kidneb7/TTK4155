#pragma once

#include "dac.h"
#include "encoder.h"

#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

void motor_test(uint8_t val);
void motor_init();
void motor_enable(uint8_t enable);
void motor_set_direction(uint8_t direction);
void motor_set_speed(int16_t speed);
void motor_position_calibrate();
