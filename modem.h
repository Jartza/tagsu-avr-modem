/* Name: modem.h
 * Author: Jari Tulilahti
 * Copyright: 2014 Rakettitiede Oy
 * License: LGPLv3, see COPYING, and COPYING.LESSER -files for more info
 */

#pragma once

#include <avr/interrupt.h>
#include <stdlib.h>

/* Modem ring buffer size must be power of 2 */
#define MODEM_BUFFER_SIZE	4

/* Modem defines */
#define MODEM_SYNC_LEN		42
#define MODEM_TIMER		TCNT1
#define MODEM_PIN 		PCINT3
#define MODEM_DDR		DDRB

/* Public funtions */
uint8_t modem_buffer_available();
uint8_t modem_buffer_get();
void modem_init();
