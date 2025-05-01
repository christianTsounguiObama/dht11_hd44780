#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "hd44780.h"


// Definition des broches de connexion
//// Briches de control de l'ecran
#define LCD_EN PE4 // Digital pin2
#define LCD_RS PE5 // Digital pin3

//// Broches de reception de donnees (Mode 4-bit)
#define LCD_D4 PG5 // Digital pin4
#define LCD_D5 PE3 // Digital pin5
#define LCD_D6 PH3 // Digital pin6
#define LCD_D7 PH4 // Digital pin7

// Activation de l'ecran
void lcd_envoi_impulsion(void){
	gpio_ecrire(&PORTE, LCD_EN, 1); // Envoi signal a la broche 2
	_delay_us(1); // Attendre que le signal s'etablisse
	gpio_ecrire(&PORTE, LCD_EN, 0); // Eteindre signal a la broche 2
	_delay_us(100); // Attendre que le signal s'eteigne
}

void transmission_donnee(volatile uint8_t* port, uint8_t pin, uint8_t value, uint8_t nibble){
	if(nibble & (1 << value)){
		gpio_ecrire(port, pin, 1);
	}else{
		gpio_ecrire(port, pin, 0);
	}
}

// Envoi 4 bits
void lcd_envoi_bits(uint8_t nibble, uint8_t is_data){
	// Broche RS
	if(is_data){
		gpio_ecrire(&PORTE, LCD_RS, 1); // Envoi signal a la broche RS
	}else{
		gpio_ecrire(&PORTE, LCD_RS, 0); // Eteindre signl a la broche RS
	}

	// Envoi de donnees 4-bits en parallel
	transmission_donnee(&PORTG, LCD_D4, 0, nibble); // Broche D4
	transmission_donnee(&PORTE, LCD_D5, 1, nibble); // Broche D5
	transmission_donnee(&PORTH, LCD_D6, 2, nibble); // Broche D6
	transmission_donnee(&PORTH, LCD_D7, 3, nibble); // Broche D7

	lcd_envoi_impulsion(); // Envoi impulsion
}

void lcd_envoi_octet(uint8_t byte, uint8_t is_data){
	lcd_envoi_bits(byte >> 4, is_data); // 4-bits hauts
	lcd_envoi_bits(byte & 0x0F, is_data); // 4-bits bas
}

void lcd_envoi_commande(uint8_t cmd){
	lcd_envoi_octet(cmd, 0); // Envoi commande a l'ecran LCD
}

void lcd_ecrire_caractere(char c){
	lcd_envoi_octet(c, 1); // Envoi d'un caractere a l'ecran
}

void lcd_ecrire_mot(const char* str){
	//uint8_t count = 0;
	while(*str){
	//	if(count==16){
	//		lcd_envoi_commande(0xC0); // Nouvelle ligne
	//	}
		lcd_ecrire_caractere(*str++); // Envoi du mot a l'ecran un caractere a la fois
	//	count++;
	}
}

void lcd_initialization(void){
	// Definir les broches de control de l'ecran comme sorties
	DDRE |= (1 << LCD_RS) | (1 << LCD_EN);

	// Definir les broches de donnees en sorties
	DDRE |= (1 << LCD_D5);
	DDRG |= (1 << LCD_D4);
	DDRH |= (1 << LCD_D6) | (1 << LCD_D7);

	_delay_ms(50); // Attendre 50 ms pour que l'ecran s'active

	// Sequence d'initialization de l'ecran
	lcd_envoi_bits(0x03, 0);
	_delay_ms(5);
	lcd_envoi_bits(0x03, 0);
	_delay_us(150);
	lcd_envoi_bits(0x03, 0);
	_delay_us(150);
	lcd_envoi_bits(0x02, 0);
	_delay_us(150);

	lcd_envoi_commande(0x28); // Mode 4-bit et 2 lignes
	lcd_envoi_commande(0x0C); // Allumer l'ecran sans le curseur
	lcd_envoi_commande(0x06); // Mode entree
	lcd_envoi_commande(0x01); // Effacer l'ecran
	_delay_ms(2);
}
