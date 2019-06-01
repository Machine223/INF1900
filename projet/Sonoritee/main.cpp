#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "../librairie/sonorite.h"
#include "../librairie/pins.h"


// //Tableau qui contient les frequences pour les notes 
// const double tabMus[] = { 110.0, 116.5409404, 123.4708253, 130.8127827, 
// 	130.5913155, 146.832384, 155.5634919, 164.8137785, 174.6141157, 
// 	184.9972114, 195.997718, 207.6523488, 220.0, 233.0818808, 
// 	246.9416506, 261.6255653, 277.182631, 293.6647679, 311.1269837, 
// 	329.6275569, 349.2282314, 369.9944227, 391.995436, 415.3046976, 
// 	440.0, 466.1637615, 493.8833013, 523.2511306, 554.365262, 
// 	587.3295358, 622.2539674, 659.2551138, 69.4564629, 739.9888454, 
// 	783.990872, 830.6093952, 880.0};

// /**********************************************************************
// * Fonction: void PWMnotes(uint8_t indice)
// * Description: Le timer 0 en mode CTC est utilise pour le son avec PWM 
// * Paramètres: la période de temps actifs de la note (nomme : indice)
// * Retour: Aucun
// **********************************************************************/
// void PWMnotes(uint8_t indice)
// {
// 	TCCR0A |= (1 << COM0A0) | (1 << WGM01); // mode CTC
// 	TCCR0B |= (1 << CS02); //dision par 256
// 	OCR0A = indice; //relier au PINB3
// }

// /**********************************************************************
// * Fonction: uint8_t tempsActif(uint8_t indice)
// * Description: Calcul le temps actif d'une note selon sa fréquence
// * Paramètres: la nième note du tableau de fréquence (de 45 à 81)
// * Retour: la période de temps actifs de la note choisie
// **********************************************************************/
// uint8_t tempsActif(uint8_t indice)
// {
// 	double frequenceChoisie = tabMus[indice-45];
// 	uint8_t tempsActif = 8000000/(2*frequenceChoisie); 
// 	//retourne le temps actif selon la note
// 	return tempsActif;
// }

// /**********************************************************************
// * Fonction: void arreterSon() 
// * Description: Arrêter le son
// * Paramètres: Aucun
// * Retour: Auncun
// **********************************************************************/
// void arreterSon() 
// {
// 	OCR0A = 0;
// }

// /**********************************************************************
// * Fonction: void jouerNote(uint8_t indice)
// * Description: Retour du PWM d'une note
// * Paramètres: la nième note du tableau de fréquence (de 45 à 81)
// * Retour: Auncun
// **********************************************************************/ 
// void jouerNote(uint8_t indice)
// {
// 	PWMnotes(tempsActif(indice));
// }

// enum Note {
// 	Do = 65,
// 	Re = 73,
// 	Mi = 81,
// 	Fa = 45,
// 	Sol = 49,
// 	La = 55,
// 	Si = 61,
// 	Do = 32,
	
// };

volatile bool on = false;

int main() {
	
	DDRD = 0xff; //piezo
	//Initialisation des ports
	
	//Initilastion des classes et creation des objets
	
	//Intialisation des variables 
		
	//uint8_t operande = 12;
	//Note notes = 0;

	// Chanson 1 
    int chanson1[] = {72, 12, 20, 24, 67, 12, 20, 24, 64, 12, 20, 24, 69, 12, 20, 12, 71, 12, 20, 12, 70, 12, 69, 12, 20, 12, 67, 16, 76, 16, 79, 16, 81, 12, 20, 12, 77, 12, 79, 12, 20, 12, 76, 12, 20, 12, 72, 12, 74, 12, 71, 12, 20, 24 };
	int chanson2[] = {76, 12, 72, 12, 20, 12, 67, 12, 55, 12, 20, 12, 68, 12, 20, 12, 69, 12, 77, 12, 53, 12, 77, 12, 69, 12, 60, 12, 53, 12, 20, 12, 71, 16, 81, 16, 81, 16, 81, 16, 79, 16, 77, 16, 76, 12, 72, 12, 55, 12, 69, 12, 67, 12, 60, 12, 55, 12, 20, 12, 76, 12, 72, 12, 20, 12, 67, 12, 55, 12, 20, 12, 68, 12, 20, 12, 69, 12, 77, 12, 53, 12, 77, 12, 69, 12, 60, 12, 53, 12, 20, 12, 71, 12, 77, 12, 20, 12, 77, 12, 77, 16, 76, 16, 74, 16, 72, 12, 64, 12, 55, 12, 64, 12, 60, 12, 20, 36,0};
	int chanson3[] = {72, 12, 20, 24, 67, 12, 20, 24, 64, 24, 69, 16, 71, 16, 69, 16, 68, 24, 70, 24, 68, 24, 67, 12, 65, 12, 67, 48,0};
	//PORTB &= (0xff ^ (1 << PIEZOGRD));
	// j = nombre de répétitions de la chanson
    for (int j=0; j<1; j++) 
	{
        for (int i=0; i<45; i++) 
       	{
        	int operande = chanson1[i];
			int operande2 = chanson3[i];
			Sonorite::jouerNote(operande);
			Sonorite::jouerNote(operande2);
           	_delay_ms(23);	
			Sonorite::arreterSon();
		}
		
	}
}

// ISR(TIMER1_COMPA_vect){
// 	on = !on;
// 	if(on){
// 		PORTB |= (1 << PIEZOCTRL);
// 	}
// 	else{
// 		PORTB &= (0xff ^ (1 << PIEZOCTRL)); //PIEZOCTRL a 0 donc arrete 
// 	}

// }