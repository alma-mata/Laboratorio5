/*
* Laboratorio5.c
* Control de servomotor con PWM usando Timer1 a 16MHz
* Author: Alma Mata
*/
#include <avr/io.h>
#include "PWM2.h"

void PWM2_Init(void) {
	// PB2 (OC1B) como salida (Arduino D10)
	DDRB |= (1 << PINB2);
	
	// Modo Fast PWM con ICR1 como TOP (Modo 14)
	TCCR1A |= (1 << COM1B1); // Clear OC1B on compare match, set at BOTTOM (non-inverting)

	OCR1B = 3000;
}

// Establece el ancho de pulso en ticks del Timer1
void update_DutyCycle2(uint16_t dutyCycle) {
	OCR1B = dutyCycle;
}
