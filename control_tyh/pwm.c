
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "pin_config.h"

//extern volatile unsigned long ticks = 0;


typedef struct
{
    uint8_t tccr0a;   // 0x44
    uint8_t tccr0b;   // 0x45
    uint8_t tcnt0;    // 0x46  contador (8 bits)
    uint8_t ocr0a;    // 0x47 compare A
    uint8_t ocr0b;    // 0x48 compare B
} volatile timer0_t;

volatile unsigned char *DDRD  = (unsigned char *) 0x2A;


volatile timer0_t *timer0 = (timer0_t*) 0x44;

//duty cycle= potencia?

void timer_init(void)
{ 
    //pongo WGM01 WGM00 EN 1
    timer0->tccr0a |= (1 << 1) | (1 << 0) ;
    //Pwm no invertido COM0A1 en 1 
    timer0->tccr0a |= (1 << 7) ;
    timer0->ocr0a = 127; // 50% duty cycle
    DDRD |= (1 << 6); // pin 6 como salida 0C0A
    timer0->tccr0b  |= (1 << 1) |  (1 << 0) ; // prescalar 64

} 
