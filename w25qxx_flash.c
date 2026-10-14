#include "w25qxx_flash.h"

void W25Q_Init(void) {
    SPI_CS_Deselect(); // Ensure CS is high initially
}

void W25Q_WriteEnable(void) {
    SPI_CS_Select();
    SPI_TransmitReceive(W25Q_WRITE_ENABLE);
    SPI_CS_Deselect();
}

bool W25Q_IsBusy(void) {
    uint8_t status;
    SPI_CS_Select();
    SPI_TransmitReceive(W25Q_READ_STATUS_REG1);
    status = SPI_TransmitReceive(W25Q_DUMMY_BYTE);
    SPI_CS_Deselect();
    
    // Check BUSY bit (Bit 0)
    return (status & 0x01) == 0x01;
}

void W25Q_EraseSector(uint32_t addr) {
    W25Q_WriteEnable();
    
    while(W25Q_IsBusy()); // Wait if flash is busy
    
    SPI_CS_Select();
    SPI_TransmitReceive(W25Q_SECTOR_ERASE);
    SPI_TransmitReceive((addr >> 16) & 0xFF); // High byte
    SPI_TransmitReceive((addr >> 8)  & 0xFF); // Mid byte
    SPI_TransmitReceive(addr & 0xFF);         // Low byte
    SPI_CS_Deselect();
    
    while(W25Q_IsBusy()); // Wait for erase to complete
}

void W25Q_ReadData(uint32_t addr, uint8_t *buffer, uint16_t length) {
    while(W25Q_IsBusy()); 
    
    SPI_CS_Select();
    SPI_TransmitReceive(W25Q_READ_DATA);
    SPI_TransmitReceive((addr >> 16) & 0xFF);
    SPI_TransmitReceive((addr >> 8)  & 0xFF);
    SPI_TransmitReceive(addr & 0xFF);
    
    for (uint16_t i = 0; i < length; i++) {
        buffer[i] = SPI_TransmitReceive(W25Q_DUMMY_BYTE);
    }
    SPI_CS_Deselect();
}
