// -----------------------------------------------------------------------------
// ATmega328p SPI Bus
// -----------------------------------------------------------------------------

#include "atmega328p_spi.h"

void spi_init()
{
    // TODO
}

uint8_t spi_transfer(uint8_t data)
{
    SPDR = data;
    while (isb_clr(SPSR, SPIF));
    return SPDR;
}
