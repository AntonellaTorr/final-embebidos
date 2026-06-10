

#include <stdint.h>
#include "gpio.h"

void energy(){
    //utilizo el d8 como pin de entrada con pull-up interno, y el d13 como salida para encender el led integrado
    gpio_input(8);
    gpio_pin(8, ON);    // activa pull up en D8

    gpio_output(13);

    while (1) {
        if (gpio_pin(8, GET) == 0)   // si esta presionado
            gpio_pin(13, ON);
        else
            gpio_pin(13, OFF);
    }

    return 0;
}
