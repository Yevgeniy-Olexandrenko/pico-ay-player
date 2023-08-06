// -----------------------------------------------------------------------------
// ATmega328p I2C Bus
// -----------------------------------------------------------------------------

#ifndef _I2C_H_
#define _I2C_H_

#include "../../arduino.h"

#define I2C_DDR DDRC
#define I2C_PIN PINC
#define I2C_SDA PC4
#define I2C_SCL PC5

bool    i2c_start_write(uint8_t addr);
bool    i2c_start_read(uint8_t addr);
uint8_t i2c_read_ack();
uint8_t i2c_read_nack();
uint8_t i2c_read(bool ack);
bool    i2c_write(uint8_t data);
void    i2c_stop();

#endif // _I2C_H_
