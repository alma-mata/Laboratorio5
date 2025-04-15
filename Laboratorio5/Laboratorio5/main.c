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
#include "PWM2/PWM2.h"

/****************************************/
// Prototipos de función
void setup(void);
void ADC_Init(void);
uint16_t ADC_Read(void);

volatile uint8_t potenciometro = 0;

/****************************************/
// Función principal
int main(void) {
	// Configuracion inicial
	setup();
	
	while (1) {
		// Leer valor del potenciómetro (0-1023)
		// Mapear ADC a ancho de pulso (2000-4000 = 1ms-2ms @ 16MHz, prescaler 8)
		if (potenciometro == 0)
		{
			uint16_t valor_ADC2 = ADC_Read();
			uint16_t dutyCycle2 = (valor_ADC2 * 4000UL / 1023) + 1000;
			update_DutyCycle2(dutyCycle2); // Actualizar PWM
		}
		else{
			uint16_t valor_ADC1 = ADC_Read();
			uint16_t dutyCycle1 = (valor_ADC1 * 4000UL / 1023) + 1000;
			update_DutyCycle1(dutyCycle1); // Actualizar PWM
		}
		_delay_ms(20); // Delay para estabilidad
	}
}

/****************************************/
// Subrutinas sin Interrupcion
void setup(void){
	cli();
	ADC_Init();
	PWM1_Init();
	PWM2_Init();
	
	// Habilitar interrupciones del TIMER0
	TCCR0A = 0x00;  // Modo Normal
	TCCR0B = (1 << CS01) | (1 << CS00);   //Prescaler 64
	TCNT0 = 131;
	TIMSK0 = (1 << TOIE0);
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

/****************************************/
// Subrutinas de Interrupcion
ISR(TIMER0_OVF_vect){
	ADMUX = 0;
	if (potenciometro == 0)
	{
		potenciometro = 1;
		ADMUX |= (1<<REFS0)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
	}
	else{
		potenciometro = 0;
		ADMUX |= (1<<REFS0)|(1<<MUX2)|(1<<MUX1);
	}
	_delay_us(1);
}