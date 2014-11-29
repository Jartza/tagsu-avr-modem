# Name: Makefile
# Author: Jari Tulilahti
# Copyright: (C) 2014 Rakettitiede Oy

# Object files to be created from source
OBJECTS    = main.o simple_spi.o modem.o

# AVR device name
DEVICE     = attiny85

# Clock speed
CLOCK      = 8000000

# Programming device used
PROGRAMMER = -c usbasp

# 8MHz, self programming enabled, reset pin as reset, save eeprom
FUSES = -B12 -U lfuse:w:0xe2:m -U hfuse:w:0xd7:m -U efuse:w:0xfe:m

# AVRDUDE command
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)

# Compile command
COMPILE = avr-gcc -Wall -Os -std=gnu99 -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all: main.hex

.c.o:
	$(COMPILE) -c $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuses:
	$(AVRDUDE) $(FUSES)

reset:
	$(AVRDUDE)

install: fuses flash

clean:
	rm -f main.hex main.elf $(OBJECTS)

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
