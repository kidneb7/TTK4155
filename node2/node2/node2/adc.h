#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

void adc_init();
uint16_t adc_read();