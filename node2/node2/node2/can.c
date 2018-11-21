#include "can.h"

uint8_t transmission_complete = 0;

 void can_init() {
	
	 mcp2515_init();
	 mcp2515_write(MCP_CANINTE, 0b00000101);				// Enable recieve and transmit buffer 0 interrupt
	 mcp2515_bit_modify(MCP_TXB0CTRL, (MCP_TXREQ), 0x00);	// clear transmit request bit
	 mcp2515_write(MCP_CANINTF, 0);							// Resetting all interrupt flags
	 
	 transmission_complete = 1;
	 mcp2515_write(MCP_CANCTRL, MODE_NORMAL);
	 
	 uint8_t value = mcp2515_read(MCP_CANSTAT);				// Read CAN status, check if in NORMAL MODE
	 if((value & MODE_MASK) == MODE_NORMAL) { 
		 printf("IN NORMAL MODE NODE 2\n\r"); 
	 }
 }
 
 void can_intr_init() {
	 DDRE &= ~(1 << PE0);		// configure as input pin
	 PCICR |= (1 << PCIE1);		// enables vector for INT15:8
	 PCMSK1 |= (1 << PCINT8);	// enables interrupt on PCINT8 pin
 }

 void can_message_send(can_message msg) {

	 if (transmission_complete) {
		 
		 uint8_t id_l = (msg.id & (0b111));
		 id_l = (id_l << 0x05);
		 mcp2515_write(MCP_TXB0SIDL, id_l);
		 
		 uint16_t id_h = (msg.id & (0b11111111000));
		 uint8_t id_h_2 = (id_h >> 0x03);
		 
		 mcp2515_write(MCP_TXB0SIDH, id_h_2);
		 
		 uint8_t dlc = 0x00;
		 dlc |= msg.length;
		 mcp2515_write(MCP_TXB0DLC, dlc);
		 
		 for (uint8_t i = 0; i < msg.length; i++) {
			 mcp2515_write(MCP_TXB0D0 + i, msg.data[i]);
		 }
		 
		 transmission_complete = 0;
		 
		 mcp2515_request_to_send(0);  // initiates msg transmission, buffer 0 of 2
	 }
 }

 void can_set_transmit_complete() { 
	 transmission_complete = 1;
 }
 

 can_message can_data_receive() {
	 
	can_message msg;
	 
	msg.id = (mcp2515_read(MCP_RXB0SIDH) << 3);
	msg.id |= ((mcp2515_read(MCP_RXB0SIDL) & 0b11100000) >> 5);
		 
	msg.length = (mcp2515_read(MCP_RXB0DLC) & 0b00001111);
		 
	for (uint8_t i = 0; i < msg.length; i++) {
		msg.data[i] = mcp2515_read(MCP_RXB0D0 + i);
	}
		 
	return msg;
}



