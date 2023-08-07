// -----------------------------------------------------------------------------
// TPA6130A2 Chip (Headphone Amplifier)                                completed
// -----------------------------------------------------------------------------

#include "tpa6130a2.h"
#include "atmega328p_i2c.h"

#define AMP_I2C_ADDR    0x60
#define AMP_VOL_LEVELS  64

typedef enum {
    AMP_REG_CONTROL   = 0x01,
    AMP_REG_VOL_MUTE  = 0x02,
    AMP_REG_VERSION   = 0x04
} AMP_REG;

#define AMP_BIT_SWS     0 // control
#define AMP_BIT_HP_EN_R 6 // control
#define AMP_BIT_HP_EN_L 7 // control
#define AMP_BIT_MUTE_R  6 // volume & mute
#define AMP_BIT_MUTE_L  7 // volume & mute

// -----------------------------------------------------------------------------

static uint8_t amp_get_register(AMP_REG reg)
{
    i2c_start_write(AMP_I2C_ADDR);
    i2c_write(reg);
    i2c_start_read(AMP_I2C_ADDR);
    return i2c_read_nack();
}

static uint8_t amp_get_register_and_stop(AMP_REG reg)
{
    uint8_t data = amp_get_register(reg);
    i2c_stop(); return data;
}

static void amp_set_register(AMP_REG reg, uint8_t data)
{
    i2c_start_write(AMP_I2C_ADDR);
    i2c_write(reg);
    i2c_write(data);
    i2c_stop();
}

// -----------------------------------------------------------------------------

bool amp_init()
{
    uint8_t data1 = 0x00;
    uint8_t data2 = ((AMP_VOL_LEVELS / 2) - 1);
    set_bit(data1, AMP_BIT_HP_EN_R);
    set_bit(data1, AMP_BIT_HP_EN_L);
    amp_set_register(AMP_REG_CONTROL, data1);
    amp_set_register(AMP_REG_VOL_MUTE, data2);
    uint8_t data4 = amp_get_register_and_stop(AMP_REG_VERSION);
    return (data4 == 0x02);
}

void amp_set_volume(uint8_t volume)
{
    if (volume >= AMP_VOL_LEVELS)
        volume = (AMP_VOL_LEVELS - 1);
    uint8_t data = amp_get_register(AMP_REG_VOL_MUTE);
    upd_bit(volume, AMP_BIT_MUTE_R, isb_set(data, AMP_BIT_MUTE_R));
    upd_bit(volume, AMP_BIT_MUTE_L, isb_set(data, AMP_BIT_MUTE_L));
    amp_set_register(AMP_REG_VOL_MUTE, volume);
}

void amp_set_mute(bool yes)
{
    uint8_t data = amp_get_register(AMP_REG_VOL_MUTE);
    upd_bit(data, AMP_BIT_MUTE_R, yes);
    upd_bit(data, AMP_BIT_MUTE_L, yes);
    amp_set_register(AMP_REG_VOL_MUTE, data);
}

void amp_set_shutdown(bool yes)
{
    uint8_t data = amp_get_register(AMP_REG_CONTROL);
    upd_bit(data, AMP_BIT_SWS, yes);
    amp_set_register(AMP_REG_CONTROL, data);
}

uint8_t amp_get_volume()
{
    uint8_t data = amp_get_register_and_stop(AMP_REG_VOL_MUTE);
    return (data & (AMP_VOL_LEVELS - 1));
}

bool amp_get_mute()
{
    uint8_t data = amp_get_register_and_stop(AMP_REG_VOL_MUTE);
    return (isb_set(data, AMP_BIT_MUTE_R) && isb_set(data, AMP_BIT_MUTE_L));
}

bool amp_get_shutdown()
{
    uint8_t data = amp_get_register_and_stop(AMP_REG_CONTROL);
    return isb_set(data, AMP_BIT_SWS);
}
