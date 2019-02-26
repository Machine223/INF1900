/*
 *  
 *  Programme : main.c
 *  Auteur : Abderrahim Ammour (1924705) et Abdelkader Zobiri (1891451)
 *  Objectif : TP6 probleme 1 
 *
 *  Problème 1 : Quand le bouton est enfoncé, un compteur qui incrémente 10 fois par 
 *  seconde est activé. Quand le bouton est relâché ou lorsque le compteur atteint 120,
 *  la lumière clignote vert pendant 1/2 seconde. Ensuite, la carte mère ne fait rien. 
 *  uis, deux secondes plus tard, la lumière rouge s'allume. Elle devra clignoter 
 *  (compteur / 2) fois au rythme de 2 fois par seconde. Ensuite, la lumière tourne 
 *  au vert pendant une seconde. Finalement, elle s'éteint et le robot revient à son 
 *  état original.
 *  
 *  Date : 22 fevrier 2019
 *  Version : Version 1.2
 *
 *  Table des états
 * 
 *  Etat précedent Entrée(Bouton)   Etat suivant       Sortie
 *______________________________________________________________
 *      INIT            0            INIT               ÉTEINT
 *      INIT            1            ATTENTE            ÉTEINT (Compteur activer incemente 10 fois par sec.)
 *      ATTENTE         1            ATTENTE            ÉTEINT (Tant que le bouton-pussoir n'est pas relache ou compteur n'a pas atteint 120 sinon passe au prochain etat) 
 *      ATTENTE         0            CLIGNOTEMENT       La lumière clignote VERT pendant 1/2 seconde, puis devient ROUGE 2 sec. plus tard. Ensuite, la DEL devra clignoter (compteur / 2) fois au rythme de 2 fois par seconde.Enfin, la DEL tourne au VERT pendant 1 sec et passe au prochain ETAT.
 *      CLIGNOTEMENT    1            CLIGNOTEMENT       NE FAIT RIEN
 *      CLIGNOTEMENT    0            INIT               ÉTEINT (revient a INIT)
 *
 *     
 * 
 * 
 *    
 * 
 */
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> //Controle avec Interrupts 
#include <stdbool.h> 


volatile uint8_t compteur = 0;
volatile uint8_t minuterieExpiree;
enum  ETAT {INIT, ATTENTE, CLIGNOTEMENT};
enum ETAT etat = 0;
uint8_t Rouge = 0x01;
uint8_t Vert = 0x02;
uint8_t Eteint = 0x00;

ISR ( TIMER1_COMPA_vect ) {
    switch (etat)
    {
        case ATTENTE:
            compteur +=10;
            minuterieExpiree = 1;
        break;
        case CLIGNOTEMENT:
                minuterieExpiree = 1;
        break;
        default: break; 
    }
} 

int lire_bouton_poussoir ()
{   
  if (!(PIND & 0x08 ))
  { 
    _delay_ms(30);
    if (!(PIND & 0x08))
      return 1;
  }
  return 0;
}

void partirMinuterie ( uint16_t duree ) {
    cli();
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    minuterieExpiree =0;
    TCNT1 = 0 ; //compteur commence a compter a 0.
    OCR1A = duree; // comparateur verfie le compteur
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) ; //registre de controle
    TCCR1B |= (1 << CS10) | (1 << CS12 )| (1 << WGM12); // le timer division par 1024
    TCCR1C = 0;
    TIMSK1 |= (1<< OCIE1A); //OCIE1A vaut 1
    sei();
}

void initialisation ( void ) {
    DDRB = 0xff; // PORT B est en mode sortie
    DDRD = 0x00; //PORTD en entree
    PORTB = 0x00; //La LED est ETEINT
    compteur=0;
    minuterieExpiree = 0;
}

void clignoterLed(uint8_t couleur, uint16_t duree, uint8_t repeterFois)
{
    for (uint8_t i = 0; i < repeterFois; i++)
    {
        PORTB = couleur; // couleur
        partirMinuterie( duree); 
        while (minuterieExpiree == 0) {}           
        minuterieExpiree = 0;
        PORTB = Eteint; // eteint
        partirMinuterie( duree);
        while (minuterieExpiree == 0) {}
    } 
}

int main()
{
    initialisation();
    int boutonPoussoirActuel = lire_bouton_poussoir();
    int boutonPoussoirPrec = 0;
    for(;;)
    {
        switch (etat)
        {
            case INIT: 
                boutonPoussoirActuel = lire_bouton_poussoir();
                compteur=0;
                if ( boutonPoussoirActuel ^ boutonPoussoirPrec && boutonPoussoirActuel) // XOR afin de voir quand est-ce qu on a changé l etat du bouton poussoir
                {
                    etat++;
                }
                boutonPoussoirPrec = boutonPoussoirActuel;
            break;

            case ATTENTE: 
                while(!(PIND & 0b00001000) &&  compteur < 110) {
                    partirMinuterie(7812);
                    while(minuterieExpiree == 0){}
                }
                        etat++;
            break;

            case CLIGNOTEMENT: 
                clignoterLed(Vert, 976, 2); // clignoter deux fois en vert par 0.5 secondes
                clignoterLed(Eteint, 7812, 1); // mettre a eteint pendant 2 secondes
                for (uint8_t i =0; i< compteur/2; i++){// clignoter en rouge (compteur / 2) fois au rythme de 2 fois par seconde
                    clignoterLed(Rouge, 1953, 1); 
                }
                clignoterLed(Vert, 7812, 1);  // mettre a Vert pendant 1 seconde
                boutonPoussoirPrec = lire_bouton_poussoir(); // verification de l etat bouton poussoir
                etat= INIT;
            break;

            default: break; 
        }
    }
}



