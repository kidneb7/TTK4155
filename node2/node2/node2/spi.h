#pragma once

#include "f_cpu.h"

#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>

void spi_init();
void spi_write(uint8_t data);
uint8_t spi_read();
