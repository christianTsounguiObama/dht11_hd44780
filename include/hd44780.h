#ifndef HD44780_H
#define HD44780_H
// Activation de l'ecran
void lcd_envoi_impulsion(void);

// Envoi 4 bits
void transmission_donnee(volatile uint8_t* port, uint8_t pin, uint8_t value, uint8_t nibble);

void lcd_envoi_bits(uint8_t nibble, uint8_t is_data);

void lcd_envoi_octet(uint8_t byte, uint8_t is_data);

void lcd_envoi_commande(uint8_t cmd);

void lcd_ecrire_caractere(char c);

void lcd_ecrire_mot(const char* str);

void lcd_initialization(void);
#endif







