# Target microcontroller
MCU = atmega2560
# Clock frequency (16 MHz for Arduino Mega)
F_CPU = 16000000UL
# Output filename (without extension)
TARGET ?= main

# AVR toolchain
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Iinclude

# AVRDUDE settings (for Arduino Mega on /dev/ttyUSB0)
PROGRAMMER = wiring
PORT ?= /dev/ttyUSB0
BAUD = 115200

# Source files
SRC = \
	main/$(TARGET).c\
	drivers/uart/uart.c\
	drivers/gpio/gpio.c\
	drivers/dht11/dht11.c\
	drivers/hd44780/hd44780.c

# Directories
BUILD_DIR = build

# Default target: compile and flash
all: compile flash

# Compile .c to .elf
compile: $(SRC)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET).elf $(SRC)
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex

# Flash .hex to MCU
flash:
	$(AVRDUDE) -v -V -p$(MCU) -c$(PROGRAMMER) -P$(PORT) -b$(BAUD) -D -Uflash:w:$(BUILD_DIR)/$(TARGET).hex:i

# Clean build artifacts
clean:
	rm -f $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex

.PHONY: all compile flash clean
