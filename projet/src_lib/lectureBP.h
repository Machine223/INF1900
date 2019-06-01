#ifndef __LECTUREBP_H__
#define __LECTUREBP_H__

// C/avr libraries
#include <avr/io.h>

// Personnalized libraries


class LectureBP{

public:
    LectureBP();	// Constructeur

    void reset();
    void setBP(uint8_t val);	// La configuration de l'ISR
    uint8_t getBP();	// Recuperer le nombre d'appui sur le Bouton Poussoir
    void increment();

private:
    uint8_t nAppuis_;
};

#endif //__LECTUREBP_H__