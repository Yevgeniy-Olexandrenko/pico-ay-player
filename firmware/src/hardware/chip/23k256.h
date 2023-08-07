// -----------------------------------------------------------------------------
// 23K256 Chip (32 Kb SRAM)
// -----------------------------------------------------------------------------

#ifndef _23K256_H_
#define _23K256_H_

#include "../../arduino.h"

#define SRAM_DDR  DDRB
#define SRAM_PORT PORTB
#define SRAM_CS   PB1

void     sram_init();
void     sram_fill_block (uint16_t addr, uint8_t  data, uint16_t size);
void     sram_write_block(uint16_t addr, uint8_t* data, uint16_t size);
void     sram_read_block (uint16_t addr, uint8_t* data, uint16_t size);
void     sram_write  (uint16_t addr, uint8_t data);
uint8_t  sram_read   (uint16_t addr);
void     sram_write16(uint16_t addr, uint16_t data);
uint16_t sram_read16 (uint16_t addr);
void     sram_write32(uint16_t addr, uint32_t data);
uint32_t sram_read32 (uint16_t addr);

#endif // _23K256_H_
