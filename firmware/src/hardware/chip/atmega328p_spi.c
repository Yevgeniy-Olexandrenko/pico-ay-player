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

void spi_start(SPI_PRESCALE prescale, SPI_ORDER order, SPI_MODE mode)
{
    clr_bit(SPI_DDR, SPI_MISO); // MISO as input
    set_bit(SPI_DDR, SPI_MOSI); // MOSI as output
    set_bit(SPI_DDR, SPI_SCK ); // SCK  as output

    SPCR = (_BV(SPE) | order | _BV(MSTR) | mode);
    upd_bit(SPSR, SPI2X, prescale & 0b100);
    upd_bit(SPCR, SPR1,  prescale & 0b010);
    upd_bit(SPCR, SPR0,  prescale & 0b001);
}

void spi_write(uint8_t data)
{
    spi_transfer(data);
}

uint8_t spi_read() 
{
    return spi_transfer(0x00);
}

void spi_stop()
{
    clr_bit(SPCR, SPE);
}
