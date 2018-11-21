#include "joystick.h"

const int TRESHOLD = 20;
const int LIMIT = 80;

uint8_t x_offset = 0;
uint8_t y_offset = 0;

struct ADCPosition joystick_read() {
	struct ADCPosition pos;
	volatile char *ext_adc_x = (char *) 0x1400; // start address for ADC.
	ext_adc_x[0] = 4;
	_delay_us(60);
	uint8_t read_joystick_x = ext_adc_x[0];
	pos.x = read_joystick_x - x_offset;
	
	_delay_us(60);
	volatile char *ext_adc_y = (char *) 0x1400; // start address for ADC.
	ext_adc_y[1] = 5;
	_delay_us(60);
	int read_joystick_y = ext_adc_y[1];
	pos.y = read_joystick_y - y_offset;
	
	return pos;
	
}

uint8_t slider_read() {
	volatile char *ext_adc_slider = (char *) 0x1400;  // start address for ADC
	ext_adc_slider[0] = 7;
	_delay_us(60);
	uint8_t slider_right = ext_adc_slider[0];
	return slider_right;
}

uint8_t joystick_button_read() {
	volatile char *ext_adc_button = (char *) 0x1400;  // start address for ADC
	ext_adc_button[0] = 6;
	_delay_us(60);
	uint8_t button = ext_adc_button[0];
	return button;
}

void joystick_init() {
	struct ADCPosition pos = joystick_read();
	x_offset = 0;
	y_offset = 0;
}

struct Position joystick_position() {

	struct ADCPosition adc_pos = joystick_read();
	struct Position position;
	
	position.x = (200/255.0)*adc_pos.x - 100; 
	position.y = (200/255.0)*adc_pos.y - 100; 
	
	return position;
}

enum direction joystick_direction() {
	struct Position pos = joystick_position();
	
	if (abs(pos.x) <= 5 && abs(pos.y) <= 5) {
		return NEUTRAL;
	}
	if (pos.x >= LIMIT && abs(pos.y) <= TRESHOLD) {
		return RIGHT;
	}
	if (pos.x <= -LIMIT && abs(pos.y) <= TRESHOLD) {
		return LEFT;
	}
	if (pos.y >= LIMIT && abs(pos.x) <= TRESHOLD) {
		return UP;
	}
	if (pos.y <= -LIMIT && abs(pos.x) <= TRESHOLD) {
		return DOWN;
	}
	return NEUTRAL;
};

void joystick_print_direction(){
	switch(joystick_direction()){
		case 0: {
			printf("UP\n\r");
			break;
		}
		case 1: {
			printf("DOWN\n\r");
			break;
		}
		case 2: {
			printf("RIGHT\n\r");
			break;
		}
		case 3: {
			printf("LEFT\n\r");
			break;
		}
		case 4: {
			printf("NEUTRAL\n\r");
			break;
		}
	}
};

void joystick_send_position(){
	static struct ADCPosition prev_position;
	struct ADCPosition new_position = joystick_read();
	
	static uint8_t prev_slider_pos;
	uint8_t slider_pos = slider_read();
	
	static uint8_t prev_button;
	uint8_t button = joystick_button_read();
	if (button < 5) {  // digital filtering
		button = 0;
	} else {
		button = 255;
	}
	
	if ((new_position.x == prev_position.x && new_position.y == prev_position.y) && (slider_pos == prev_slider_pos) && (prev_button == button)) {
		return; // Terminate function - no new position
	}
	
	can_message msg;
	msg.id = 20;
	msg.length = 4;
	msg.data[0] = new_position.x;
	msg.data[1] = new_position.y;
	msg.data[2] = slider_pos;
	msg.data[3] = button;

	can_message_send(msg);
	
	prev_position = new_position;
	prev_slider_pos = slider_pos;
	prev_button = button;
}
