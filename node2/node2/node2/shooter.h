#pragma once

#include "f_cpu.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void shooter_init();
void shooter_off();
void shooter_on();
uint8_t shooter_get_status();