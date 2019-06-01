#ifndef __SIRC_H__
#define __SIRC_H__
// CPU CLOCK SPEED
#ifndef F_CPU
# define F_CPU 8000000UL
#endif
#define COMMAND_DIMENSION 7UL
#define VERIFICATION_NUMBER 5UL
// C/avr libraries
#include <avr/io.h>
#include <util/delay.h>
// Personnalized libraries
#include "clock.h"
#include "IRLED.h"

#include "DIGIRPT.h"
class SIRC{
protected:
    int  BEG;
    int  END;
    uint8_t  PROTOCOLE_;
private:
    void init_();
    IRLED led;
    IRPTDIG IRReader;    
    void writeSTART_();
    void write_(bool bit);    // chooses autonomously which write function to call (0 or 1);
    void write1_();
    void write0_();
    void writeEND_();
    void waitForBegginning_();
    int readPulse_();
    int read();
    int getSignal();

public:
    SIRC();
    SIRC(IRLED outputLED);
    void write(uint8_t data, uint8_t size);
    uint8_t getCommand();
};
#endif // __SIRC_H__