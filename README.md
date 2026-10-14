# C-SPI-Flash-Driver
Hardware Abstraction Layer for W25Qxx SPI Flash
# SPI Flash Memory Driver (W25Qxx)

A lightweight, hardware-independent C driver for the popular Winbond W25Qxx series NOR Flash memory (e.g., W25Q64, W25Q128) using the SPI protocol.

## Architecture
This driver is designed with portability in mind. It utilizes a Hardware Abstraction Layer (HAL) approach. The core logic handles the specific instruction sets, dummy bytes, and status register polling of the W25Qxx chip, while leaving the physical SPI hardware implementation (SPI_TransmitReceive, SPI_CS_Select) to be defined by the user's specific microcontroller platform (STM32, ESP32, AVR).

## Features
- **Status Polling:** Implements blocking checks to ensure the BUSY flag is cleared before executing new memory operations.
- **Bitwise Address Shifting:** Demonstrates proper handling of 24-bit addressing via standard 8-bit SPI transfers.
- **Memory Safety:** Uses standard integer types (stdint.h) to guarantee cross-architecture compatibility.
