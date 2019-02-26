
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> //Controle avec Interrupts 
#include <stdbool.h> 


volatile uint8_t minuterieExpiree;

volatile uint8_t boutonPoussoir;

ISR ( TIMER1_COMPA_vect ) {

minuterieExpiree = 1;

}

ISR ( INT0_vect ) {

boutonPoussoir = 1;

// anti-rebond
}


void partirMinuterie ( uint16_t duree ) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisée par 1024

// interruption après la durée spécifiée

TCNT1 = 0 ; //compteur commence a compter a 0.

OCR1A = duree; // comparateur verfie le compteur

TCCR1A = 0x00 ; //registre de controle , o pour normal

TCCR1B |= (1 << CS10) | (1 << CS12 )| (1 << WGM12); // le timer division par 1024
//  xxxxxxxx 
//| 00000001    --> 1 soit 1 << 0 et on sait que CSn0 vaut 0. Donc on obtient 00000001 = 1 << CS00
//| 00000100    --> 4 soit 1 << 2 et on sait que CSn2 vaut 1. Donc on obtient 00000100 = 1 << CS12 
//| 00001000    --> 8 soit 1 << 3 et on sait que WGM12 vaut 3. Donc on obtient 00001000 = 1 << WGM12 
//= xxxx11x1 
TCCR1B &= 0xFD & 0xEF; //pour forcer la position 2 a 0 et position 5 a 0;
TCCR1C = 0;

TIMSK1 = 0x02; //OCIE3A vaut 2
}


void initialisation ( void ) {
// cli est une routine qui bloque toutes les interruptions.
// Il serait bien mauvais d'etre interrompu alors que
// le microcontroleur n'est pas pret...
cli ();
boutonPoussoir=0;
// configurer et choisir les ports pour les entrees
// et les sorties. DDRx... Initialisez bien vos variables
DDRB = 0xff; // PORT B est en mode sortie
PORTB = 0x00;  // La LED est ETEINT
// cette procedure ajuste le registre EIMSK
// de ATmega324PA pour permettre les interruptions externes
EIMSK |= (1 << INT0) ; //shift 1 de INT0 fois vers la gauche ce qui vaut ..00001
// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA
EICRA |= (1 << ISC00) | (1 << ISC01 ); // on veut que le premier bit de EICRA soit 1 et le second soit 1 (xxxxxx11) pour sensibiliser linterupteur au front montant 
// Pour ce faire on as EICRA = xxxxxxxx et pour generer xxxxxx11 oon effectue lopperation suivante 
// The rising edge of INTn generates asynchronously an interrupt request (11)
//  xxxxxxxx 
//| 00000001    --> 1 soit 1 << 0 et on sait que ISC00 vaut 0. Donc on obtient 00000001 = 1 << ISC00 
//| 00000010    --> 2 soit 1 << 1 et on sait que ISC01 vaut 1. Donc on obtient 00000010 = 1 << ISC01 
//= xxxxxx11
//
sei (); // sei permet de recevoir Ã  nouveau des interruptions.
}


int main()
{

initialisation();

_delay_ms(1000); // 10 sec
PORTB= 0x02; // ROUGE
_delay_ms(100); //1/10 sec
PORTB= 0x00; //ETEINT
boutonPoussoir=0;
partirMinuterie(7812);
do {
// attendre qu'une des deux variables soit modifiée
// par une ou l'autre des interruptions.
} while ( minuterieExpiree == 0 && boutonPoussoir == 0 ); // cette boucle est dune duree max de 1sec


// Une interruption s'est produite. Arrêter toute

// forme d'interruption. Une seule réponse suffit.

cli ();

// Verifier la réponse

if (minuterieExpiree == 0)
    PORTB=0x01; // VERT 
else
    PORTB = 0x02; //ROUGE
}

