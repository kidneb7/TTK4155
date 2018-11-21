#include "oled.h"
#include "fonts.h"

volatile char* OLED_CMD_BASE_ADDR = (char*) 0x1000;
volatile char* OLED_DATA_BASE_ADDR = (char*) 0x1200;

#define PAGES 8
#define ROWS 64
#define COLS 128

uint8_t curr_row;
uint8_t curr_col = 0;
uint8_t curr_page = 0;

menu_level* curr_node = NULL;

uint8_t row_mask[PAGES] = {0};
	
menu_level* oled_get_curr_node() {
	return curr_node;
}

void oled_write_cmd(uint8_t value) {
	*OLED_CMD_BASE_ADDR = value;
	_delay_us(10);
}

void oled_write_data(uint8_t value) {
	*OLED_DATA_BASE_ADDR = value;
	_delay_us(10);
}

void oled_init() {
	oled_write_cmd(0xAE);	// Display off
	oled_write_cmd(0xA1);	// Segment remap
	oled_write_cmd(0xDA);	// Com pads HW: alt
	oled_write_cmd(0x12);	//
	oled_write_cmd(0xC8);	// Com output scan dir: com63..com0
	oled_write_cmd(0xA8);	// Multiplex ration mode: 63
	oled_write_cmd(0x3F);
	oled_write_cmd(0xD5);	// Display divide ratio/osc. freq mode
	oled_write_cmd(0x80);
	oled_write_cmd(0x81);	// Contrast mode
	oled_write_cmd(0x50);
	oled_write_cmd(0xD9);	//Set pre-charge period
	oled_write_cmd(0x21);
	oled_write_cmd(0x20);	//Set Memory Addressing Mode
	oled_write_cmd(0x00);	// horizontal mode 
	oled_write_cmd(0xDB);   // VCOM deselect level mode
	oled_write_cmd(0x30);
	oled_write_cmd(0xAD);	// master configuration
	oled_write_cmd(0x00);
	oled_write_cmd(0xA4);	//out follows RAM content
	oled_write_cmd(0xA6);	// set normal display
	oled_write_cmd(0xAF);	// display on
	oled_write_cmd(0xA5);	// entire display ON
	_delay_ms(1000);
	oled_write_cmd(0xA4); // Resume to RAM content
}

void oled_set_mem_mode(Mem_adr_mode mode) {
	oled_write_cmd(0x20);
	oled_write_cmd(mode);
}

void oled_goto_column(uint8_t column) {			// zero-indexed column number
	if (column > COLS) {
		return;
	}
	
	curr_col = column;
	
	oled_write_cmd(0x21);						// set column address command
	oled_write_cmd(column);						// column start address
	oled_write_cmd(floor((COLS - 1)));			// column end address
}

void oled_goto_page(uint8_t page) {
	if (page > PAGES) {
		return;
	}
	
	curr_page = page;
	
	oled_write_cmd(0x22);						// initiate page start address command
	oled_write_cmd(page);						// set start page
	oled_write_cmd(PAGES - 1);					// end page address
}

void oled_goto_pos(uint8_t page, uint8_t column) {
	oled_goto_page(page);
	oled_goto_column(column);
}

oled_postion oled_get_postion() {
	oled_postion pos = {curr_page, curr_col};
	return pos;	
}

void oled_go_home() {
	oled_goto_pos(0, 0);
}

void oled_reset() {						// For horizontal mode
	
	oled_go_home();
	
	oled_write_cmd(0x21);				// set column address command
	oled_write_cmd(0x00);				// column start address
	oled_write_cmd(0x7F);				// column end address
	
	oled_write_cmd(0x22);				// initiate page start address command
	oled_write_cmd(0x00);				// set start page
	oled_write_cmd(PAGES - 1);			// end page address
	for (uint8_t i = 0; i < 8; i++) {
		for (uint8_t j = 0; j < 128; j++) {
			oled_write_data(0b00000000);
		}
	}
}

void oled_print_char(char character) {
	for (int i = 0; i < 8; i++) {
		oled_write_data(pgm_read_word(&font8[character - 32][i])); // Writes bitmask at cursor position placed by goto_column
	}

}

void oled_print_string(char* str) {
	uint8_t i = 0;
	while (str[i] != '\0') {
		oled_print_char(str[i]);
		i++;
	}
}

void oled_clear() {
	
	oled_write_cmd(0x21);				// set column address command
	oled_write_cmd(0x00);				// column start address
	oled_write_cmd(0x7F);				// column end address
	
	oled_write_cmd(0x22);				// initiate page start address command
	oled_write_cmd(0x00);				// set start page
	oled_write_cmd(PAGES - 1);			// end page address
	for (uint8_t i = 0; i < 8; i++) {
		for (uint8_t j = 0; j < 128; j++) {
			oled_write_data(0b00000000);
		}
	}
}
 
