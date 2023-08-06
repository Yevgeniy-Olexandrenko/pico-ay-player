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

void    spi_init();
void    spi_write(uint8_t data);
uint8_t spi_read();

#endif // _SPI_H_
