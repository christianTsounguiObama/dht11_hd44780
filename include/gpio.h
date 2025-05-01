#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include <stdint.h>

#define GPIO_OUTPUT 1
#define GPIO_INPUT 0

void gpio_definir_direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction);
void gpio_ecrire(volatile uint8_t* port, uint8_t pin, uint8_t value);
uint8_t gpio_lire(volatile uint8_t pinr, uint8_t pin);

#endif
