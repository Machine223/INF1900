/*
 *  
 *  Programme : main.c
 *  Auteur : Abderrahim Ammour (1924705) et Abdelkader Zobiri (1891451)
 *  Objectif : TP5 probleme 1 
 *
 *  Problème 1 : Vous devrez faire un programme qui écrit la chaîne de caractères « *P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*» 
 *  suivi d'un 0x00 en mémoire externe. La chaîne commencera à l'adresse 0x00. Faire en sorte que votre programme puisse aller relire 
 *  la chaîne en question et comparez la chaîne de caractères
 * 
 *  Date : 12 fevrier 2018
 *  Version : Version 1.1.2
 *
 *  Table des états
 * 
 *  Etat précedent Entrée Etat suivant   Sortie
 *_______________________________________________
 *   
 *  
 *    DEL -> ROUGE si la chaine n'est pas similaire
 *    DEL -> VERT si la chaine est similaire
 * 
 */
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
#include <stdbool.h> 
#include "memoire_24.h"
#include <string.h>

void setPort()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode ENTREE
}


void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premier registres pour vous éviter des complications

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la reception et la transmission par le UART0

//UCSR0A |= (1<<MPCM0) ; 

UCSR0B |= (1<<RXEN0)| (1<<TXEN0) ; // activer la reception activer la transmission

// Format des trames: 8 bits, 1 stop bits, none parity

UCSR0C |= (1<<UCSZ00)| (1<<UCSZ01)  ; // 8 bits
UCSR0C &= 11000111; // usb0s a 0 1 stop bits upm00 upm01 a 0 none parity
}

void transmissionUART ( uint8_t donnee ) {
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
/* Put data into buffer, sends the data */
UDR0 = donnee;
}


int main()
{
  Memoire24CXXX memoire;
  setPort();
  initialisationUART();
 
  uint16_t adresse = 0x0000;
  uint8_t* donnee = 0;

while (*donnee != 0xFF )
  {
    memoire.lecture(adresse, donnee);
    transmissionUART (*donnee);
    adresse ++;

  }
  return 0 ;
}

