#pragma once

#include "f_cpu.h"
#include "spi.h"
#include "mcp2515.h"

#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t mcp2515_read(uint8_t addr);
void mcp2515_write(uint8_t addr, uint8_t data);
void mcp2515_request_to_send(uint8_t buffer);
uint8_t mcp2515_read_status();
void mcp2515_bit_modify(uint8_t addr, uint8_t bitmask, uint8_t data);
void mcp2515_reset();
uint8_t mcp2515_init();