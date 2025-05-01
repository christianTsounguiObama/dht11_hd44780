# Lecture de capteur DHT11 et transmission UART en C bas-niveau sur ATmega2560

Ce projet implémente, en langage C bare-metal, une interface directe entre un microcontrôleur ATmega2560 (Arduino Mega) et un capteur de température et d’humidité DHT11, sans utiliser de bibliothèques externes. Les données mesurées sont ensuite transmises via le protocole UART à un terminal série ou un autre périphérique. L’objectif est de comprendre le protocole de communication 1-Wire spécifique au DHT11, de le mettre en œuvre via des manipulations de registres, et de configurer l’UART pour envoyer les données en ASCII.

## Structure du projet
dht11_ws/ ├── include/ # Fichiers d'en-tête (headers)</br>
		  │ ├── dht11.h </br>
	      │ ├── uart.h </br>
		  │ └── gpio.h </br>
          ├── drivers/ # Fichiers source pour les pilotes bas-niveau </br>
          │ ├── dht11/dht11.c </br>
	      │ ├── uart/uart.c</br>
		  │ └── gpio/gpio.c</br>
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
- Codé sans bibliothèques Arduino, uniquement en accès registre.

## Prérequis

- **Matériel** : Arduino Mega 2560, capteur DHT11
- **Outils** :
  - `avr-gcc`
  - `avrdude`
- **Système** : Linux (testé sous Ubuntu 20.04+)

## Démarrage rapide

### 1. Cloner le dépôt

```bash
git clone https://github.com/christianTsounguiObama/dht11UART.git
cd dht11UART/dht11_ws
```

### 2. Compiler le projet
```bash
make
```

### 3. Flasher le fichier binaire
Assurez-vous que votre carte est connectée via USB et ajustez PORT dans le Makefile si nécessaire.
```bash
make flash
```

### 4. Lire les données sur le port série
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





