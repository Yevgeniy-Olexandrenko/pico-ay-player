// -----------------------------------------------------------------------------
// TPA6130A2 Chip
// -----------------------------------------------------------------------------

#include "tpa6130a2.h"
#include "../mcu/i2c.h"

#define TPA6130A2_I2C_ADDR    0x60
#define TPA6130A2_VOL_LEVELS  64

typedef enum {
    TPA6130A2_CONTROL         = 0x01,
    TPA6130A2_VOLUME_MUTE     = 0x02,
    TPA6130A2_VERSION         = 0x04
} TPA6130A2_REG;

#define TPA6130A2_BIT_SWS     0 // control
#define TPA6130A2_BIT_HP_EN_R 6 // control
#define TPA6130A2_BIT_HP_EN_L 7 // control
#define TPA6130A2_BIT_MUTE_R  6 // volume & mute
#define TPA6130A2_BIT_MUTE_L  7 // volume & mute

// -----------------------------------------------------------------------------

static uint8_t tpa6130a2_get_register(TPA6130A2_REG reg)
{
    i2c_start_write(TPA6130A2_I2C_ADDR);
    i2c_write(reg);
    i2c_start_read(TPA6130A2_I2C_ADDR);
    return i2c_read_ack();
}

static void tpa6130a2_set_register(TPA6130A2_REG reg, uint8_t data)
{
    i2c_start_write(TPA6130A2_I2C_ADDR);
    i2c_write(reg);
    i2c_write(data);
    i2c_stop();
}

// -----------------------------------------------------------------------------

bool tpa6130a2_init()
{
    uint8_t data1 = 0x00;
    uint8_t data2 = ((TPA6130A2_VOL_LEVELS / 2) - 1);
    set_bit(data1, TPA6130A2_BIT_HP_EN_R);
    set_bit(data1, TPA6130A2_BIT_HP_EN_L);
    tpa6130a2_set_register(TPA6130A2_CONTROL, data1);
    tpa6130a2_set_register(TPA6130A2_VOLUME_MUTE, data2);
    uint8_t data4 = tpa6130a2_get_register(TPA6130A2_VERSION);
    i2c_stop();
    return (data4 == 0x02);
}

void tpa6130a2_set_volume(uint8_t volume)
{
    if (volume >= TPA6130A2_VOL_LEVELS)
        volume = (TPA6130A2_VOL_LEVELS - 1);
    uint8_t data = tpa6130a2_get_register(TPA6130A2_VOLUME_MUTE);
    upd_bit(volume, TPA6130A2_BIT_MUTE_R, isb_set(data, TPA6130A2_BIT_MUTE_R));
    upd_bit(volume, TPA6130A2_BIT_MUTE_L, isb_set(data, TPA6130A2_BIT_MUTE_L));
    tpa6130a2_set_register(TPA6130A2_VOLUME_MUTE, volume);
}

void tpa6130a2_set_mute(bool yes)
{
    uint8_t data = tpa6130a2_get_register(TPA6130A2_VOLUME_MUTE);
    upd_bit(data, TPA6130A2_BIT_MUTE_R, yes);
    upd_bit(data, TPA6130A2_BIT_MUTE_L, yes);
    tpa6130a2_set_register(TPA6130A2_VOLUME_MUTE, data);
}

void tpa6130a2_set_shutdown(bool yes)
{
    uint8_t data = tpa6130a2_get_register(TPA6130A2_CONTROL);
    upd_bit(data, TPA6130A2_BIT_SWS, yes);
    tpa6130a2_set_register(TPA6130A2_CONTROL, data);
}

uint8_t tpa6130a2_get_volume()
{
    uint8_t data = tpa6130a2_get_register(TPA6130A2_VOLUME_MUTE);
    i2c_stop();
    return (data & (TPA6130A2_VOL_LEVELS - 1));
}

bool tpa6130a2_get_mute()
{
    uint8_t data = tpa6130a2_get_register(TPA6130A2_VOLUME_MUTE);
    i2c_stop();
    return (isb_set(data, TPA6130A2_BIT_MUTE_R) && isb_set(data, TPA6130A2_BIT_MUTE_L));
}

bool tpa6130a2_get_shutdown()
{
    uint8_t data = tpa6130a2_get_register(TPA6130A2_CONTROL);
    i2c_stop();
    return isb_set(data, TPA6130A2_BIT_SWS);
}
