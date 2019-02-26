/*
 *  
 *  Programme : main.cpp
 *  Auteur : Abderrahim Ammour (1924705) et Abdelkader Zobiri (1891451)
 *  Objectif : TP6 probleme 2 
 *
 *  Problème 2 : Faire un robot pouvant se faire bronzer.Si la lumière est 
 *  basse (en cachant la photorésistance), la DEL prendra la couleur verte.
 *  Si la lumière est à un bon niveau (lumière ambiante), la DEL tournera à l'ambré. 
 *  Si la lumière est trop forte (photorésistance sous une lampe de poche), 
 *  la DEL devient rouge.
 *  
 *  Date : 22 fevrier 2019
 *  Version : Version 1.2
 *
 *  
 *  Seuil acceptable (avec la photorésistance): 
 * 
 *  Si la lumière est basse -> DEL VERT
 *  Si la lumière est à un bon niveau  -> DEL AMBRE
 *  Si la lumière est trop forte -> DEL ROUGE
 *
 *  De plus, nous avons tester l'ecriture et la lecture sur la memoire EEPROM,
 *  afin de traduire le signal en caratere ascii pour verifier le bon fonctionnement
 *  et nous permettre ainsi d'evaluer le bon seuil de l'intensite lumineux 
 *  de la photorésistance. Nous avons convertie les valeurs obtenue de la table ascii 
 *  en decimal, afin d'avoir au final une echelle de 0 a 128. De 0 a 25 correspond a 
 *  une faible intensite de la lumiere. De 26 a 122 correspond a une lumiere ambiante 
 *  de la salle. De 123 a 128 correspond a une lumiere intense tel que celle de notre cellulaire.
 *
 * 
 *  
 */
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
#include "can.h" 
uint8_t Rouge = 0x01;
uint8_t Vert = 0x02;
uint8_t Eteint = 0x00;

void initialisation ( void ) {
    DDRB = 0xff;    // PORT B est en mode sortie
    DDRD = 0x00;    // PORTD en entree
    PORTB = 0x00;   // La LED est ETEINT
}
void couleurAmbree()
{
    PORTB = Rouge;
    _delay_ms(3);
    PORTB = Vert;
    _delay_ms(4);
}

int main()
{
    can signal; // constructeur dans le fichier can.cpp qui fait l'initialisation du convertisseur
    initialisation();
    uint8_t valeurNumerique =0; // Valeur utiliser pour l'intensite lumineux de la photorésistance                       

    for (;;) //Boucle infinie qui repete l'instruction suivante
    {
        valeurNumerique = signal.lecture(0); // Appel la fonction lecture dans can.cpp 
        // Faire une conversion et aller retourner le resultat sur 16 bits
        // dont seulement les 10 de poids faibles sont significatifs.
    
        if (0 <= valeurNumerique && valeurNumerique <= 25 )
            PORTB = Vert;
        while ( 25 < valeurNumerique && valeurNumerique <= 122 )
        {
            couleurAmbree();
            valeurNumerique = signal.lecture(0); //Faire une nouvelle lecture de la valeur
        }
        if ( 122 < valeurNumerique && valeurNumerique <= 128 )
            PORTB = Rouge; 
    }
}


