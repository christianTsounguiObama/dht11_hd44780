#include <util/delay.h>
#include "dht11.h"
#include "gpio.h"

#define DHT_DDR DDRA
#define DHT_PORT PORTA
#define DHT_PIN PINA
#define DHT_INPUTPIN PA0

// Lecture d'un bit du DHT11
uint8_t dht_reception_bit(void){
	while(!gpio_lire(DHT_PIN, DHT_INPUTPIN)); // Attendre arrivee du signal
	_delay_us(30); //Attendre 30 microsecondes (us) // Si signal present apres 30us, lire 1 sinon lire 0
	uint8_t bit = gpio_lire(DHT_PIN, DHT_INPUTPIN) ? 1 : 0; // Attendre que signal s'arrete
	while(gpio_lire(DHT_PIN, DHT_INPUTPIN));
	return bit;
}

// Lecture d'un octet
uint8_t dht_reception_octet(void){
	uint8_t octet = 0;
	for(uint8_t i = 0; i < 8; i++){
		octet <<= 1; // Deplacer dernier bit vers la gauche
		octet |= dht_reception_bit(); // Remplacer dernier par valeur lue
	}
	return octet;
}

// Lecture de temperature et humidite
uint8_t dht_lecture(uint8_t* hum, uint8_t* temp){
	uint8_t data[5] = {0};

	// Etape 1 -- Envoyer requete au DHT11
	gpio_definir_direction(&DHT_DDR, DHT_INPUTPIN, GPIO_OUTPUT); // Definir la broche 22 en sortie
	gpio_ecrire(&DHT_PORT, DHT_INPUTPIN, 0); // Arreter le signal
	_delay_ms(20); // Attendre au mois 18 millisecondes (ms)
	gpio_ecrire(&DHT_PORT, DHT_INPUTPIN, 1); // Activer le signal
	_delay_us(30); // Attendre entre 20 et 40 microsecondes (us)

	// Etape 2 -- Confirmer la requete
	gpio_definir_direction(&DHT_DDR, DHT_INPUTPIN, GPIO_INPUT); // Definir la broche 22 en entree
	_delay_us(40); // Attendre que le changement en entree se fasse
	if(gpio_lire(DHT_PIN, DHT_INPUTPIN)) return 1; // Requete non recue
	_delay_us(80); // Attendre que la requete soit confirmee
	if(!gpio_lire(DHT_PIN, DHT_INPUTPIN)) return 2; // Pas de transition desactiver - activer
	_delay_us(80); // Attendre que le capteur se prepare a envoyer les donnees

	// Etape 3 -- Recevoir les donnees
	for(uint8_t i = 0; i < 5; i++){
		data[i] = dht_reception_octet();
	}
	if((uint8_t)(data[0] + data[1] + data[2] + data[3]) != data[4]) return 3; // Donnees non-valides

	// Etape 4 -- Sauvegarder les donnees
	*hum = data[0];
	*temp = data[2];

	return 0; // Succes
}
