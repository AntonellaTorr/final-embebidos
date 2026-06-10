
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include "gpio.h"
#include "ultrasound.h"

int main(void)
{
  
    init_ultrasound(9, 10); // trig en D9, echo en D10

    while (1) {
        int distance = ultrasound_get_distance(9, 10);
        if (distance >= 0) {
                if (distance < 20) {
                    // Si la distancia es menor a 20 cm, enciende el LED en D13
                    gpio_output(13);
                    gpio_pin(13, ON);
                } else {
                    // Si la distancia es mayor o igual a 20 cm, apaga el LED
                    gpio_pin(13, OFF);
                }
         
        } else {
        }
        _delay_ms(100);
    }

}
   
