#include "lectureBP.h"
//uint8_t LectureBP::nbAppuis_;
LectureBP::LectureBP() { // Constructeur
	nAppuis_=0; // 
}
void LectureBP::reset() { // Constructeur
	nAppuis_=0; // 
}
void LectureBP::setBP( uint8_t val) { // La configuration de l'ISR
	nAppuis_ = val;
	if (nAppuis_ >= 10)
		nAppuis_= 1;
}
uint8_t LectureBP::getBP(){ // Recuperer le nombre d'appui sur le Bouton Poussoir
	return nAppuis_;
}
void LectureBP::increment() { // Constructeur
	nAppuis_ ++; // 
	if (nAppuis_ == 10)
		setBP(1);
}