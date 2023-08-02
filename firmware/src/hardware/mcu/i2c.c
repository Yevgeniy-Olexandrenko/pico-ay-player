// -----------------------------------------------------------------------------
// I2C Bus
// -----------------------------------------------------------------------------

#include "i2c.h"

#define i2c_sda_release()  clr_bit(I2C_DDR, I2C_SDA)
#define i2c_sda_pulldown() set_bit(I2C_DDR, I2C_SDA)
#define i2c_sda_read()     isb_set(I2C_PIN, I2C_SDA)
#define i2c_scl_release()  clr_bit(I2C_DDR, I2C_SCL)
#define i2c_scl_pulldown() set_bit(I2C_DDR, I2C_SCL)
#define i2c_scl_read()     isb_set(I2C_PIN, I2C_SCL)
#define i2c_delay()        __asm__ __volatile__ ("nop")

// -----------------------------------------------------------------------------

static void i2c_scl_release_wait()
{
    i2c_scl_release();
    while (!i2c_scl_read());
}

static uint8_t i2c_read_write(uint8_t data)
{
    for (uint8_t sda, i = 8; i > 0; --i)
    {
        if (data & 0x80)
            i2c_sda_release();
        else
            i2c_sda_pulldown();
        i2c_scl_release_wait();

        sda = i2c_sda_read();
        i2c_scl_pulldown();

        data <<= 1;
        if (sda) data |= 0x01;
    }
    i2c_sda_release();
    return data;
}

static void i2c_start()
{
    i2c_scl_release_wait();
    i2c_sda_pulldown();
    i2c_delay();
    i2c_scl_pulldown();
}

// -----------------------------------------------------------------------------

bool i2c_start_write(uint8_t addr)
{
    i2c_start();
    return i2c_write(addr << 1);
}

bool i2c_start_read(uint8_t addr)
{
    i2c_start();
    return i2c_write(addr << 1 | 1);
}

uint8_t i2c_read_ack()
{
    return i2c_read(true);
}

uint8_t i2c_read_nack()
{
    return i2c_read(false);
}

uint8_t i2c_read(bool ack)
{
    uint8_t data = i2c_read_write(0xFF);
    if (ack) i2c_sda_pulldown();
    i2c_scl_release_wait();

    i2c_delay();
    i2c_scl_pulldown();
    return data;
}

bool i2c_write(uint8_t data)
{
    i2c_read_write(data);
    i2c_scl_release_wait();

    bool ack = !i2c_sda_read();
    i2c_scl_pulldown();
    return ack;
}

void i2c_stop()
{
    i2c_sda_pulldown();
    i2c_scl_release_wait();
    i2c_delay();
    i2c_sda_release();
}
