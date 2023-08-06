// -----------------------------------------------------------------------------
// ATmega328p SPI Bus
// -----------------------------------------------------------------------------

#include "atmega328p_spi.h"

static uint8_t spi_transfer(uint8_t data)
{
    SPDR = data;
    while (isb_clr(SPSR, SPIF));
    return SPDR;

}

// -----------------------------------------------------------------------------

void spi_init()
{
    // TODO
}

void spi_write(uint8_t data)
{
    spi_transfer(data);
}

uint8_t spi_read()
{
    return spi_transfer(0x00);
}
