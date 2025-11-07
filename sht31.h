#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
                 
#define SHT31_READSTATUS 0xF32D 
#define SHT31_DEFAULT_ADDR 0x44 /**< SHT31 Default Address */
#define SHT31_SOFTRESET 0x30A2
#define SHT31_CLEARSTATUS 0x3041 

//variable tipo uint16_t para el comando de lectura de estado, 2 bytes y un null
uint16_t sht31_read_status();   
void sht31_leer(uint8_t adress, uint8_t *data);
void sht31_reset(void);
int sht31_begin();
void leer(uint8_t adress, uint8_t *data);
void sht31_clear_status(void);