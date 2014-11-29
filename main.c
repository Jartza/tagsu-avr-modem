/* Name: main.c
 *
 * Modem demo main code. All this does is run in loop and forward
 * bytes coming to ring buffer to SPI.
 *
 * Author: Jari Tulilahti
 * Copyright: 2014 Rakettitiede Oy
 * License: GPLv3, see COPYING -file for more info
 */

#include "simple_spi.h"
#include "modem.h"

/*
 * Set up SPI and Modem
 */
static void setup()  {
	modem_init();
	spi_init();
}

/*
 * Entry point of the program 
 */
int main(void)
{
	/* Call setup */
	setup();

	/* Loop forever */
	for (;;) {
		if (modem_buffer_available()) {
			spi_send(modem_buffer_get());
		}
	}

	/* We never reach this */
	return 0;
}
