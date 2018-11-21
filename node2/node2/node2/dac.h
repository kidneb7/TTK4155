#pragma once
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "twi.h"

void dac_init();

void dac_send(uint8_t data_byte);