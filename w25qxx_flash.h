#ifndef W25QXX_FLASH_H
#define W25QXX_FLASH_H

#include <stdint.h>
#include <stdbool.h>

// W25Qxx Instruction Set
#define W25Q_WRITE_ENABLE       0x06
#define W25Q_READ_DATA          0x03
#define W25Q_SECTOR_ERASE       0x20
#define W25Q_READ_STATUS_REG1   0x05

#define W25Q_DUMMY_BYTE         0xFF

// Function Prototypes (Hardware Abstraction Layer)
// These functions must be implemented by the low-level MCU driver (e.g., STM32 HAL)
extern void SPI_CS_Select(void);
extern void SPI_CS_Deselect(void);
extern uint8_t SPI_TransmitReceive(uint8_t data);

// Flash Operations
void W25Q_Init(void);
void W25Q_WriteEnable(void);
bool W25Q_IsBusy(void);
void W25Q_EraseSector(uint32_t sector_addr);
void W25Q_ReadData(uint32_t addr, uint8_t *buffer, uint16_t length);

#endif /* W25QXX_FLASH_H */
