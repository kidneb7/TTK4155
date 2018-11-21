#pragma once

#include "f_cpu.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static volatile int encoder_val = 0;

void encoder_reset();
void encoder_init();
int encoder_read(uint8_t reset);
void encoder_position();
int8_t encoder_get_value();