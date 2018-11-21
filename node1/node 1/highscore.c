#include "highscore.h"

uint16_t highscores[8] ={0, 0, 0, 0, 0, 0, 0, 0};
uint8_t length = 8;

void highscore_sort() {
	uint16_t temp;
	for (uint8_t i = 0; i < length; i++) {
		for (uint8_t j = 0; j < length; j++) {
			if (highscores[j] < highscores[i]) {
				temp = highscores[i];
				highscores[i] = highscores[j];
				highscores[j] = temp;
			}
		}
	}
}

void highscore_update(uint16_t score) {
	highscore_sort();
	
	uint8_t index = -1;
	
	for (uint8_t i = 0; i < length; i++) {
		if (score >= highscores[i]) {
			index = i;
			break;
		}
	}
	
	if (index != -1) {
		for (uint8_t i = length-1; i > index; i--) {
			highscores[i] = highscores[i - 1];
		}
		highscores[index] = score;
	}

}

uint16_t* highscore_get_list() {
	return highscores;
}