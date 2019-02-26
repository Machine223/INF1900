/*
 *
 *  Programme : main.c
 *  Auteur : Abderrahim Ammour (1924705) et Abdelkader Zobiri (1891451)
 *  Objectif : TP2 probleme 2 
 *
 *  Quand la carte mère démarre, la DEL libre doit s'allumer en ROUGE. 
 *  Si le bouton-poussoir noir est pesé, la DEL affiche la couleur ambre.
 *  Quand le bouton-poussoir est relâché, la DEL devient VERTe. Si le bouton 
 *  est de nouveau pesé, la DEL prend la couleur ROUGE encore. Quand il est relâché,
 *  la DEL s'ÉTEINT. Si le bouton est de nouveau pesé, la DEL affiche la couleur VERTe.
 *  Quand il est relâché, la DEL tourne au ROUGE ce qui fait que la carte mère est de 
 *  retour à son état initial et tout peut recommencer.
 *  
 *  Date : 25 janvier 17h00
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

int lire_bouton_poussoir ()
{   
  if (PIND & 0x04 )
  { 
    _delay_ms(15);
    if (PIND & 0x04)
      return 1;
  }
  return 0;
}


int main()
{
  setPort();
  int boutonPoussoirPrec = 0; // designe l'etat présent du bouton poussoir
  enum etats etat = INIT; 

  for(;;)  // boucle sans fin
  {
    int BoutonPoussoirActuel=lire_bouton_poussoir();
    
    if ( BoutonPoussoirActuel ^ boutonPoussoirPrec)
    // XOR afin de voir quand est-ce qu on a changé l etat du bouton poussoir
    {
      etat++;
    }

    boutonPoussoirPrec = BoutonPoussoirActuel;

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
  return 0; 
}

