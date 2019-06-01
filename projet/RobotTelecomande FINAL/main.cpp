
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> //Controle avec Interrupts 
#include <stdbool.h> 
#include "lectureBP.h"
#include "clock.h"
#include "SIRC.h"
using namespace std;
volatile static uint8_t minuterieExpiree;
LectureBP principalReader;
void initialisation(void) {
        cli();
        // configurer et choisir les ports pour les entrees// et les sorties. DDRx... Initialisez bien vos variables
        DDRB = 0xff; // PORT B est en mode sortie
        DDRD = 0x00;
        PORTB = 0x00;  // La LED est ETEINT
        // permettre les interruptions externes
        EIMSK |= (1 << INT0);
        // il faut sensibiliser les interruptions externes aux changements de niveau du bouton-poussoir
        // en ajustant le registre EICRA
        EICRA |= (1 << ISC00) | (1 << ISC01); 
        sei(); // sei permet de recevoir Ã  nouveau des interruptions.
}
void partirMinuterie(uint16_t duree) {
        minuterieExpiree = 0;
        // mode CTC du timer 1 avec horloge divisée par 1024 // interruption après la durée spécifiée
        TCNT1 = 0; //compteur commence a compter a 0.
        OCR1A = duree; // comparateur verfie le compteur
        TCCR1A = 0x00; //registre de controle , o pour normal
        TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12); // le timer division par 1024
        TCCR1C = 0;
        TIMSK1 = 0x02; //OCIE3A vaut 2
}
ISR(TIMER1_COMPA_vect) {
        clock::sysClock++;
        minuterieExpiree = 1;
}
ISR(INT0_vect) {
        _delay_ms(10);
        if (PIND & 0x04){ //anti rebound
        principalReader.increment();
        partirMinuterie(15625);//2sec
        if (principalReader.getBP() == 10)
                principalReader.setBP(1);
        }
        EIFR |= (1 << INTF0) ;
}
int main () 
{
        initialisation(); //                Le programme utilise un compteur(un entier) et une minuterie. Au démarrage du programme, le compteur est à 0 et la minuterie est inactive.
        while(minuterieExpiree ==0);
        cli();
        //test
        for (uint8_t i = 0; i < principalReader.getBP(); i++)
        {
        PORTB = 0x01;
        _delay_ms(100);
        PORTB = 0x00;
        _delay_ms(200);
        }

        SIRC sender;
        while(true)
                sender.write(principalReader.getBP(),12);			


        principalReader.reset(); //Si la minuterie atteint 2 secondes, elle est arrêtée et un signal correspondant à la valeur du compteur est émis.La valeur du compteur est ensuite remise à 0.
        return 0;
}