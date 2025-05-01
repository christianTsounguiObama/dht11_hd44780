#ifndef DHT11_H
#define DHT11_H

#include <stdint.h>

// Lecture d'un bit du DHT11
uint8_t dht_reception_bit(void);

// Lecture d'un octet
uint8_t dht_reception_octet(void);

// Lecture de temperature et humidite
uint8_t dht_lecture(uint8_t* hum, uint8_t* temp);
#endif
