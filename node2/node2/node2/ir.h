#pragma once

#include "adc.h"

void ir_init();
uint8_t ir_is_blocked();
uint8_t score_count(uint8_t reset);
