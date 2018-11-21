#pragma once

#include "mcp2515.h"
#include "mcp2515_driver.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct Can_message {
	uint16_t id;
	uint8_t length; 
	uint8_t data[8]; 
	
	} can_message; 

void can_init();
void can_intr_init();
can_message can_msg_reset();
void can_message_send(can_message msg);
void can_set_transmit_complete();
can_message can_data_receive();