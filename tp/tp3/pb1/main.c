/*
 *  
 *  Programme : main.c
 *  Auteur : Abderrahim Ammour (1924705) et Abdelkader Zobiri (1891451)
 *  Objectif : TP3 probleme 1 
 *
 *  Problème 1: Atténuation d'une DEL
 *  
 *  Date : 
 *  Version : Version 1.1.2
 *
 *  Table des états
 * 
 *  Etat précedent Entrée Etat suivant   Sortie
 *_______________________________________________
 *     
 *
 *
 */
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 

void setPort()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode sortie
}

void signalPWM (uint16_t a, uint16_t b)
{ 
    PORTB = 0x00; //eteint
    for (uint16_t i=0; i< a; i++)
      _delay_ms(0.001);
    PORTB = 0x02; // Rouge
    for (uint16_t i=0; i< (b-a); i++)
      _delay_ms(0.001);
    _delay_ms(0.2)  ;
 }


int main()
{
  setPort();
  uint16_t a=0; 
  uint16_t b=1000; 

  for( uint16_t i = 0; i<1000; i++)  // boucle sans fin
  {
    a = a+1;
    signalPWM(a,b);
       
  }
  PORTB = 0x00;

  return 0; 
}


