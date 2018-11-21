#pragma once
/* SHOULD BE DELETED AT SOME POINT */

#include <stddef.h>

/*
Menysystem
* Start
* Difficulty ????
* Highscore
* Credits
*/

typedef struct menu_item {
	char *name;
	//up down
	struct menu_item *prev;
	struct menu_item *next;
	 //left right
	struct menu_item *parent;
	struct menu_item *child;
} menu_item;


typedef struct menu {
	char* name;
	struct menu* next;
	struct menu* prev;
	struct menu* sub_menu[8];
} menu;


//menu_item *menu_item_create(char* name);

//char *subitems[] = {[], ["Fonts", "Brightness"] }

//menu_item* menu_item_init(char** items);

//menu_item main_menu_list[] = {menu_start, menu_highscore, menu_credits};