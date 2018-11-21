#include "controller.h"
#include "encoder.h"
#include "can.h"
#include "joystick.h"
#include "shooter.h"
#include "pwm.h"

volatile int16_t measurement = 0;
volatile int16_t position = 0;

int16_t error = 0;
int16_t error_i = 0;

int16_t prev_error = 0;

float K_p = 0.7;
float K_i = 0.1;
float K_d = 0;

float dt = 0.02;

int16_t controller_get_measurement() {
	return measurement;
}

int16_t controller_get_position() {
	return position;
}

int16_t controller_get_error() {
	return error;
}

int16_t controller_error(int16_t ref, int16_t meas) {
	
	if (meas >= ref) {
		return -(meas - ref);
	}
	else if (meas < ref) {
		return (ref - meas);
	}
}

int16_t controller_transfom_position() {
	return (measurement / 36);		// scales to approx. int16_t value range
}

int16_t controller_position(uint8_t reference) {
	measurement -= encoder_read(1);  // accumulating measured value
	position = controller_transfom_position();
	prev_error = error;
	error = controller_error(reference, position);
	error_i += error;
	
	if (error_i > 120) {			// anti-windup prevention
		error_i = 120;
	}
	else if (error_i < -120) {
		error_i = -120;
	}
	
	float u_f = K_p*error + K_i*error_i + (K_d*(error - prev_error))/(dt);
	int16_t u = (int16_t) (u_f + 0.5);
	
	if (error < 3 && error > -3) {  // dead band
		u = 0;
	}
	return u;
}
