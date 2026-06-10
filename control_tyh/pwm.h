#ifndef TIMER0_PWM_H
#define TIMER0_PWM_H

#include <avr/io.h>

void timer0_pwm_init(void);
void timer0_pwm_set_duty(uint8_t duty);

#endif