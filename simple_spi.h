/* Name: simple_spi.h
 *
 * Author: Jari Tulilahti
 * Copyright: 2014 Rakettitiede Oy
 * License: LGPLv3, see COPYING, and COPYING.LESSER -files for more info
 */

#pragma once

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define SPI_PORT	PORTB
#define SPI_DDR		DDRB
#define SPI_PIN_MOSI	PB0
#define SPI_PIN_CSB	PB1
#define SPI_PIN_SCLK	PB2

#define SPI_HIGH(x)	SPI_PORT |= (1 << x)
#define SPI_LOW(x)	SPI_PORT &= ~(1 << x)

void spi_send(uint8_t b);
void spi_init();
