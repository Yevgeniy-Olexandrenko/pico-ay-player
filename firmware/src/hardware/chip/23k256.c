// -----------------------------------------------------------------------------
// 23K256 Chip (32Kb SRAM)                                             completed
// -----------------------------------------------------------------------------

#include "23k256.h"
#include "atmega328p_spi.h"

typedef enum {
    SRAM_BYTE  = 0x00, // Byte Operation
    SRAM_PAGE  = 0x80, // Page Operation
    SRAM_SEQ   = 0x40  // Sequential Operation
} SRAM_MODE;

typedef enum {
    SRAM_READ  = 0x03, // Read data from memory array beginning at selected address
    SRAM_WRITE = 0x02, // Write data to memory array beginning at selected address
    SRAM_RDSR  = 0x05, // Read STATUS register
    SRAM_WRSR  = 0x01  // Write STATUS register
} SRAM_INST;

// -----------------------------------------------------------------------------

static void sram_start()
{
    spi_start(SPI_PRESCALE2, SPI_MSB_FIRST, SPI_MODE0);
    clr_bit(SRAM_PORT, SRAM_CS); // chip select
}

static void sram_stop()
{
    set_bit(SRAM_PORT, SRAM_CS); // chip deselect
    spi_stop();
}

static void sram_inst_addr(SRAM_INST inst, uint16_t addr)
{
    sram_start();
    spi_write(inst);
    spi_write(addr >> 8);
    spi_write(addr);
}

// -----------------------------------------------------------------------------

void sram_init()
{
    set_bit(SRAM_DDR, SRAM_CS); // chip select as output
    sram_start();
    spi_write(SRAM_WRSR);
    spi_write(SRAM_SEQ);        // default mode
    sram_stop();
}

void sram_fill_block(uint16_t addr, uint8_t data, uint16_t size)
{
    sram_inst_addr(SRAM_WRITE, addr);
    for (; size > 0; --size) spi_write(data);
    sram_stop();
}

void sram_write_block(uint16_t addr, uint8_t* data, uint16_t size)
{
    sram_inst_addr(SRAM_WRITE, addr);
    for (; size > 0; ++data, --size) spi_write(*data);
    sram_stop();
}

void sram_read_block(uint16_t addr, uint8_t* data, uint16_t size)
{
    sram_inst_addr(SRAM_READ, addr);
    for (; size > 0; ++data, --size) *data = spi_read();
    sram_stop();
}

void sram_write(uint16_t addr, uint8_t data)
{
    sram_inst_addr(SRAM_WRITE, addr);
    spi_write(data);
    sram_stop();
}

uint8_t sram_read(uint16_t addr)
{
    sram_inst_addr(SRAM_READ, addr);
    uint8_t data = spi_read();
    sram_stop();
    return data;
}

void sram_write16(uint16_t addr, uint16_t data)
{
    sram_write_block(addr, &data, 2);
}

uint16_t sram_read16(uint16_t addr)
{
    uint16_t data;
    sram_read_block(addr, &data, 2);
    return data;
}

void sram_write32(uint16_t addr, uint32_t data)
{
    sram_write_block(addr, &data, 4);
}

uint32_t sram_read32(uint16_t addr)
{
    uint32_t data;
    sram_read_block(addr, &data, 4);
    return data;
}
