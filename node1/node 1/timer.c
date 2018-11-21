#include "timer.h"

void timer_intr_init(void) {
	// Enable CTC mode, compare with freq time
	TCCR3B |= (1 << WGM32);
	
	TCCR3B |= (1 << CS31); // Pre-scaler 8 */

	OCR3AH = 0x77; // 30719
	OCR3AL = 0xFF;

	TCNT3H = 0x00;
	TCNT3L = 0x00;
	
	ETIMSK |=  (1 << OCIE3A); // Interrupt enable

}

void timer_enable_intr() {
	ETIMSK |=  (1 << OCIE3A); // Interrupt enable
}

void timer_disable_intr() {
	ETIMSK &=  ~(1 << OCIE3A); // Interrupt disable
}
