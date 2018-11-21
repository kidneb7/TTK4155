#pragma once
#include "f_cpu.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include "menu_system.h"

typedef enum mem_adr_mode {HORIZONTAL, VERTICAL, PAGE} Mem_adr_mode;
	
typedef struct oled_Position {
	int page;
	int column;
} oled_postion;

menu_level* oled_get_curr_node();
void oled_write_cmd(uint8_t value);
void oled_write_data(uint8_t value);
void oled_init();
void oled_set_mem_mode(Mem_adr_mode mode);
uint8_t oled_goto_row(uint8_t row);    // returns 1 if line out-of-bounds
void oled_goto_column(uint8_t column);
void oled_goto_page(uint8_t page);
void oled_goto_pos(uint8_t page, uint8_t column);
oled_postion oled_get_postion();
void oled_go_home();
void oled_reset();
void oled_reset_row_mask();
void oled_write_pixel(uint8_t row, uint8_t column);
void oled_print_char(char character);
void oled_print_string(char* str);
void oled_print_arrow(uint8_t column);
void oled_print_menu(menu_level* menu_head);
void oled_menu_print_cursor(uint8_t column);
void oled_print_highscores(uint16_t* h_list);
void oled_menu_navigate(menu_level* current_head, int reset);
void oled_clear();
void oled_clear_columns(uint8_t start, uint8_t end);