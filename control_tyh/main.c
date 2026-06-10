
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include "twi.h"
#include "sht31.h"
#include "gpio.h"

#define  HIGH_TEMP 37.8
#define  LOW_TEMP 37.5
extern float sht31_temperature;
extern float sht31_humidity;

int main(void){
    int loopCnt = 0;
    int enableHeater = 0;
    
    gpio_output(13);

    twi_init();
    _delay_ms(5000);
    
    // Verificar si el sensor responde
    if (!sht31_begin()) {
        while(1) {
            // Loop infinito de error
            _delay_ms(1000);
        }
    }
    //sensor ok
    
    while (1) {
     float t, h;
        if (sht31_read_both(&t, &h)) {
            if (t< LOW_TEMP){
                while (1){
                    gpio_pin(13, ON);
                    _delay_ms(1000);
                    gpio_pin(13, OFF);  _delay_ms(1000);
                }
            } else {
                gpio_pin(13, ON);
            }

            //MISMO COMPORTAMIENTO CON HUMEDAD
        } else {
            // Failed to read sensor
        }
        
        _delay_ms(1000);  // Espera 1 segundo entre lecturas
        
        // Cada 30 iteraciones (~30 segundos) alternar heater
        if (loopCnt >= 30) {
            enableHeater = !enableHeater;
            sht31_heater(enableHeater);            
            loopCnt = 0;
        }
        
        loopCnt++;
    }
    

}
