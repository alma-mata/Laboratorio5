/*
 * Universidad del Valle de Guatemala
 * IE2023: Programacion de Microcontroladores
 * Laboratorio5.c
 * Autor: Alma Lisbeth Mata Ixcayau
 * Proyecto: Laboratorio 5
 * Descripcion: Control de servomotores y led con PWM
 * Creado: 10/04/2025
*/
/****************************************/
// Encabezado
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PWM1/PWM1.h"
#include "PWM2/PWM2.h"
#include "PWM3/PWM3.h"

/****************************************/
// Prototipos de función
void setup(void);
void ADC_Init(void);
uint16_t ADC_Read(void);

volatile uint16_t POT1 = 0;
volatile uint16_t POT2 = 0;
volatile uint16_t POT3 = 0;
volatile uint8_t canal_ADC = 0;
/****************************************/
// Función principal
int main(void) {
	// Configuracion inicial
	setup();
	
	while (1) {
		update_DutyCycle1(500 + (POT1 * 2000UL / 1023));
		update_DutyCycle2(500 + (POT2 * 2000UL / 1023));
		update_DutyCycle3(POT3 >> 2);
	}
}

/****************************************/
// Subrutinas sin Interrupcion
void setup(void){
	cli();
	ADC_Init();
	PWM1_Init();
	PWM2_Init();
	PWM3_Init();
	sei();
}

// Configuración ADC
void ADC_Init(void) {
	ADMUX = 0;
	ADMUX |= (1 << REFS0) | (canal_ADC & 0x07); // AVcc como referencia
	ADCSRA = 0;
	ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Habilitar ADC con prescaler de 128 (16MHz/128 = 125kHz)
	ADCSRA |= (1<<ADSC); // Inicia primera conversión del ADC
}

/****************************************/
// Subrutinas de Interrupcion
ISR(ADC_vect){
	switch (canal_ADC){
		case 0: POT1 = ADC; break;
		case 1: POT2 = ADC; break;
		case 2: POT3 = ADC; break;
	}
	canal_ADC = (canal_ADC + 1) % 3;
	ADMUX = (ADMUX & 0xF0) | (canal_ADC & 0x07);
	ADCSRA |= (1 << ADSC); // Volver a iniciar conversion
}