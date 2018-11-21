#pragma once

#include "f_cpu.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

void status_led_init();

void status_led_toggle();