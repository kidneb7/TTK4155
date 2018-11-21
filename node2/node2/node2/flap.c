#include "flap.h"

void flap_open(){
	timer_flap_set_DUTY(pwm_DUTY(0));
}

void flap_close(){
	timer_flap_set_DUTY(pwm_DUTY(128));
}