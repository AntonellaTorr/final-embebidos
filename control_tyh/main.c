
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include "twi.h"
#include "sht31.h"
#include "gpio.h"

#define  HIGH_TEMP 37.8
#define  LOW_TEMP 38.9
extern float sht31_temperature;
extern float sht31_humidity;

//Se conecta scl a A5 y sda a A4

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
            //definir comportoamiento del heater
        } else {
            //  No se pudo leer el sensor, manejar error
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
