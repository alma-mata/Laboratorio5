/*
* Laboratorio5.c
* Control de servomotor con PWM usando Timer1 a 16MHz
* Author: Alma Mata
*/
/****************************************/
// Encabezado
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PWM1/PWM1.h"

/****************************************/
// Prototipos de función
void setup(void);
void ADC_Init(void);
uint16_t ADC_Read(void);

/****************************************/
// Función principal
int main(void) {
	// Configuracion inicial
	setup();
	
	while (1) {
		// Leer valor del potenciómetro (0-1023)
		uint16_t valor_ADC = ADC_Read();
		
		// Mapear ADC a ancho de pulso (2000-4000 = 1ms-2ms @ 16MHz, prescaler 8)
		uint16_t dutyCycle = (valor_ADC * 4000UL / 1023) + 1000;
		
		update_DutyCycle(dutyCycle); // Actualizar PWM
		_delay_ms(20); // Delay para estabilidad
	}
}

/****************************************/
// Subrutinas sin Interrupcion
void setup(void){
	cli();
	ADC_Init();
	PWM_Init();
	sei();
}

// Configuración ADC
void ADC_Init(void) {
	ADMUX = 0;
	ADMUX |= (1<<REFS0)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0); // AVcc como referencia
	ADCSRA = 0;
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Habilitar ADC con prescaler de 128 (16MHz/128 = 125kHz)
}

// Lectura del ADC
uint16_t ADC_Read(void) {
	ADCSRA |= (1 << ADSC); // Iniciar conversión
	while (ADCSRA & (1 << ADSC)); // Esperar hasta que la conversión se complete
	return ADC; // Retornar valor convertido
}