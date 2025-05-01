#include "uart.h"
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>

// Configuration du protocol de communication
void uart_init(void){
	UBRR0H = 0;
	UBRR0L = 103; // Exple: 9600 pour 16MHz --> baud = 103
	UCSR0B = (1 << TXEN0); // Activer la transmission
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Donees 8-bit
}

// Lecture d'un caractere
void uart_envoi_caractere(char c){
	while(!(UCSR0A & (1 << UDRE0))); // Attendre que le buffer soit libre
	UDR0 = c;
}

// Lecture d'un mot
void uart_envoi_mot(const char* str){
	while(*str){
		uart_envoi_caractere(*str++); // Envoyer le mot un caractere a la  fois
	}
}

// Convertir donnee en nombre (optionel)
void uart_envoi_nombre(uint8_t num){
	char buffer[4];
	itoa(num, buffer, 10);
	uart_envoi_mot(buffer);
}

