#pragma once

#include "f_cpu.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

void highscore_sort();

void highscore_update(uint16_t score);

uint16_t* highscore_get_list();

