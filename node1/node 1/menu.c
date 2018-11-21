/* SHOULD BE DELETED AT SOME POINT */

#include "menu.h"
/*
void invert_bitmap(){
		
}
*/

menu_item *menu_item_create(char name[]){
	menu_item *item = malloc(sizeof(menu_item)); //allocates memory for struct menu_item
	item->name = name;
	item->next = NULL;
	item->prev = NULL;
	item->parent = NULL;
	item->child = NULL;
	return item;
}

	//char *items[][8] = {{"Start"}, {"Settings", "Fonts", "Brightness"}, {"High scores"}};

/*

menu_item* menu_item_init(char** items) {
	menu_item *item;
	menu_item *head = NULL;
	menu_item *prev = NULL;
	
	int length = sizeof(items)/sizeof(*items[0]);
	
	printf("Length of outer array: %d\n", length);
	
	for(int i = 0; i < length; i++) {
		
		item = menu_item_create(&items[i][0]);
		
		printf(item->name);
		 
		if (i == 0) {
			head = item;
			prev = item;
		}
		else {
			item->prev = prev;
			prev->next = item;
		}
		
		int length_submenu = sizeof(items[i]) / sizeof(items[i][0]) ;
		menu_item *prev_sub = NULL;
		for (int j = 1; j < length_submenu; j++) {
			
			
			menu_item* subitem = menu_item_create(&items[i][j]);
			
			subitem->parent = item;
			
			if (j == 1) {
				item->child = subitem;
				prev_sub = subitem;
			}
			else {
				subitem->prev = prev_sub;
				prev_sub->next = subitem;
			}
		}
	}
	return head;
}

*/

menu* new_menu_item(char* name) {
	menu* new_item = malloc(sizeof(menu));
	new_item->name = name;
	new_item->next = NULL;
	new_item->prev = NULL;
	
	return new_item;
}

char* main_menu[] = {"Main menu" "Start", "Settings", "High score"};
	
char* settings_menu[] = {"Settings", "Fonts", "Brightness"};
	
char* high_score_menu[] = {"High score", "All time", "This hour"};
	
void create_menu_system() {
	
}