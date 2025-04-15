/*
* Laboratorio5.c
* Control de servomotor con PWM usando Timer1 a 16MHz
* Author: Alma Mata
*/
#include <avr/io.h>
#include "PWM1.h"

void PWM1_Init(void) {
	// PB1 (OC1A) como salida (Arduino D9)
	DDRB |= (1 << PINB1);
	
	// Modo Fast PWM con ICR1 como TOP (Modo 14)
	TCCR1A = (1 << COM1A1) | (1 << WGM11); // Clear OC1A on compare match, set at BOTTOM (non-inverting)
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
	
	ICR1 = 39999; // Periodo PWM para 50Hz (16MHz/(8*50Hz) - 1 = 39999)
	OCR1A = 3000; // Ancho de pulso inicial (1.5ms - posición neutra)
}

// Establece el ancho de pulso en ticks del Timer1
void update_DutyCycle1(uint16_t dutyCycle) {
	OCR1A = dutyCycle;
}