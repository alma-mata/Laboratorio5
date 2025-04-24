/*
 * Universidad del Valle de Guatemala
 * IE2023: Programacion de Microcontroladores
 * PWM3.c
 * Autor: Alma Lisbeth Mata Ixcayau
 * Proyecto: Laboratorio 5
 * Descripcion: Control de servomotor con PWM manual con Timer0 a 16MHz
 * Creado: 22/04/2025
*/

#ifndef PWM3_H_
#define PWM3_H_

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

void PWM3_Init(void);
void update_DutyCycle3(uint16_t dutyCycle);

#endif /* PWM3_H_ */