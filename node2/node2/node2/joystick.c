#include "joystick.h"

struct ADCPosition joystick_read_position(can_message new_msg) {
	
	static struct ADCPosition prev_position = {0, 0};

	
	//if (new_msg.id != 20) {
	//	return prev_position;
	//}
	
	struct ADCPosition new_position;
	new_position.x = new_msg.data[0];
	//printf("new msg data x %d %d\n\r", new_msg.data[0], new_msg.id);
	new_position.y = new_msg.data[1];
	
	prev_position = new_position;
	return new_position;	
}

uint8_t slider_read_position(can_message new_msg) {
	uint8_t slider_pos = new_msg.data[2];
	return slider_pos;
}

uint8_t joystick_button_read_status(can_message new_msg) {
	uint8_t button_status = new_msg.data[3];
	return button_status;
}