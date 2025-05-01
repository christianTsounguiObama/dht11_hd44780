#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "gpio.h"
#include "hd44780.h"

int main(void){
	lcd_initialization();
	lcd_ecrire_mot("Hallo Christian!");
	while(1){
	}
}
