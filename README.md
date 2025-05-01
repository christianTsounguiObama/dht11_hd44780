# Lecture de donnees du capteur DHT11 et affiche sur ecran LCD HD44780 16x22 en C bas-niveau sur ATmega2560

Ce projet implémente, en langage C bare-metal, une interface directe entre un microcontrôleur ATmega2560 (Arduino Mega) et un capteur de température et d’humidité DHT11, sans utiliser de bibliothèques externes. Les données mesurées sont ensuite transmises via le protocole UART à un terminal série et a l'ecran LCD. L’objectif est de comprendre les protocoles de communication 1-Wire spécifique au DHT11, communication parallele du HD44780 16x2. Les donnees de temperature et d'humidite sont envoyees au moniteur serie et a l'ecran LCD.

## Structure du projet
dht11_ws/ ├── include/ # Fichiers d'en-tête (headers)</br>
		  │ ├── dht11.h </br>
	      │ ├── uart.h </br>
		  │ └── gpio.h </br>
          |  └── hd44780.h </br>
          ├── drivers/ # Fichiers source pour les pilotes bas-niveau </br>
          │ ├── dht11/dht11.c </br>
	      │ ├── uart/uart.c</br>
		  │ └── gpio/gpio.c</br>
            └── hd44780/hd44780.c</br>
		  ├── main/ # Logique principale de l’application </br>
          │ └── main.c </br>
		  ├── build/ # Fichiers compilés (ignorés par Git) </br>
		  ├── Makefile # Système de compilation </br>
		  └── .gitignore</br>

## Fonctionnalités

- Lecture des données du capteur DHT11 via le protocole 1-Wire.
- Traitement du signal (timing précis, gestion des bits de données).
- Configuration et utilisation du module UART interne du microcontrôleur.
- Transmission des mesures température/humidité vers un terminal série.
- Initialisation manuelle de l’écran selon le protocole HD44780.
- Affichage des donnees sur ecran LCD HD44780.
- Implémentation de l’envoi de données/commandes via un bus parallèle 4 bits.
- Codé sans bibliothèques Arduino, uniquement en accès registre.

## Prérequis

- **Matériel** : Arduino Mega 2560, capteur DHT11, ecran LCD HD44780 16x2
- **Outils** :
  - `avr-gcc`
  - `avrdude`
- **Système** : Linux (testé sous Ubuntu 20.04+)

## Démarrage rapide

### 1. Cloner le dépôt

```bash
git clone https://github.com/christianTsounguiObama/dht11_hd44780.git
cd dht11_hd44780/dht11_hd44780
```
### 2. Flasher le fichier binaire
Assurez-vous que votre carte est connectée via USB et ajustez PORT dans le Makefile si nécessaire.
```bash
make
```

### 3. Lire les données sur le port série
Utilisez un outil comme screen :
```bash
screen /dev/ttyUSB0 9600
```

## Licence
Ce projet est open source et disponible sous la Licence Apache2.0.

### Contribuer
Les contributions sont les bienvenues. Si vous trouvez des problèmes, n’hésitez pas à ouvrir une issue ou à proposer des améliorations.

### Remerciements
Ce projet fait partie de mon initiative pour te montrer comment construire des systèmes embarqués à partir de zéro au travers de projets 
dont le niveau de difficulté augmente progressivement. Happy Coding!





