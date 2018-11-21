/* TTK4155 NODE 2 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart_driver.h"
#include "can.h"
#include "joystick.h"
#include "timer.h"
#include "pwm.h"
#include "dac.h"
#include "adc.h"
#include "ir.h"
#include "motor.h"
#include "encoder.h"
#include "shooter.h"
#include "status_led.h"

enum states {INIT, IN_GAME_INIT, IN_GAME, END_GAME, IDLE, DEFAULT};
	
static can_message msg;

static volatile uint8_t button = 255;

uint8_t counter = 0;
uint16_t score = 0;

ISR(TIMER3_COMPA_vect) {
	
	counter++;
	if (counter > 50) {
		score++;
		counter = 0;
	}
	
	if (msg.id == 20) {						// USB-card data for game and controller
		uint8_t slider = slider_read_position(msg);
		button = joystick_button_read_status(msg);
		struct ADCPosition pos = joystick_read_position(msg);
		
		int16_t control = controller_position(slider);
		
		motor_set_speed(control);			// feedback control
		
		timer_set_DUTY(pwm_DUTY(pos.x));	// control servo with PWM
		
	}
}

ISR(PCINT1_vect) {
	if (mcp2515_read(MCP_CANINTF) & (MCP_RX0IF)) {
		msg = can_data_receive();
		mcp2515_bit_modify(MCP_CANINTF, (0b00000001), 0x00);
	}
	if (mcp2515_read(MCP_CANINTF) & (MCP_TX0IF)) {
		can_set_transmit_complete();
		mcp2515_bit_modify(MCP_CANINTF, (0b00000100), 0x00);
	}
}

int main(){
	
	cli();
	
	uart_init();
	uart_printf();
	can_init();
	can_intr_init();
	timer_init();
	timer_flap_init();
	dac_init();
	ir_init();
	motor_init();
	encoder_init();
	shooter_init();
	status_led_init();

	sei();  // enable global interrupt
	
	msg.id = 999;
	msg.length = 1;
	msg.data[0] = 0;
	
	enum states state = INIT;
	
	while (1) {

		switch(state) {
			case INIT: {
				motor_enable(0);
				flap_close();
				
				timer_intr_init();
				timer_disable_intr();
				
				state = IDLE;
				
				break;
			}
			case IN_GAME_INIT: {
				motor_enable(1);
				timer_enable_intr();
				flap_open();
				shooter_off();
				
				printf("START GAME!\n\r");
				
				state = IN_GAME;
				
				break;
			}
			case IN_GAME: {
				if (button == 0 && !shooter_get_status()) {
					shooter_on();
				}
				else if (button != 0 && shooter_get_status()) {
					shooter_off();
				}
				if (ir_is_blocked()) {
					flap_close();
					state = END_GAME;
				}
				break;
			}
			case END_GAME: {
				motor_enable(0);
				timer_disable_intr();
				
				printf("YOU LOSE! %d\n\r", score);
				
				can_message game_over;
				game_over.id = 10;
				game_over.length = 2;
				game_over.data[0] = (score & 0xFF);
				game_over.data[1] = ((score & ~0xFF) >> 8);
				
				can_message_send(game_over);
				
				counter = 0;
				score = 0;
				
				state = IDLE;
				
				break;
			}
			case IDLE: {
				if (msg.id == 5) {
					
					state = IN_GAME_INIT;
				}
				break;
			}
			case DEFAULT: {
				break;
			}
		}
		_delay_us(60);
		status_led_toggle();
	}
	
	return 0;
}

