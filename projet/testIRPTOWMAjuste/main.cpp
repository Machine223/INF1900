#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
//#include "IRPT.h"
#include "clock.h"
#include "can.h" 
#include "Memoire_24.h"
#include "uart.h"


void setPort(){
    DDRB = 0xff; // PORT B est en mode sortie
    DDRD = 0xff;
}
void ajustementPWM (uint8_t val) {
// // mise à un des sorties OC1A et OC1B sur comparaison
// // réussie en mode PWM 8 bits, phase correcte // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
// TCCR1A |= (1<<WGM10) | (1<<COM1A1)  | (1<<COM1B1) ; //pour mettre le signal mode PWM 8 bits, phase correcte 
// TCCR1B |= (1<<CS11) ; //diviser lhorloge par 256 pr avoir 60hz pr la frequence

// OCR1A = 0xff * ratio;
// OCR1B = 0xff * ratio;
// // division d'horloge par 8 - implique une frequence de PWM fixe
// TCCR1C = 0;
TCCR1A=0;//reset the register
TCCR1B=0;//reset the register
TCCR1A=0b01010011;// fast pwm mode(WGM10 and WGM11 are 1)
TCCR1B=0b00011001;// no prescaler and WGM12 and WGM13 are 1
OCR1A=val;//control value from the formula
}


int main () 
{
    UART uart;
    setPort();
    uint8_t valeurNumerique =0 ; // Valeur utiliser pour l'intensite lumineux de la photorésistance  
    for (;;) //Boucle infinie qui repete l'instruction suivante
    {
         for (int j=0; j< 200; ++j)
        {
            if (j%2==0)
                ajustementPWM(100);
            else
                ajustementPWM(50);
            
            for (int i=0; i< 200; ++i)
                if ((can().lecture(7)>>2) <3){
                    PORTB= 0x01;
                    uart.MemoryToUart('s');
                }
                else {
                    PORTB= 0x00;
                    uart.MemoryToUart(valeurNumerique);
                    uart.MemoryToUart('e');
                }
        }
    }                     
    return 0;


    
}