/* TTK4155 NODE 1 */

#include "f_cpu.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "uart_driver.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "menu.h"
#include "menu_system.h"
#include "spi.h"
#include "mcp2515_driver.h"
#include "can.h"
#include "status_led.h"
#include "highscore.h"
#include "pixelart.h"
#include "timer.h"

enum states {INIT, MENU_INIT, MENU_NAV, GAME, GAME_OVER, HIGH_SCORE_INIT, HIGH_SCORE, IDLE, DEFAULT};

menu_level* current_menu_head = NULL;

static can_message msg; // static?

ISR(TIMER3_COMPA_vect) {
	joystick_send_position();
}

ISR(INT1_vect) {
	if (mcp2515_read(MCP_CANINTF) & (MCP_RX0IF)) {
		msg = can_data_receive();
		mcp2515_bit_modify(MCP_CANINTF, (0b00000001), 0x00);	// reset interrupt flag
	}
	if (mcp2515_read(MCP_CANINTF) & (MCP_TX0IF)) {
		can_set_transmit_complete();
		mcp2515_bit_modify(MCP_CANINTF, (0b00000100), 0x00);	// reset interrupt flag
	}
}

int main(void) {
	cli();
	//DDRA = 0xFF; // def port A output
	uart_init();
	uart_printf();
	printf("IT WORKS\n\r");
	MCUCR |= (1 << SRE); //Enables external memory interface
	oled_init();
	_delay_us(10);
	oled_reset();
	
	joystick_init();
		
	can_init();
	timer_intr_init();
	can_intr_init();
	sei();
	timer_disable_intr();
	status_led_init();
	
	msg = can_msg_reset();
	
	/* --- allocates memory from menu linked lists --- */
	char* main_menu_strings[] = {"Play", "Highscore", "Misc.", "Settings"};
	char* misc_menu_strings[] = {"How to play", "Credits"};
	char* settings_menu_strings[] = {"Difficulty"};
	
	menu_level* main_menu_head = menu_create_linked_list(main_menu_strings, 4);
	menu_level* misc_menu_head = menu_create_linked_list(misc_menu_strings, 2);
	menu_level* settings_menu_head = menu_create_linked_list(settings_menu_strings, 1);
	
	menu_insert_submenu(menu_get_element(main_menu_head, "Misc."), misc_menu_head);
	menu_insert_submenu(menu_get_element(main_menu_head, "Settings"), settings_menu_head);
		
	enum states state = INIT;
	
    while(1) {
		
		//msg = can_data_receive();
		
		switch(state) {
			case INIT: {
				
				state = MENU_INIT;
				
				break;
			}
			case MENU_INIT: {
				
				oled_print_menu(main_menu_head);
				
				current_menu_head = main_menu_head;
				state = MENU_NAV;
				
				break;
			}
			case MENU_NAV: {
				
				oled_menu_navigate(current_menu_head, 0);
				
				if ((oled_get_curr_node()->name == "Play") && (joystick_button_read() == 0)) {
					can_message start_game; 
					start_game.id = 5;
					start_game.length = 1;
					start_game.data[0] = 0;
					can_message_send(start_game);
					state = GAME;
				}
				if ((oled_get_curr_node()->name == "Highscore") && (joystick_button_read() == 0)) {
					state = HIGH_SCORE_INIT;
				}
				
				break;
			}
			case GAME: {
				//msg = can_data_receive();
				if (msg.id == 10) {
					timer_disable_intr();
					state = GAME_OVER;
				} 
				else {
					timer_enable_intr();
					//joystick_send_position();  // sending CAN message
				}
				
				break;
			}
			case GAME_OVER: {
				
				
				uint16_t score = (msg.data[1] << 8) + msg.data[0];
				
				char game_over_string[8];
				
				sprintf(game_over_string, "Score: %u", score);
				
				printf("%s\n\r", game_over_string);
				
				oled_clear();
				oled_go_home();
				oled_goto_pos(3,(128/2)-((8*8)/2));
				oled_print_string(game_over_string);
				
				_delay_ms(5000);
				
				oled_reset();
				oled_menu_navigate(current_menu_head, 1);
				highscore_update(score);
				msg = can_msg_reset();
				state = MENU_INIT;
				
				break;
			}
			case HIGH_SCORE_INIT: {
				uint16_t* h_list = highscore_get_list();
				oled_clear();
				oled_go_home();
				oled_print_highscores(h_list);
				state = HIGH_SCORE;
				break;
			}
			case HIGH_SCORE: {
				static uint8_t cnt = 0;
				cnt++;
				if (joystick_direction() == LEFT) {
					oled_clear();
					oled_reset();
					oled_menu_navigate(current_menu_head, 1);
					state = MENU_INIT;
				}
				
				break;
			}
			case IDLE: {
				break;
			}
			case DEFAULT: {
				break;
			}
		}
			
		_delay_us(60);
		
		status_led_toggle();
    }
}
