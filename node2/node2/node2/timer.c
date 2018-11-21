#include "timer.h"

void timer_init() {
	DDRB |= (1 << DDB5);  // set PB5/Oc1A direction as output
	
	//Clock select bits: CSN2:0=1
	 TCCR1B  |= (1 << CS11) | (1 << WGM13) | (1 << WGM12);
	 uint8_t mask = 0xFF;
	 mask &= ~(1 << CS12) | ~(1 << CS10);
	 TCCR1B &= mask;
	
	//COM1An; Clear OC1A on compare match | Set OC1A at BOTTOM. WGM1n: Set Fast PWM, TOP = ICRn, update OCRnx at BOTTOM, TOVn flag set og TOP.
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	mask = 0xFF;
	mask &= ~(1 << COM1A0) | ~(1 << WGM10);
	TCCR1A &= mask;

	ICR1H = 0x9E;
	ICR1L = 0x34;
	
	timer_set_DUTY(0.075*TOP);

}

void timer_set_DUTY(uint16_t duty) {
	if (duty >= 0.05*TOP && duty <= 0.1*TOP) {
		OCR1AH = duty >> 8;
		OCR1AL = duty & 0xFF;
	}
}

void timer_intr_init() {
 // Enable CTC mode, compare with freq time 
	TCCR3B |= (1 << WGM32); 
	
	TCCR3B |= (1 << CS31); // Pre-scaler 8 */

	OCR3AH = 0x9C; // 39999
	OCR3AL = 0x3F;

	TCNT3H = 0x00;
	TCNT3L = 0x00;
	
	TIMSK3 |=  (1 << OCIE3A); // Interrupt enable

}

void timer_enable_intr() {
	TIMSK3 |=  (1 << OCIE3A); // Interrupt enable
}

void timer_disable_intr() {
	TIMSK3 &=  ~(1 << OCIE3A); // Interrupt disable
}

void timer_flap_init() {
	DDRL |= (1 << DDL3);  // set PL3/Oc5A direction as output
	
	//Clock select bits: CSN2:0=1
	 TCCR5B  |= (1 << CS51) | (1 << WGM53) | (1 << WGM52);
	 uint8_t mask = 0xFF;
	 mask &= ~(1 << CS52) | ~(1 << CS50);
	 TCCR5B &= mask;
	
	//COM5An; Clear OS5A on compare match | Set OC5A at BOTTOM. WGM1n: Set Fast PWN, TOP = ICRn, update OCRnx at BOTTOM, TOVn flag set og TOP.
	TCCR5A |= (1 << COM5A1) | (1 << WGM51);
	mask = 0xFF;
	mask &= ~(1 << COM5A0) | ~(1 << WGM50);
	TCCR5A &= mask;

	ICR5H = 0x9E;
	ICR5L = 0x34;
	
	flap_close();
}

void timer_flap_set_DUTY(uint16_t duty) {
	
	if (duty >= 0.05*TOP && duty <= 0.1*TOP) {
		OCR5AH = duty >> 8;
		OCR5AL = duty & 0xFF;
	}
}















/////////////////////////////////////////////




unsigned int TIM16_ReadTCNT1(void) {
	unsigned char sreg;
	unsigned int i;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts */ 
	__disable_interrupt();
	/* Read TCNTn into i */
	i = TCNT1;
	/* Restore global interrupt flag */
	SREG = sreg;
	return i;
}

void TIM16_WriteTCNT1(unsigned int i) {
	unsigned char sreg;
	/* Save global interrupt flag */ 
	sreg = SREG;
	/* Disable interrupts */
	__disable_interrupt();
	/* TCNTn to i */
	TCNT1 = i;
	/* Restore global interrupt flag*/
	SREG = sreg;
}

/////////////////////////////////////////

