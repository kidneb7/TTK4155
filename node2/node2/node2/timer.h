#pragma once
#include <stdlib.h>
#include <avr/io.h>
#include "flap.h"

#include <avr/interrupt.h>

#define TOP			0x9E34
#define BOTTOM		0x0000
#define MIDDLE		0x4F1A

void timer_init();
void timer_set_DUTY(uint16_t duty);
void timer_intr_init();
void timer_enable_intr();
void timer_disable_intr();
void timer_flap_init();
void timer_flap_set_DUTY(uint16_t duty);

