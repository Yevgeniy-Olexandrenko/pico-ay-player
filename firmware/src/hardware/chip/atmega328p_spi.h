// -----------------------------------------------------------------------------
// ATmega328p SPI Bus
// -----------------------------------------------------------------------------

#ifndef _SPI_H_
#define _SPI_H_

#include "../../arduino.h"

#define SPI_DDR  DDRB
#define SPI_SCK  PB5
#define SPI_MISO PB4
#define SPI_MOSI PB3

typedef enum {
    SPI_SPEED_FULL,
    SPI_SPEED_HALF,
    SPI_SPEED_QUARTER,
    SPI_SPEED_EIGHTH
} SPI_SPEED;

typedef enum {
    SPI_MSB_FIRST = 0,
    SPI_LSB_FIRST = _BV(DORD)
} SPI_ORDER;

typedef enum {
    SPI_MODE0 = 0,
    SPI_MODE1 = _BV(CPHA),
    SPI_MODE2 = _BV(CPOL),
    SPI_MODE3 = _BV(CPHA) | _BV(CPOL)
} SPI_MODE;

void    spi_start(SPI_SPEED speed, SPI_ORDER order, SPI_MODE mode);
void    spi_write(uint8_t data);
uint8_t spi_read();
void    spi_stop();

#endif // _SPI_H_
