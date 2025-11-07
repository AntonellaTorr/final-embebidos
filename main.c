#include <stdint.h>
#include <util/delay.h>

void main () {
    serial_init();
    twi_init();_delay_ms(5000);; 
    while (1) {
    
        uint16_t estado = 0;
        estado = sht31_read_status();
        //mostrar por serial
        serial_put_char('\n');
        serial_put_char('\r');
        serial_put_string("byte alto : ");        
        serial_put_number((estado >> 8) & 0xFF); //byte alto
        serial_put_string("byte bajo : ");        
        serial_put_number(estado & 0xFF);      // byte bajo
        serial_put_char('-');   
        esperar();
        _delay_ms(5000);
        sht31_clear_status();

        esperar();
    }
   
  
    
}
