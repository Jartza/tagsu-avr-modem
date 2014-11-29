/* Name: simple_spi.c
 *
 * Very simple bitbanging SPI implementation
 *
 * Author: Jari Tulilahti
 * Copyright: 2014 Rakettitiede Oy
 * License: GPLv3, see COPYING -file for more info
 */

#include "simple_spi.h"

/*
 * BitBang one byte to SPI.
 */
void spi_send(uint8_t b) {
    /* Chip select low to enable bus */
    SPI_LOW(SPI_PIN_CSB);

    /* Send 8 bits */
    for (uint8_t i = 0; i < 8; i++)  {                      
        /* Pulse clock high */
        SPI_LOW(SPI_PIN_SCLK);

        /* Set MOSI bit */
        if (b & 0x80) {
            SPI_HIGH(SPI_PIN_MOSI); /* Bit 1 */
        } else {
            SPI_LOW(SPI_PIN_MOSI); /* Bit 0 */
        }

        /* Pulse clock low */
        SPI_HIGH(SPI_PIN_SCLK);

        /* Shift bits */
        b <<= 1;
    }

    /* Reset data line to low state */
    SPI_LOW(SPI_PIN_MOSI);
    SPI_LOW(SPI_PIN_SCLK);

    /* Chip select high */
    SPI_HIGH(SPI_PIN_CSB);
}

void spi_init() {
    /* Set SPI pins as output */
    SPI_DDR |= (1 << SPI_PIN_SCLK) | (1 << SPI_PIN_MOSI) | (1 << SPI_PIN_CSB);
    SPI_LOW(SPI_PIN_SCLK);
    SPI_LOW(SPI_PIN_MOSI);
    SPI_HIGH(SPI_PIN_CSB);
}
