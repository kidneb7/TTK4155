#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

int16_t controller_get_measurement();
int16_t controller_get_position();
int16_t controller_get_error();
int16_t controller_error(int16_t ref, int16_t meas);
int16_t controller_transfom_position();
float controller_speed();
int16_t controller_position(uint8_t reference);

