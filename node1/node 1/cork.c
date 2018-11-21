/*Put old code that might come in handy at some point*/

/********* INNI WHILE LØKKA I MAIN ****************/
//TODO:: Please write your application code 
		//_delay_ms(500);
		//PORTA |= (1 << PA7);
		//uart_transmit('A');
		//_delay_ms(500);
		/*
		PORTA &= ~(1 << PA7);
		ext_ram[0] = 0;
		_delay_ms(200);
		ext_ram[1] = 1;
		_delay_ms(200);*/
		/*
		volatile char *ext_ram = (char *) 0x1200; // a (random) address for the OLED
		
		*ext_ram = 0;
		_delay_ms(200);
		
		ext_ram = 0x1400;  // outside ram memory area
		
		*ext_ram = 0;
		*/
		
		//struct Position read_joystick = joystick_position();
		
		//printf("x: %d | y: %d\n\r",read_joystick.x,read_joystick.y);
		
		//struct ADCPosition read_joystick_adc = joystick_read();
		
		//Dag 3:
		//printf("x: %d | y: %d\n\r",read_joystick_adc.x,read_joystick_adc.y);		
		
		//printf("Direction: %i\n\r", joystick_direction());
		
		//printf("Left: %d | Right: %d\n\r",slider_read_left(), slider_read_right());
		//joystick_print_direction();
		
		//oled_print_char('A');
		
		//oled_reset();
		//oled_reset_row_mask();
		
		
		//printf("Position: %d,%d\n\r", oled_get_postion().page, oled_get_postion().column);
		
		
		//if (joystick_direction() != NEUTRAL) {
			//static uint8_t var = 0;
			//uint8_t current_page = oled_get_postion().page;
			//uint8_t current_column = oled_get_postion().column;
			//if (joystick_direction() == DOWN && var != 1) {
				//oled_goto_pos(current_page + 1, current_column);
				//var = 1;
				//printf("DOWN\n\r");
				//printf("Position: %d,%d\n\r", oled_get_postion().page, oled_get_postion().column);
			//}
			//if (joystick_direction() == UP && var != 1) {
				//oled_goto_pos(current_page - 1, current_column);
				//var = 1;
				//printf("UP\n\r");
				//printf("Position: %d,%d\n\r", oled_get_postion().page, oled_get_postion().column);
			//}
		//} else if (joystick_direction() == NEUTRAL) {
			//var = 0;
		//}
/************** END INNI WHILE LØKKA I MAIN **************/

/************** SRAM TEST ******************************/
/*void SRAM_test(void) {
	
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n\r");
	
	// rand() stores some internal state, so calling this function in a loop will yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n\r", write_errors, retrieval_errors);
}*/
/************** END SRAM TEST **************************/


/*Inside oled.c, navigate LEFT


			//menu_level* child = menu_get_element_by_pos(current_head, current_page);
			//printf("oled menu navigate, child name: %s\r\n",child->name);
			//current_head = current_head->parent;
			//current_head->head
			//menu_level* parent = current_head->parent;
			//printf(parent->name);
			
			//printf("oled menu navigate, current head: %s\r\n",current_head->name);
			
			*/