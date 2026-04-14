
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include "serial.h"
#include "twi.h"
#include "sht31.h"

// Declarar las variables globales del sensor
extern float sht31_temperature;
extern float sht31_humidity;

int main(void) {
    int loopCnt = 0;
    int enableHeater = 0;
    
    serial_init();
    twi_init();
    _delay_ms(5000);
    
    serial_put_string("=== SHT31 Iniciando ===\r\n");
    
    // Verificar si el sensor responde
    if (!sht31_begin()) {
        serial_put_string("ERROR: Sensor no encontrado!\r\n");
        while(1) {
            // Loop infinito de error
            serial_put_string(".");
            _delay_ms(1000);
        }
    }
    
    serial_put_string("Sensor OK. Iniciando lecturas...\r\n\r\n");
    
    while (1) {
        // Método 1: Usando sht31_read_both (RECOMENDADO)
        float t, h;
        if (sht31_read_both(&t, &h)) {
            serial_put_string("Temp C = ");
            serial_print_float(t);
            serial_put_string("\r\n");
            
            serial_put_string("Hum % = ");
            serial_print_float(h);
            serial_put_string("\r\n\r\n");
        } else {
            serial_put_string("Failed to read sensor\r\n");
        }
        
        _delay_ms(1000);  // Espera 1 segundo entre lecturas
        
        // Cada 30 iteraciones (~30 segundos) alternar heater
        if (loopCnt >= 30) {
            enableHeater = !enableHeater;
            sht31_heater(enableHeater);
            
            serial_put_string("Heater State: ");
            if (sht31_is_heater_enabled())
                serial_put_string("ENABLED\r\n");
            else
                serial_put_string("DISABLED\r\n");
            
            loopCnt = 0;
        }
        
        loopCnt++;
    }
    
    // Nunca debería llegar aquí
    return 0;
}
/*
void main () {
    serial_init();
    twi_init();_delay_ms(5000);
    while (1) {
    float t = sht31_read_temperature();
    float h = sht31_read_humidity();

    if (!isnan(t)) {
        serial_put_string("Temp C = ");
        serial_print_float(t);
        serial_put_string("\r\n");
        
    } else {
         serial_put_string("Failed to read temperature\n");
    }

    if (!isnan(h)) {
        serial_put_string("Hum % = ");
        serial_print_float(h);
        serial_put_string("\r\n");
    } else {
        serial_put_string("Failed to read humidity\n");
    }

    _delay_ms(1000);

    // Cada 30 iteraciones (~30 segundos)
    if (loopCnt >= 30) {
        enableHeater = !enableHeater;
        sht31_heater(enableHeater);

        printf("Heater Enabled State: ");
        if (sht31_is_heater_enabled())
            printf("ENABLED\n");
        else
            printf("DISABLED\n");

        loopCnt = 0;
    }

    loopCnt++;

    }
   
  
    
}
*/

