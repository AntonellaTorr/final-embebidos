#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include <stddef.h> /* para NULL */
#include <util/delay.h>
#include "sht31.h"
#include "twi.h"

uint8_t *response_data;
void leer(uint8_t adress, uint8_t *data) {
    response_data = data;
}

uint16_t sht31_read_status() {
    //leemos 2 bytes, 3 checksum
    uint8_t cmd[2];
    cmd[0] = (SHT31_READSTATUS >> 8) & 0xFF;
    cmd[1] = SHT31_READSTATUS & 0xFF;
    twi_write(SHT31_DEFAULT_ADDR, cmd, 2, NULL);
    twi_read(SHT31_DEFAULT_ADDR, 3, leer);
    _delay_ms(10);
    uint16_t stat = response_data[0];
    stat <<= 8;
    stat |= response_data[1];
    return stat;
}

int sht31_begin() {
    sht31_reset();
   return sht31_read_status() != 0xFFFF;   
}

void sht31_reset(void) {
    uint8_t cmd[2];
    cmd[0] = (SHT31_SOFTRESET >> 8) & 0xFF;
    cmd[1] = SHT31_SOFTRESET & 0xFF;
    twi_write(SHT31_DEFAULT_ADDR, cmd, 2, NULL);
    _delay_ms(10);

}
void sht31_clear_status(void) {
    uint8_t cmd[2];
    cmd[0] = (SHT31_CLEARSTATUS >> 8) & 0xFF;
    cmd[1] = SHT31_CLEARSTATUS & 0xFF;
    twi_write(SHT31_DEFAULT_ADDR, cmd, 2, NULL);
    _delay_ms(10);
}








