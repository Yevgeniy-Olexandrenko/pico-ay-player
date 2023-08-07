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

void spi_start(SPI_SPEED speed, SPI_ORDER order, SPI_MODE mode);
{
    res_bit(SPI_DDR, SPI_MISO); // MISO as input
    set_bit(SPI_DDR, SPI_MOSI); // MOSI as output
    set_bit(SPI_DDR, SPI_SCK);  // SCK  as output

    SPCR = (_BV(SPE) | order | _BV(MSTR) | mode);
    switch (speed)
    {
        case SPI_SPEED_FULL: 
            // F_CPU / 2
            set_bit(SPSR, SPI2X); res_bit(SPCR, SPR1); res_bit(SPCR, SPR0);
            break;

        case SPI_SPEED_HALF:
            // F_CPU / 4
            res_bit(SPSR, SPI2X); res_bit(SPCR, SPR1); res_bit(SPCR, SPR0);
            break;

        case SPI_SPEED_QUARTER:
            // F_CPU / 8
            set_bit(SPSR, SPI2X); res_bit(SPCR, SPR1); set_bit(SPCR, SPR0);
            break;

        case SPI_SPEED_EIGHTH:
            // F_CPU / 16
            res_bit(SPSR, SPI2X); res_bit(SPCR, SPR1); set_bit(SPCR, SPR0);
            break;
    }
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
    res_bit(SPCR, SPE);
}
