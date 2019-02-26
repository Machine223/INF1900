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
#include <avr/interrupt.h> //Controle avec Interrupts 
#include <stdbool.h> 
#include "memoire_24.h"
void setPort()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode sortie
}

int main()
{
  
  setPort();
  char chaine1 [45]= {'*','A', '*', 'O', '*', 'L', '*', 'Y','*','T','*','E','*','C','*','H','*','N','*','I','*','Q','*','U','*','E','*',
                      ' ','*','M','*','O','*','N','*','T','*','R','*','E','*','A','*','L','*'};
  uint8_t* donneeEcrit = (uint8_t*)chaine1;
  
  const uint8_t longueur = 45;
  uint16_t adresse = 0x00; //ADRESSE DE DEBUT,La chaîne commencera à l'adresse 0x00
    
  
 
  Memoire24CXXX memoire; // on cree l'objet memoire
  
    
  memoire.ecriture( 0x00, donneeEcrit, 45);
  //Comparez la chaîne de caractères envoyée à la mémoire et celle relue
  _delay_ms(500); // faut prévoir un délai de 5 ms après l'écriture 
 
  //d'un octet en mémoire et l'accès suivant à la mémoire

  
  
  uint8_t donnee [45];
  memoire.lecture ( 0x00, donnee, 45);

  for (uint8_t i=0 ;i< longueur;i++)
  {
    if(donneeEcrit[i] == donnee[i])
      PORTB = 0x01; //VERT
      _delay_ms(100);
      PORTB = 0x00;
    if(donneeEcrit[i] != donnee[i])
      PORTB = 0x02; //ROUGE
     _delay_ms(100);
      PORTB = 0x00;
  }
  return 0;
}

