#include "gpio.h"
//#include "uart.h"

void gpio_definir_direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction) {
    if (direction == GPIO_OUTPUT){
		*ddr |= (1 << pin); // Definir broche comme sortie
	}else{
        *ddr &= ~(1 << pin); // Definir broche comme entree
	}
}

void gpio_ecrire(volatile uint8_t* port, uint8_t pin, uint8_t value) {
    if (value){ // Si signal actif value == 1
        *port |= (1 << pin);
	}else{ // Si signal eteint value == 0
        *port &= ~(1 << pin);
	}
}

uint8_t gpio_lire(volatile uint8_t pinr, uint8_t pin) {
    return (pinr & (1 << pin)); // Lire 1
}
