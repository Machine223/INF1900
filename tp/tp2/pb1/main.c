/*
 *  
 *  Programme : main.c
 *  Auteur : Abderrahim Ammour (1924705) et Abdelkader Zobiri (1891451)
 *  Objectif : TP2 probleme 1 
 *
 *  Les compteurs sont une forme de machines à états. 
 *  On veut ici simplement que la DEL soit éteinte au départ. 
 *  On doit appuyer et relâcher 5 fois le bouton-poussoir avant que la DEL tourne 
 *  au rouge pendant exactement 1 seconde. Par la suite, on revient au départ pour
 *  pouvoir recommencer.
 *  
 *  Date : 25 janvier 17h00
 *  Version : Version 1.1.2
 *
 *  Table des états
 * 
 *  Etat précedent Entrée Etat suivant   Sortie
 *_______________________________________________
 *      INIT         0      INIT         ÉTEINT
 *      INIT         1       EA          ÉTEINT
 *      EA           0       EA          ÉTEINT
 *      EA           1       EB          ÉTEINT
 *      EB           0       EB          ÉTEINT
 *      EB           1       EC          ÉTEINT
 *      EC           0       EC          ÉTEINT
 *      EC           1       ED          ÉTEINT
 *      ED           0       ED          ÉTEINT
 *      ED           1       EE          ROUGE(1sec)
 *      EE           0       INIT        ÉTEINT
 *
 *
 *    DEL -> PORTA1-2
 * 
 */

#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 


//Enumerer les entree A et B
enum etats {INIT, EA,EB,EC,ED,EE};

//La sortie  B
void setPort(){
  DDRB = 0xff; // PORT B est en mode sortie
}


enum etats lire_bouton_poussoir (enum etats etat)
{   
  if (PIND & 0x04)
  {
    _delay_ms(15);
    if (PIND & 0x04)
    {
      etat ++;  
      while (PIND & 0x04);
    }     
  }
  return etat;
}


int main()
{
setPort();
enum etats etat = 0;        // etat Init
  for(;;)                   // boucle sans fin
  {
    PORTB = 0x00;           // eteinte au debut
    etat = lire_bouton_poussoir(etat);
    if (etat == EE){        // derniere etat on fait la transition au premier etat 
      PORTB = 0x02;         // LED Rouge
      _delay_ms(1000);      // Durée d'une seconde
      PORTB = 0x00;         // LED Eteinte
      etat = 0;             // etat Reset
    }
  } 
  return 0; 
}

