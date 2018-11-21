#include "menu_system.h"

menu_level* menu_create(char* name) {
	menu_level* new_menu_item = malloc(sizeof(menu_level));
	
	new_menu_item->name = name;
	new_menu_item->next = NULL;
	new_menu_item->prev = NULL;
	new_menu_item->child = NULL;
	new_menu_item->parent = NULL;
	
	return new_menu_item;
}

menu_level* menu_create_linked_list(char* string_array[], int length) {

	menu_level* head = menu_create(string_array[0]);
	menu_level* prev = head;
	
	for (int i = 1; i < length; i++) {
		menu_level* new_item = menu_create(string_array[i]);
		new_item->prev = prev;
		prev->next = new_item;
		prev = new_item;
	}
	
	return head;
}

menu_level* menu_get_element(menu_level* list, char* element) {
	menu_level* node = list;
	menu_level* prev = NULL;

	while (node != NULL) {
		if (node->name == element) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

menu_level* menu_get_element_by_pos(menu_level* list, uint8_t page) {
	menu_level* node = list;
	
	for (uint8_t i = 0; i < page; i++) {
		node = node->next;
	}
	return node;
}

menu_level* menu_get_parent(menu_level* node) {
	return node->parent;
}

menu_level* menu_get_child(menu_level* node) {
	return node->child;
}

void menu_insert_submenu(menu_level* node, menu_level* child) {
	node->child = child;
	printf("menu insert submenu node: %s\r\n",node->name);
	child->parent = node;
	printf("menu insert submenu child: %s\r\n",child->name);
	
	// Make the parent node the parent for all nodes in the submeny
	
	menu_level* ptr = child;
	while (1) {
		ptr->parent = node;
		if (ptr->next == NULL) {
			break;
		}
		ptr = ptr->next;
	}
	
	
	
	
}

//void menu_navigate() {
	//static uint8_t var = 0;
	//if (joystick_direction() != NEUTRAL) {
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
//}

menu_level* menu_get_head(menu_level* list) {
	menu_level* prev;
	menu_level* node = list;
	
	while (node->prev != NULL) {
		prev = node->prev;
	}
	
	return node;
}