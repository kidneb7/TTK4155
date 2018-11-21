#pragma once

#include "f_cpu.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

void timer_intr_init(void);

void timer_enable_intr();

void timer_disable_intr();