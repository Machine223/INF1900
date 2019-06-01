#ifndef __SONORITE_H__
#define __SONORITE_H__

// C/avr libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Personnalized libraries
#include "debug.h"

namespace Sonorite 
{
	void jouerNote(uint8_t indice);
	void arreterSon();
	void PWMSonorite (uint8_t indice);
	uint8_t tempsActif(uint8_t indice);	
	void jouerSonorite(uint8_t indice);
};
#endif 