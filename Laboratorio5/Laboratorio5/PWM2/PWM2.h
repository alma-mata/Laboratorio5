/*
 * Universidad del Valle de Guatemala
 * IE2023: Programacion de Microcontroladores
 * PWM2.h
 * Autor: Alma Lisbeth Mata Ixcayau
 * Proyecto: Laboratorio 5
 * Descripcion: Control de servomotor con PWM usando Timer1 a 16MHz
 * Creado: 11/04/2025
*/

#ifndef PWM2_H_
#define PWM2_H_

#include <avr/io.h>

void PWM2_Init(void);
void update_DutyCycle2(uint16_t dutyCycle);

#endif /* PWM2_H_ */