/*
* Laboratorio5.c
* Control de servomotor con PWM usando Timer1 a 16MHz
* Author: Alma Mata
*/

#ifndef PWM1_H_
#define PWM1_H_

void PWM_Init(void);
void update_DutyCycle(uint16_t dutyCycle);

#endif /* PWM1_H_ */