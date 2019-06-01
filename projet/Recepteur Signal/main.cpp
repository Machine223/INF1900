#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h> //Controle avec Interrupts 
#include "lectureBP.h"
#include "SIRC.h"
#include "uart.h"


void initialisation(void) {
	// configurer et choisir les ports pour les entrees// et les sorties. DDRx... Initialisez bien vos variables
	DDRB = 0xff; // PORT B est en mode sortie
	DDRD = 0xff;
}

int main () 
{
	initialisation(); //		Le programme utilise un compteur(un entier) et une minuterie. Au démarrage du programme, le compteur est à 0 et la minuterie est inactive.
	UART uart;
	SIRC Receiver;
	for (;;){
		PORTB = Receiver.read();
		_delay_ms(100);
	}
	return 0;
}
