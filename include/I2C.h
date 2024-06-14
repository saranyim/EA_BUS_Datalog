
#ifndef __I2C_H__
#define __I2C_H__

#include "gd32f30x.h"

#define I2C_MEMADD_SIZE_8BIT 8
#define I2C_MEMADD_SIZE_16BIT 16


ErrStatus I2C_buff_write(uint32_t i2c_periph,uint8_t dev_addr, uint16_t write_address,uint16_t addr_len, uint8_t *p_buffer, uint8_t number_of_byte);
ErrStatus I2C_Byte_write(uint32_t i2c_periph,uint8_t dev_addr, uint16_t write_address,uint16_t addr_len, uint8_t p_buffer);
ErrStatus I2C_buffer_read( uint32_t i2c_periph,uint8_t dev_addr, uint16_t read_address,uint16_t addr_len, uint8_t *p_buffer, uint8_t number_of_byte);
void I2C_wait_standby_state(uint32_t i2c_periph,uint8_t dev_addr);
#endif  /* AT24CXX_H */
