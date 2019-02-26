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
#include <avr/interrupt.h> //Controle avec Interrupts 
#include "memoire_24.h"
#include <string.h>
volatile  uint16_t minuterieExpiree ;

ISR ( TIMER1_COMPA_vect ) {
minuterieExpiree = 1;
}

void partirMinuterie ( uint16_t duree ) {

minuterieExpiree = 0;

TCNT1 = 0 ; //compteur commence a compter a 0.
OCR1A = duree; // comparateur verfie le compteur
TCCR1A = 0x00 ; //registre de controle , o pour normal
TCCR1B |= (1 << CS10) | (1 << CS12 )| (1 << WGM12); // le timer division par 1024
TCCR1B &= 0xFD & 0xEF; //pour forcer la position 2 a 0 et position 5 a 0;
TCCR1C = 0;
TIMSK1 = 0x02; //OCIE3A vaut 2
}

void initialisation ( void ) {
cli ();
DDRB = 0xff; // PORT B est en mode sortie
PORTB = 0x00;  // La LED est ETEINT
sei (); // sei permet de recevoir Ã  nouveau des interruptions.
}



int main()
{
  initialisation();

  char* message= "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
  // char* message2= "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";

  Memoire24CXXX memoire;

  uint16_t adresse = 0x0000;
  memoire.ecriture(adresse, (uint8_t*) message, sizeof(message));

  partirMinuterie (1758); //_delay_ms(225); //5 fois 45 pour le delai
  do 
  {}
  while(minuterieExpiree == 0);

  char* donnee;
  bool egale = true;
  memoire.lecture(adresse, (uint8_t*) donnee, sizeof(message));
  for (int i = 0; i < sizeof(message) ; i++)
      if (message[i] != donnee [i] )
        egale = false;
    
  if (egale == false)
    PORTB=0x02;
  else
    PORTB=0x01;

  return 0 ;
}

