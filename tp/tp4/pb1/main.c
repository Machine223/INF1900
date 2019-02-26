/*
 *  
 *  Programme : main.c
 *  Auteur : Abderrahim Ammour (1924705) et Abdelkader Zobiri (1891451)
 *  Objectif : TP4 probleme 1 
 *
 *  Problème 1 : Il vous faudra reprendre le code écrit pour le problème 2 de la semaine 2 (TP2).
 *  
 *  Date : 
 *  Version : Version 1.1.2
 *
 *  Table des états
 * 
 *  Etat précedent Entrée Etat suivant   Sortie
 *_______________________________________________
 *      INIT         0      INIT         ROUGE
 *      INIT         1       EA          AMBRÉ
 *      EA           1       EA          AMBRÉ
 *      EA           0       EB          VERT
 *      EB           0       EB          VERT
 *      EB           1       EC          ROUGE
 *      EC           1       EC          ROUGE
 *      EC           0       ED          ÉTEINT
 *      ED           0       ED          ÉTEINT
 *      ED           1       EE          VERT
 *      EE           1       EE          VERT
 *      EE           0       INIT        ROUGE
 *
 * 
 *    Registre / valeur initial 
 * 
 *    ISC21 = 0
 *    ISC20 = 0
 *    ISC11 = 0
 *    ISC10 = 0
 *    ISC01 = 0
 *    ISC00 = 0
 * 
 * 
 * 
 *    DEL -> PORTA1-2
 * 
 */
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> //Controle avec Interrupts 
#include <stdbool.h> 




volatile enum etats {INIT, EA,EB,EC,ED,EE};
volatile enum etats etat = INIT; 
volatile bool boutonActuel = 0; // 0 = Aucun changement 1 = changement d'état
volatile bool boutonPrecedent = 0;

void switchEtat (){
    switch (etat) {
      case INIT:                 //LED ROUGE
        PORTB = 0b00000010;      //ROUGE
          break;
      case EA:                   //LED AMBRÉ
        while (PIND & 0x04) 
        {
            PORTB = 0b00000010;  //AMBRÉ
            _delay_ms(2);
            PORTB = PORTB >> 1;
            _delay_ms(8);
        }
        break;
      case EB:  
        PORTB = 0b00000001;     //VERT
        break;
      case EC:
        PORTB = 0b00000010;     //ROUGE
        break;
      case ED:
        PORTB = 0b00000000;     //ÉTEINT
        break;
      case EE:
        PORTB = 0b00000001;     //VERT
        break;
      default:
        etat = INIT;            //En cas de default retour à l'état INIT
    }
}

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR ( INT0_vect) { //p.61 Atmega164A external interup Request 0
// laisser un delai avant de confirmer la réponse du
// bouton-poussoir: environ 30 ms (anti-rebond)
_delay_ms ( 30 );
// se souvenir ici si le bouton est pressé ou relâché
boutonActuel = PIND & 0X04;
// changements d'états tels que ceux de la
// semaine précédente
if ( boutonActuel ^ boutonPrecedent ) // changement d etat
    etat++; // lorsqu'on pousse le bouton interruption on incrémente l'état
boutonPrecedent = boutonActuel;
// Voir la note plus bas pour comprendre cette instruction et son rôle
EIFR |= (1 << INTF0) ; // shift vers la gauche et ajoute 1
}


void initialisation ( void ) {
// cli est une routine qui bloque toutes les interruptions.
// Il serait bien mauvais d'être interrompu alors que
// le microcontroleur n'est pas prêt...
cli ();
// configurer et choisir les ports pour les entrées
// et les sorties. DDRx... Initialisez bien vos variables
DDRB = 0xff; // PORT B est en mode sortie
PORTB = 0x00; 
// cette procédure ajuste le registre EIMSK
// de l’ATmega324PA pour permettre les interruptions externes
EIMSK |= (1 << INT0) ;
// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA
EICRA |= (1 << ISC00); //'modifier ici' //QUESTION
// sei permet de recevoir à nouveau des interruptions.
sei ();
}

int main()
{
    initialisation();
    for(;;)  // boucle sans fin
    {
    switchEtat();
    } 
  return 0; 
}

