#ifndef TRACKER_CPP
#define TRACKER_CPP
#include "Memoire_24.h"
#include "pins.h"
#include "can.h"
#include "global.h"
class Tracker{
public:
    bool calibrer(); // on vient faire une calibration 
    bool calibrerFromMemory(); // calibrer a partir de memoire
    bool lecture();
    // arreter la lecture avec can::~can()
    bool capteurs[5];
    uint8_t read(uint8_t pos); //pos prend des valeurs entre 0 a 7
    Tracker();
private:
    void init();
    uint8_t analogValue[5];  // valeur analogique suite a la lecture
    uint8_t seuil_[5];          // attribue utiliser pour le calibrage
};

#endif
/*
How to Use
In the case of working with a MCU:

VCC ↔ 3.3V ~ 5V
GND ↔ GND
IR1 ↔ MCU.IO (ch1, analog output)
IR2 ↔ MCU.IO (ch2, analog output)
IR3 ↔ MCU.IO (ch3, analog output)
IR4 ↔ MCU.IO (ch4, analog output)
IR5 ↔ MCU.IO (ch5, analog output)

*/
