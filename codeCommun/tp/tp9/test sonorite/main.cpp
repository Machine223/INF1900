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
		
	//uint8_t note = 12;
	//Note notes = 0;

	// Chanson 1 
    int chanson1[] = {72, 12, 20, 24, 67, 12, 24, 64, 12,65,73,81};
	
	//PORTB &= (0xff ^ (1 << PIEZOGRD));
    
	for (int i=0; i<9; i++) 
	{
		int note = chanson1[i];
		Sonorite::jouerNote(note);
		_delay_ms(200);	
		Sonorite::arreterSon();
	}
	Sonorite::jouerSonoriteSonGrave();
	_delay_ms(600);
	Sonorite::arreterSon();

	Sonorite::jouerSonoriteSonAigu();
	_delay_ms(600);
	Sonorite::arreterSon();
}