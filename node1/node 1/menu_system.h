#pragma once

#include <stddef.h>

#include "joystick.h"

typedef struct Menu_level {
	char* name;
	
	// traverse same level
	struct menu_level* next;
	struct menu_level* prev;
	
	// sub menu traverse
	struct menu_level* child;
	struct menu_level* parent;
} menu_level;

menu_level* menu_create(char* name);
menu_level* menu_create_linked_list(char* string_array[], int length);
menu_level* menu_get_element(menu_level* list, char* element);
menu_level* menu_get_element_by_pos(menu_level* list, uint8_t page);
menu_level* menu_get_parent(menu_level* node);
menu_level* menu_get_child(menu_level* node);
void menu_insert_submenu(menu_level* node, menu_level* child);
menu_level* menu_get_head(menu_level* list);