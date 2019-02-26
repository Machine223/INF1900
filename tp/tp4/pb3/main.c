
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> //Controle avec Interrupts 
#include <stdbool.h> 

void ajustementPWM (double ratio) {
// mise à un des sorties OC1A et OC1B sur comparaison
// réussie en mode PWM 8 bits, phase correcte // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
TCCR1A |= (1<<WGM10) | (1<<COM1A1)  | (1<<COM1B1) ; //pour mettre le signal mode PWM 8 bits, phase correcte 
TCCR1B |= (1<<CS11) ; //diviser lhorloge par 8

OCR1A = 0xff * ratio;
OCR1B = 0xff * ratio;
// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1C = 0;



}
// void initialisation ( void ) {
// // cli est une routine qui bloque toutes les interruptions.
// // Il serait bien mauvais d'etre interrompu alors que
// // le microcontroleur n'est pas pret...
// cli ();
// boutonPoussoir=0;


// }

int main()
{
  cli();
  DDRD= 0xff; // la broche D est en mode sortie 
  ajustementPWM(0);
  _delay_ms(2000);
  ajustementPWM(0.25);
  _delay_ms(2000);
  ajustementPWM(0.5);
  _delay_ms(2000);
  ajustementPWM(0.75);
  _delay_ms(2000);
  ajustementPWM(1);
  _delay_ms(2000);
  DDRD= 0x00; // mettre la sortie broche D a 0
  return 0; 
}