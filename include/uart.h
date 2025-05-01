#ifndef UART_H
#define UART_H

#include <stdint.h>
// Configuration du protocol de communication
void uart_init(void);
// Lecture d'un caractere
void uart_envoi_caractere(char c);
// Lecture d'un mot
void uart_envoi_mot(const char* str);
// Convertir donnee en nombre (optionel)
void uart_envoi_nombre(uint8_t num);
#endif
