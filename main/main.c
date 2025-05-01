#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>

#include "uart.h"
#include "dht11.h"
#include "gpio.h"
#include "hd44780.h"

int main(void){
	uart_init(); // 103 pour baud 9600 a frequence 16MHz
	uint8_t humidite, temperature;
	lcd_initialization();
	char temp[4];
	char hum[4];

	while(1){ // Boucle infinie
		uint8_t status = dht_lecture(&humidite, &temperature); // Lecture du capteur
		if(status == 0){
			uart_envoi_mot("Temperature = ");
			uart_envoi_nombre(temperature);
			uart_envoi_mot("C, Humidite = ");
			uart_envoi_nombre(humidite);
			// Ecran LCD

			lcd_envoi_commande(0x01); // Nettoyer l'ecran
			_delay_ms(2);
			lcd_ecrire_mot("Temperature = ");
			itoa(temperature, temp, 10);
			lcd_ecrire_mot(temp);
			lcd_envoi_commande(0xC0); // Aller a la seconde ligne
			lcd_ecrire_mot("Humidite = ");
			itoa(humidite, hum, 10);
			lcd_ecrire_mot(hum);
		}else{
			uart_envoi_mot("DHT11 error: ");
			uart_envoi_nombre(status);
		}
		uart_envoi_mot("\r\n");
		_delay_ms(2000); // Attendre 2 secondes pour la prochaine lecture
	}
}