void oled_print_arrow(uint8_t column) {
	oled_goto_column(column);
	oled_write_data(0b00011000);
	oled_write_data(0b00011000);
	oled_write_data(0b01111110);
	oled_write_data(0b00111100);
	oled_write_data(0b00011000);
}

void oled_clear_columns(uint8_t start, uint8_t end) {
	for (uint8_t page = 0; page < PAGES; page++) {
		for (uint8_t column = start; column < end; column++) {
			oled_goto_pos(page, column);
			oled_write_data(0b00000000);
		}
	}
}

void oled_print_menu(menu_level* menu_head) {
	menu_level* node = menu_head;
	int page = 0;
	
	oled_go_home();
	oled_clear();

	oled_goto_column(COLS-16);
	oled_print_string("*");
	oled_go_home();
	
	while(node != NULL) {
		oled_print_string(node->name);
		
		if (node->child != NULL) {
			oled_print_arrow(COLS-8); // Print arrow if menu item has submenu
		}
		
		page++;
		oled_goto_pos(page, 0);
		node = node->next;
	}
	
	oled_go_home();
}

void oled_menu_print_cursor(uint8_t column) {
	oled_print_arrow(column);
}

void oled_print_highscores(uint16_t* h_list) {
	for (uint8_t i = 0; i < (PAGES); i++) {
		oled_goto_pos(i,0);
		char score[12];
		if (h_list[i] <= 9) {
			sprintf(score, "Score:   %u", h_list[i]);
		}
		else if (h_list[i] > 9 && h_list[i] <= 99) {
			sprintf(score, "Score:  %u", h_list[i]);
		}
		else {
			sprintf(score, "Score: %u", h_list[i]);
		}
		oled_print_string(score);
	}
}

void oled_menu_navigate(menu_level* current_head, int reset) {
	static uint8_t var = 0;		// local variable to prevent continuous scrolling
	static uint8_t first_time_baby = 0;
	static menu_level* current_node = NULL;
	if (reset) {
		first_time_baby = 0;
	}
	if (first_time_baby == 0) {
		current_node = current_head;
		first_time_baby++;
	}
	if (joystick_direction() != NEUTRAL) {
		uint8_t current_page = oled_get_postion().page;
		uint8_t current_column = oled_get_postion().column;
		if (joystick_direction() == DOWN && var != 1 && current_node->next != NULL) {
			current_node = current_node->next;
			oled_goto_pos(current_page + 1, current_column);
			
			uint8_t page = oled_get_postion().page;
			uint8_t column = oled_get_postion().column;
			
			oled_clear_columns(COLS-16, COLS-8);
			oled_goto_pos(page, column);
			
			oled_goto_column(COLS-16);
			oled_print_string("*");
			
			var = 1;
		}
		else if (joystick_direction() == UP && var != 1 && current_node->prev != NULL) {
			current_node = current_node->prev;
			oled_goto_pos(current_page - 1, current_column);
			
			uint8_t page = oled_get_postion().page;
			uint8_t column = oled_get_postion().column;
			
			oled_clear_columns(COLS-16, COLS-8);
			oled_goto_pos(page, column);
			
			oled_goto_column(COLS-16);
			oled_print_string("*");
			
			var = 1;
		}
		else if (joystick_direction() == LEFT && var != 1 && current_node->parent != NULL) {
			current_node = current_head;
			oled_print_menu(current_head);
			var = 1;
		}
		else if (joystick_direction() == RIGHT && var != 1) {
			if (current_node->child != NULL) {
				menu_level* parent = menu_get_element_by_pos(current_head, current_page);
				current_head = parent->child;
				current_node = current_head;
				var = 1;
				
				oled_go_home();
				current_page = 0;
				oled_print_menu(current_head);
			}
		}
	}
	else if (joystick_direction() == NEUTRAL) {
		var = 0;
	}
	
	curr_node = current_node;
}

/* --- NOT IN USE --- */
uint8_t oled_goto_row(uint8_t row) {			// zero-indexed display line number (row)
	if (row > ROWS) {
		return 255;
	}
	
	oled_write_cmd(0x22);						// initiate page start address command
	uint8_t page = floor(row/PAGES);
	oled_write_cmd(page);						// set start page
	oled_write_cmd(PAGES - 1);					// end page address
	
	//row_mask[page] = 0x00;
	row_mask[page] |= (1 << row%(PAGES));
	
	return row_mask[page];						// returns row on page that is set
}

void oled_write_pixel(uint8_t row, uint8_t column) {
	uint8_t myRow = oled_goto_row(row);			// Returns bitmask and places cursor at correct PAGE
	oled_goto_column(column);					// Places cursor at correct column
	
	oled_write_data(myRow);						// Writes bitmask from goto_row at cursor position places by goto_column
}
