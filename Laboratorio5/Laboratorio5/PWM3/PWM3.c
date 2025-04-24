/*
 * Universidad del Valle de Guatemala
 * IE2023: Programacion de Microcontroladores
 * PWM3.c
 * Autor: Alma Lisbeth Mata Ixcayau
 * Proyecto: Laboratorio 5
 * Descripcion: Control de servomotor con PWM manual con Timer0 a 16MHz
 * Creado: 22/04/2025
*/

#include "PWM3.h"

uint8_t contador_PWM = 0;
uint8_t limite_contador = 0;

void PWM3_Init(void){
	DDRD |= (1 << PIND5);	// Salida PD5
	TCCR0A = 0; 
	TCCR0B = (1 << CS01) | (1 << CS00);  //Prescaler de 64
	
	TIMSK0 = (1<<TOIE0);	// Interrupcion por overflow del timer 0
	TCNT0 = 255;
}

void update_DutyCycle3(uint16_t dutyCycle){
	limite_contador = dutyCycle;
}

ISR(TIMER0_OVF_vect) // Interrupcion para PWM manual
{
	if (contador_PWM >= limite_contador)
	{
		PORTD = 0;
	}
	else
	{
		PORTD = 0b00100000;
	}
	contador_PWM += 1;
	TCNT0 = 255;
}